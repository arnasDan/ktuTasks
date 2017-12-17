#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>

using namespace std;

struct preke
{
    string kod;
    string pav;
    int galT;
    int n;
};

void skaityti(vector<preke> &Prekes);
void salintiParduotas(vector <preke> &Prekes);
void salintiPasibaigusias(vector <preke> &Prekes, vector <preke> &pasibaigusiosPrekes);
void rikiuoti(vector <preke> &Prekes);
void isvesti(vector <preke> Prekes, vector <preke> pasibaigusiosPrekes);

int main()
{
    vector <preke> Prekes;
    vector <preke> pasibaigusiosPrekes;
    skaityti(Prekes);
    salintiParduotas(Prekes);
    salintiPasibaigusias(Prekes, pasibaigusiosPrekes);
    rikiuoti(Prekes);
    isvesti(Prekes, pasibaigusiosPrekes);
    return 0;
}

void skaityti(vector <preke> &Prekes)
{
    int n;
    ifstream in("duom.csv");
    in >> n;
    in.ignore(1, '\n');
    Prekes.resize(n);
    for (int i = 0; i < n; i++)
    {
        getline(in, Prekes[i].kod, ',');
        getline(in, Prekes[i].pav, ',');
        in >> Prekes[i].galT;
        in.ignore(1, ',');
        in >> Prekes[i].n;
        in.ignore(1, '\n');
    }
}

void salintiParduotas(vector <preke> &Prekes)
{
    string kod;
    int sk, prdtN;
    ifstream in("parduota.csv");
    in >> sk;
    in.ignore(1, '\n');
    for (int i = 0; i < sk; i++)
    {
        getline(in, kod, ',');
        in >> prdtN;
        in.ignore(1, '\n');
        for (int j = 0; j < Prekes.size(); j++)
            if (Prekes[j].kod == kod)
            {
                Prekes[j].n -= prdtN;
                if (Prekes[j].n == 0)
                    Prekes.erase(Prekes.begin() + j);
                break;
            }
    }
}

void salintiPasibaigusias(vector <preke> &Prekes, vector <preke> &pasibaigusiosPrekes)
{
    int dabT = time(0);
    for (int i = 0; i < Prekes.size(); i++)
        if (Prekes[i].galT < dabT)
        {
            pasibaigusiosPrekes.push_back(Prekes[i]);
            Prekes.erase(Prekes.begin() + i);
            i--;
        }
}

void rikiuoti(vector <preke> &Prekes)
{
    preke tmp;
    for (int i = 0; i < Prekes.size() - 1; i++)
        for (int j = i; j < Prekes.size(); j++)
            if (Prekes[j].galT < Prekes[i].galT)
            {
                tmp = Prekes[i];
                Prekes[i] = Prekes[j];
                Prekes[j] = tmp;
            }
}

void isvesti(vector <preke> Prekes, vector <preke> pasibaigusiosPrekes)
{
    cout << "Pasibaigusio galiojimo laiko prekes:" << endl;
    for (int i = 0; i < pasibaigusiosPrekes.size(); i++)
        cout << pasibaigusiosPrekes[i].kod << ", " << pasibaigusiosPrekes[i].pav << ", " << pasibaigusiosPrekes[i].galT << ", " << pasibaigusiosPrekes[i].n << endl;
    ofstream out("rez.csv");
    out << Prekes.size() << endl;
    for (int i = 0; i < Prekes.size(); i++)
        out << Prekes[i].kod << ", " << Prekes[i].pav << ", " << Prekes[i].galT << ", " << Prekes[i].n << endl;
}
