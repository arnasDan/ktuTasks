#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

struct tersalas
{
    string pav;
    double K[100];
    double sum;
};

void skaityti(vector <tersalas> &Ters, int &mPr, int &m);
void isvesti(vector <tersalas> Ters, int mPr, int m);
void isvestiSarasa(vector <tersalas> Ters, ofstream &out);
void rikiuoti(vector <tersalas> &Ters);
void salinti(vector <tersalas> &Ters, int m);
int didziausia(double K[], int m);
int maziausia(double K[], int m);
double sumaMetu(vector <tersalas> Ters, int m);
double sumaRusies(double K[], int m);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    int mPr, m;
    vector <tersalas> Ters;
    skaityti(Ters, mPr, m);
    isvesti(Ters, mPr, m);
    return 0;
}

void skaityti(vector <tersalas> &Ters, int &mPr, int &m)
{
    int n, endPos;
    char Pav[30];
    ifstream in("tersalai.txt");
    in >> n >> mPr >> m;
    in.ignore();
    Ters.resize(n);
    for (int i = 0; i < n; i++)
    {
        in.get(Pav, 30);
        Ters[i].pav = Pav;
        endPos = Ters[i].pav.find("  ");
        Ters[i].pav = Ters[i].pav.substr(0, endPos);
        for (int j = 0; j < m; j++)
            in >> Ters[i].K[j];
        Ters[i].sum = sumaRusies(Ters[i].K, m);
        in.ignore();
    }
}

void isvesti(vector <tersalas> Ters, int mPr, int m)
{
    ofstream out("tersalairez.txt");
    string trp = "---------------------------------------------\n";
    for (int i = 0; i < Ters.size(); i++)
        out << setw(30) << left << Ters[i].pav << mPr + didziausia(Ters[i].K, m) << " " << mPr + maziausia(Ters[i].K, m) << endl;
    out << trp;
    double sum = 0;
    for (int i = 0; i < m; i++)
    {
        out << mPr + i << " " << fixed << setprecision(1) << sumaMetu(Ters, i) << endl;
        sum += sumaMetu(Ters, i);
    }
    out << trp << fixed << setprecision(1) << sum / m << endl << trp;
    rikiuoti(Ters);
    isvestiSarasa(Ters, out);
    out << trp;
    salinti(Ters, m);
    isvestiSarasa(Ters, out);

}

void isvestiSarasa(vector <tersalas> Ters, ofstream &out)
{
    for (int i = 0; i < Ters.size(); i++)
        out << setw(30) << left << Ters[i].pav << fixed << setprecision(1) << Ters[i].sum << endl;
}

void rikiuoti(vector <tersalas> &Ters)
{
    tersalas tmp;
    for (int i = 0; i < Ters.size() - 1; i++)
        for (int j = i; j < Ters.size(); j++)
            if (Ters[i].sum > Ters[j].sum || (Ters[i].sum == Ters[j].sum && Ters[i].pav < Ters[j].pav))
            {
                tmp = Ters[i];
                Ters[i] = Ters[j];
                Ters[j] = tmp;
            }
}

void salinti(vector <tersalas> &Ters, int m)
{
    int max = 0;
    for (int i = m - 1; i >= 0; i--)
        if (Ters[i].sum > Ters[max].sum)
        {
            max = i;
            break;
        }
    Ters.erase(Ters.begin() + max);
}

int didziausia(double K[], int m)
{
    int max = 0;
    for (int i = 0; i < m; i++)
        if (K[i] > K[max])
        {
            max = i;
            return max;
        }
}

int maziausia(double K[], int m)
{
    int min = 0;
    for (int i = m - 1; i >= 0; i--)
        if (K[i] < K[min])
        {
            min = i;
            return min;
        }
}

double sumaRusies(double K[], int m)
{
    double sum = 0;
    for (int i = 0; i < m; i++)
        sum += K[i];
    return sum;
}

double sumaMetu(vector <tersalas> Ters, int m)
{
    double sum = 0;
    for (int i = 0; i < Ters.size(); i++)
        sum += Ters[i].K[m];
    return sum;
}
