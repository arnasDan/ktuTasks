#include <iostream>
#include <fstream>

using namespace std;

struct dalyvis
{
    string vard;
    string pvrd;
    int tsk;
    int uzd;
};

void skaityti(struct dalyvis Dlv[], int &dlvSk);
void rezultatai(struct dalyvis Dlv[], struct dalyvis Rez[], int dlvSk);
void isvesti(struct dalyvis Rez[]);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    int dlvSk;
    dalyvis Dlv[20];
    dalyvis Rez[4];
    skaityti(Dlv, dlvSk);
    rezultatai(Dlv, Rez, dlvSk);
    isvesti(Rez);
    return 0;
};

void skaityti(struct dalyvis Dlv[], int &dlvSk)
{
    ifstream in("Duomenys2.txt");
    in >> dlvSk;
    for (int i = 0; i < dlvSk; i++)
    {
        in >> Dlv[i].vard >> Dlv[i].pvrd;
        Dlv[i].uzd = 0;
        Dlv[i].tsk = 0;
        for (int j = 0; j < 5; j++)
        {
            int tmp;
            in >> tmp;
            Dlv[i].tsk += tmp;
            if (tmp == 100)
                Dlv[i].uzd++;
        }
    }
}

void rezultatai(struct dalyvis Dlv[], struct dalyvis Rez[], int dlvSk)
{
    dalyvis tmp;
    for (int i = 0; i < dlvSk - 1; i++)
        for (int j = i + 1; j < dlvSk; j++)
            if (Dlv[j].uzd > Dlv[i].uzd || (Dlv[j].uzd == Dlv[i].uzd && Dlv[j].tsk > Dlv[i].tsk))
            {
                tmp = Dlv[i];
                Dlv[i] = Dlv[j];
                Dlv[j] = tmp;
            }
    for (int i = 0; i < 3; i++)
        Rez[i] = Dlv[i];
    Rez[3] = Dlv[dlvSk - 1];
}

void isvesti(struct dalyvis Rez[])
{
    ofstream out("Rezultatai2.txt");
    out << "Konkurso prizininkai:" << endl;
    for (int i = 0; i < 3; i++)
        out << Rez[i].vard << " " << Rez[i].pvrd << " " << Rez[i].tsk << " " << Rez[i].uzd << endl;
    out << "Prasèiausiai pasirodë:" << endl;
    out << Rez[3].vard << " " << Rez[3].pvrd << " " << Rez[3].tsk << " " << Rez[3].uzd << endl;
}
