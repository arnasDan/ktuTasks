#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>

using namespace std;

struct sritis
{
    string pav;
    double sum;
};

void skaityti(vector <sritis> &Srt, vector <sritis> &Rmj);
void isvesti(vector <sritis> Srt, vector <sritis> Rmj);
void rikiuoti(vector <sritis> &Srt);
void salintiMaziausia(vector <sritis> &Srt, struct sritis min);
double suma(vector <sritis> Vktr);
sritis didziausia(vector <sritis> Vktr);
sritis maziausia(vector <sritis> Vktr);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    vector <sritis> Srt;
    vector <sritis> Rmj;
    skaityti(Srt, Rmj);
    isvesti(Srt, Rmj);
    return 0;
}

void skaityti(vector <sritis> &Srt, vector <sritis> &Rmj)
{
    int nP, nS, endPos;
    double tmp;
    char Pav[18];
    ifstream in("parama.txt");
    in >> nP >> nS;
    Srt.resize(nS);
    Rmj.resize(nP);
    for (int i = 0; i < nP; i++)
    {
        in >> Rmj[i].pav;
        Rmj[i].sum = 0;
    }
    in.ignore();
    for (int i = 0; i < nS; i++)
    {
        in.get(Pav, 18); //skiriama ne 20, o 18..
        Srt[i].pav = Pav;
        endPos = Srt[i].pav.find("  ");
        Srt[i].pav = Srt[i].pav.substr(0, endPos);
        for (int j = 0; j < nP; j++)
        {
            in >> tmp;
            Rmj[j].sum += tmp;
            Srt[i].sum += tmp;
        }
        in.ignore(5, '\n');
    }
}

void isvesti(vector <sritis> Srt, vector <sritis> Rmj)
{
    ofstream out("paramarez.txt"); //reikalavimuose "paramairez", bet turbut klaida
    string trp = "---------------------------------------------\n";
    sritis tmp;
    tmp = didziausia(Rmj);
    out << tmp.pav << " " << tmp.sum << endl << trp;
    tmp = maziausia(Srt);
    out << tmp.pav << " " << tmp.sum << endl << trp;
    out << suma(Rmj) << endl << trp;
    out << fixed << setprecision(1) << suma(Srt) / Srt.size() << endl << trp;
    rikiuoti(Srt);
    for (int i = 0; i < Srt.size(); i++)
        out << setw(18) << left << Srt[i].pav << Srt[i].sum << endl;
    salintiMaziausia(Srt, tmp);
    out << trp;
    for (int i = 0; i < Srt.size(); i++)
        out << setw(18) << left << Srt[i].pav << Srt[i].sum << endl;
}

void rikiuoti(vector <sritis> &Srt)
{
    for (int i = 0; i < Srt.size() - 1; i++)
        for (int j = i; j < Srt.size(); j++)
            if (Srt[i].sum < Srt[j].sum || (Srt[i].sum == Srt[j].sum && Srt[i].pav < Srt[j].pav))
                swap(Srt[i], Srt[j]);
}

void salintiMaziausia(vector <sritis> &Srt, struct sritis min)
{
    for (int i = 0; i < Srt.size(); i++)
        if (min.pav == Srt[i].pav)
        {
            Srt.erase(Srt.begin() + i);
            break;
        }
}

double suma(vector <sritis> Vktr)
{
    double sum = 0;
    for (int i = 0; i < Vktr.size(); i++)
        sum += Vktr[i].sum;
    return sum;
}

sritis didziausia(vector <sritis> Vktr)
{
    int max = 0;
    for (int i = Vktr.size() - 1; i >= 0; i--)
        if (Vktr[i].sum > Vktr[max].sum)
            max = i;
    return Vktr[max];
}

sritis maziausia(vector <sritis> Vktr)
{
    int min = 0;
    for (int i = 0; i < Vktr.size(); i++)
        if (Vktr[i].sum < Vktr[min].sum)
            min = i;
    return Vktr[min];
}
