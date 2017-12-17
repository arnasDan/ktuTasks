#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

struct banknotas
{
    int n;
    int nom;
};

struct zaidejas
{
    string vard;
    int png;
    int banknotuSkaiciai[100];
    bool negaus;
};

void skaityti(struct banknotas Bnknt[], struct zaidejas Zaid[], int &zaidSk, int bnkntSk);
void atiduoti(struct banknotas Bnknt[], struct zaidejas Zaid[], int zaidSk, int bnkntSk);
void skaiciuotiKupiuras(struct zaidejas Zaid[], struct banknotas Bnknt[], int bnkntSk, int zaidNr);
void kasLiko(struct banknotas Bnknt[], int bnkntSk, int &kprSk, int &kprSum);
void isvesti(struct zaidejas Zaid[], int zaidSk, int bnkntSk, int kprSk, int kprSum);

bool arAtiduoti(int png, struct banknotas Bnknt[], int bnkntSk);

int main()
{
    int zaidSk, kprSk = 0, kprSum = 0, bnkntSk = 7;
    banknotas Bnknt[100];
    zaidejas Zaid[100];
    skaityti(Bnknt, Zaid, zaidSk, bnkntSk);
    atiduoti(Bnknt, Zaid, zaidSk, bnkntSk);
    kasLiko(Bnknt, bnkntSk, kprSk, kprSum);
    isvesti(Zaid, zaidSk, bnkntSk, kprSk, kprSum);
    return 0;
}

void skaityti(struct banknotas Bnknt[], struct zaidejas Zaid[], int &zaidSk, int bnkntSk)
{
    ifstream in("Duomenys.txt");
    for (int i = 0; i < bnkntSk; i++)
    {
        in >> Bnknt[i].nom;
    }
    for (int i = 0; i < bnkntSk; i++)
    {
        in >> Bnknt[i].n;
    }
    in >> zaidSk;
    for (int i = 0; i < zaidSk; i++)
    {
        in >> Zaid[i].vard >> Zaid[i].png;
        Zaid[i].negaus = false;
        Zaid[i].banknotuSkaiciai = {0};
    }
}

void atiduoti(struct banknotas Bnknt[], struct zaidejas Zaid[], int zaidSk, int bnkntSk)
{
    for (int i = 0; i < zaidSk; i++)
    {
        if(arAtiduoti(Zaid[i].png, Bnknt, bnkntSk))
        {
            skaiciuotiKupiuras(Zaid, Bnknt, bnkntSk, i);
        }
        else
            Zaid[i].negaus = true;
    }
}

bool arAtiduoti(int png, struct banknotas Bnknt[], int bnkntSk)
{
    banknotas bnkntTmp;
    for (int i = 0; i < bnkntSk; i++)
    {
        bnkntTmp = Bnknt[i];
        for (int j = 1; j <= bnkntTmp.n; j++)
        {
            if ((png < Bnknt[i].nom * (j + 1) || j == Bnknt[i].n) && png - (Bnknt[i].nom * j) >= 0)
            {
                int pngtemp = png;
                png -= (bnkntTmp.nom * j);
                if (png != pngtemp)
                    bnkntTmp.n -= j;
                if (png == 0)
                    return true;
                break;
            }
        }
    }
    return false;
}

void skaiciuotiKupiuras(struct zaidejas Zaid[], struct banknotas Bnknt[], int bnkntSk, int zaidNr)
{
    for (int i = 0; i < bnkntSk; i++)
    {
        for (int j = 1; j <= Bnknt[i].n; j++)
        {
            if ((Zaid[zaidNr].png < Bnknt[i].nom * (j + 1) || j == Bnknt[i].n) && Zaid[zaidNr].png - (Bnknt[i].nom * j) >= 0)
            {
                int pngtemp = Zaid[zaidNr].png;
                Zaid[zaidNr].png -= (Bnknt[i].nom * j);
                if (Zaid[zaidNr].png != pngtemp)
                    Bnknt[i].n -= j;
                Zaid[zaidNr].banknotuSkaiciai[i] = j;
                break;
            }
        }
        if (Zaid[zaidNr].png == 0)
            break;
    }
}

void kasLiko(struct banknotas Bnknt[], int bnkntSk, int &kprSk, int &kprSum)
{
    for (int i = 0; i < bnkntSk; i++)
    {
        kprSk += Bnknt[i].n;
        kprSum += Bnknt[i].n * Bnknt[i].nom;
    }
}

void isvesti(struct zaidejas Zaid[], int zaidSk, int bnkntSk, int kprSk, int kprSum)
{
    ofstream out("Rezultatai.txt");
    for (int i = 0; i < zaidSk; i++)
    {
        out << Zaid[i].vard << setw(16 - Zaid[i].vard.length());
        if (!Zaid[i].negaus)
            for (int j = 0; j < bnkntSk; j++)
                out << Zaid[i].banknotuSkaiciai[j] << setw(3);
        else
            out << setw(16 - Zaid[i].vard.length() - 1) << '\0' << "NEGALIMA";
        out << endl;
    }
    out << setw(0) << kprSk << " " << kprSum << endl;
}
