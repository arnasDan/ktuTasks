#include <iostream>
#include <fstream>

using namespace std;

struct zaidejas
{
    string vardas;
    char raide;
    int kt[2];
    bool atversta;
    int atverusiosKortelesNr;
};

void skaityti(struct zaidejas Zaid[], int &n);
void isvesti(string zodis, int n, struct zaidejas Zaid[], int Tvarka[]);
void rikiuoti(string &zodis, int n, struct zaidejas Zaid[], int Tvarka[]);
bool visosAtvertos(struct zaidejas Zaid[], int n);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    int n;
    string zodis;
    zaidejas Zaid[10];
    skaityti(Zaid, n);
    int Tvarka[n];
    rikiuoti(zodis, n, Zaid, Tvarka);
    isvesti(zodis, n, Zaid, Tvarka);
    return 0;
}

void skaityti(struct zaidejas Zaid[], int &n)
{
    ifstream in("Þaidëjai.txt");
    in >> n;
    for (int i = 0; i < n; i++)
    {
        in >> Zaid[i].vardas >> Zaid[i].raide >> Zaid[i].kt[0] >> Zaid[i].kt[1];
        Zaid[i].atversta = false;
    }
}

void rikiuoti(string &zodis, int n, struct zaidejas Zaid[], int Tvarka[])
{
    zodis = "";
    Tvarka[0] = Zaid[0].kt[0] - 1;
    Zaid[Zaid[0].kt[0] - 1].atversta = true;
    zodis += Zaid[Zaid[0].kt[0] - 1].raide; //debug cout << Tvarka[0] << endl;
    int prev = 1, sk = 1, nr = 1; //nr reikalingas, jeigu atgal reikia eit
    bool fail;
    while (!visosAtvertos(Zaid, n))
    {
        fail = false;
        if (!Zaid[Zaid[prev].kt[0] - 1].atversta && Zaid[prev].kt[0] != 0)
        {
            Tvarka[nr] = Zaid[prev].kt[0] - 1;
            Zaid[Tvarka[nr]].atversta = true;
            Zaid[Tvarka[nr]].atverusiosKortelesNr = prev;
        }
        else if (!Zaid[Zaid[prev].kt[1] - 1].atversta && Zaid[prev].kt[1] != 0)
        {
            Tvarka[nr] = Zaid[prev].kt[1] - 1;
            Zaid[Tvarka[nr]].atversta = true;
            Zaid[Tvarka[nr]].atverusiosKortelesNr = prev;
        }
            else
            {
                sk = prev;
                prev = Zaid[sk].atverusiosKortelesNr; //debug cout << sk << endl;
                fail = true;
            }
        if(!fail)
        {
            prev = Tvarka[nr]; //debug cout << Tvarka[sk]+1 << " " << prev+1 << endl;
            zodis += Zaid[prev].raide;
            sk++;
            nr++;
        }
    }
}

bool visosAtvertos(struct zaidejas Zaid[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if(!Zaid[i].atversta)
            return false;
    }
    return true;
}

void isvesti(string zodis, int n, struct zaidejas Zaid[], int Tvarka[])
{
    ofstream out("Rezultatai.txt");
    for (int i = 0; i < n; i++)
    {
        out << Zaid[Tvarka[i]].vardas << endl;
    }
    out << "Þodis: " << zodis << endl;
}
