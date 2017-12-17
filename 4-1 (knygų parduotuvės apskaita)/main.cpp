#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

struct diena
{
    int nr;
    int kng;
    int pln;
};

void skaityti(struct diena Dien[31], int &n);
void pelningosDienos(struct diena Dien[31], struct diena Peln[31], int n, int &plnN);
void pajamuDiagrama(struct diena Dien[31], int n, ofstream& out);
void pelnoLentele(struct diena Peln[31], int plnN, ofstream& out);
int pelningiausia(struct diena Dien[31], int n);
int maziausiaiPelninga(struct diena Dien[31], int n);

int main()
{
    int n = 0, plnN = 0;
    diena Dien[31];
    diena Peln[31];
    skaityti(Dien, n);
    ofstream out("Rezultatai1.txt");
    pelningosDienos(Dien, Peln, n, plnN);
    pajamuDiagrama(Dien, n, out);
    out << endl;
    pelnoLentele(Peln, plnN, out);
    return 0;
}

void skaityti(struct diena Dien[31], int &n)
{
    ifstream in("Duomenys1.txt");
    while (!in.eof())
    {
        in >> Dien[n].nr >> Dien[n].kng >> Dien[n].pln;
        n++;
    }
}

void pajamuDiagrama(struct diena Dien[31], int n, ofstream& out)
{
    out << setw(12) << ' ' << "Pajamu_diagrama" << endl;
    out << "Dienos" << endl;
    string grfk(Dien[0].pln, '_');
    out << setw(6) << ' ' << grfk << endl;
    int trp;
    for (int i = 0; i < n; i++)
    {
        if (i + 1 <= 10)
            trp = 5;
        else
            trp = 4;
        out << i + 1 << setw(trp) << ' ';
        if (Dien[i].pln < Dien[i + 1].pln && i + 1 != n)
            trp = Dien[i].pln + Dien[0].pln;
        else
            trp = Dien[i].pln;
        string grfk(trp, '_');
        grfk.insert(Dien[i].pln, "|");
        out << grfk << endl;
    }
}

void pelnoLentele(struct diena Peln[31], int plnN, ofstream& out)
{
    out << setw(12) << ' ' << "Pelningos_dienos" << endl;
    out << "|----------|------------|-------------|" << endl;
    out << "|  Diena   |   Knygos   |   Pajamos   |" << endl;
    out << "|----------|------------|-------------|" << endl;
    for (int i = 0; i < plnN; i++)
    {
        out << '|' << setw(6) << Peln[i].nr << setw(5) << '|' << setw(7) << Peln[i].kng << setw(6) << '|' << setw(7) << Peln[i].pln << setw(7) << '|' << endl;
    }
    out << "|----------|------------|-------------|" << endl;
}

void pelningosDienos(struct diena Dien[31], struct diena Peln[31], int n, int &plnN)
{
    double vid = (double) (Dien[maziausiaiPelninga(Dien, n)].pln + Dien[pelningiausia(Dien, n)].pln) / 2;
    for (int i = 0; i < n; i++)
        if (Dien[i].pln >= vid)
        {
            Peln[plnN] = Dien[i];
            plnN++;
        }
}

int pelningiausia(struct diena Dien[31], int n)
{
    int max = 0;
    for (int i = 0; i < n; i++)
    {
        if (Dien[i].pln > Dien[max].pln)
            max = i;
        if (Dien[i].pln == Dien[max].pln && Dien[i].kng > Dien[max].kng)
            max = i;
    }
    return max;
}

int maziausiaiPelninga(struct diena Dien[31], int n)
{
    int min = 0;
    for (int i = 0; i < n; i++)
    {
        if (Dien[i].pln < Dien[min].pln)
            min = i;
        if (Dien[i].pln == Dien[min].pln && Dien[i].kng < Dien[min].kng)
            min = i;
    }
    return min;
}
