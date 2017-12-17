#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

void suvestiKlasiuDuomenis(struct klase Kl[], int klSk);
void salintiMokinius(struct klase &kl);
void rikiuoti(struct klase &kl);
void sujungti(struct klase Kl[], struct klase &grs, int klSk);
void isvesti(struct klase Kl[], struct klase grs, int klSk);
bool abecelineTvarka(string vard1, string vard2);

struct mokinys
{
    string vard;
    double vid;
};

struct klase
{
    int mokSk;
    double vid;
    mokinys Mok[100];
};

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    int klSk = 4;
    klase Kl[100];
    klase grs;
    suvestiKlasiuDuomenis(Kl, klSk);
    for (int i = 0; i < klSk; i++)
    {
        salintiMokinius(Kl[i]);
        rikiuoti(Kl[i]);
    }
    sujungti(Kl, grs, klSk);
    salintiMokinius(grs);
    rikiuoti(grs);
    isvesti(Kl, grs, klSk);
    return 0;
}

void suvestiKlasiuDuomenis(struct klase Kl[], int klSk)
{
    string path = ".txt";
    for (int i = 0; i < klSk; i++)
    {
        double vidSum = 0;
        Kl[i].mokSk = 0;
        ifstream in(((char) (i + 49) + path).c_str());
        while(!in.eof())
        {
            in >> Kl[i].Mok[Kl[i].mokSk].vard >> Kl[i].Mok[Kl[i].mokSk].vid;
            if (Kl[i].Mok[Kl[i].mokSk].vard == "")
                break;
            vidSum += Kl[i].Mok[Kl[i].mokSk].vid;
            Kl[i].mokSk++;
        }
        Kl[i].vid = vidSum / Kl[i].mokSk;
    }
}

void salintiMokinius(struct klase &kl)
{
    mokinys tuscias;
    for (int i = 0; i < kl.mokSk; i++)
        if (kl.Mok[i].vid < kl.vid)
        {
            if (i + 1 != kl.mokSk)
                for (int j = i; j < kl.mokSk; j++)
                    kl.Mok[j] = kl.Mok[j + 1];
            kl.Mok[kl.mokSk - 1] = tuscias;
            kl.mokSk--;
            i--;
            }
}

void rikiuoti(struct klase &kl)
{
    mokinys tmp;
    for (int i = 0; i < kl.mokSk - 1; i++)
        for (int j = i; j < kl.mokSk; j++)
            if (kl.Mok[j].vid > kl.Mok[i].vid || (kl.Mok[j].vid == kl.Mok[i].vid && kl.Mok[i].vard > kl.Mok[j].vard))
            {
                tmp = kl.Mok[i];
                kl.Mok[i] = kl.Mok[j];
                kl.Mok[j] = tmp;
            }
}

void sujungti(struct klase Kl[], struct klase &grs, int klSk)
{
    double vidSum = 0;
    grs.mokSk = 0;
    for (int i = 0; i < klSk; i++)
        for (int j = 0; j < Kl[i].mokSk; j++)
        {
            grs.Mok[grs.mokSk] = Kl[i].Mok[j];
            vidSum += grs.Mok[grs.mokSk].vid;
            grs.mokSk++;
        }
    grs.vid = vidSum / grs.mokSk;
}

void isvesti(struct klase Kl[], struct klase grs, int klSk)
{
    string virsus = "-------------------------------\n|      Vardas      | Vidurkis |\n-------------------------------\n";
    ofstream out("rezultatai.txt");
    for (int i = 0; i < klSk; i++)
    {
        out << "Klasë " << i + 1 << ":" << endl;
        out << virsus;
        for (int j = 0; j < Kl[i].mokSk; j++)
        {
            out << "|      " << setw(12) << left << Kl[i].Mok[j].vard << "|" << setw(9) << right << fixed << setprecision(2) << Kl[i].Mok[j].vid << " |" << endl;
            out << "-------------------------------" << endl;
        }
        out << endl;
    }
    out << "Rezultatas:" << endl;
    out << virsus;
    for (int i = 0; i < grs.mokSk; i++)
    {
        out << "|      " << setw(12) << left << grs.Mok[i].vard << "|" << setw(9) << right << fixed << setprecision(2) << grs.Mok[i].vid << " |" << endl;
        out << "-------------------------------" << endl;
    }
}
