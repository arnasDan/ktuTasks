#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct zaidejas
{
    string vard;
    string pvrd;
    int tsk;
};

void skaityti(vector <zaidejas> &Zaid, string &krt);
void zaisti(vector <zaidejas> &Zaid, string krt);
void isvesti(vector <zaidejas> &Zaid);
void pridetiTaskus(vector <zaidejas> &Zaid);
void salintiZaideja(vector <zaidejas> &Zaid, vector <zaidejas> &iskrtZaid);
void grazintiZaideja(vector <zaidejas> &Zaid, vector <zaidejas> &iskrtZaid);
void rikiuotiMinMax(vector <zaidejas> &Zaid);
void rikiuotiPagalVardus(vector <zaidejas> &Zaid);
void rikiuotiPagalPavardes(vector <zaidejas> &Zaid);
zaidejas laimetojas(vector <zaidejas> &Zaid);

int main()
{
    string krt;
    vector <zaidejas> Zaid;
    skaityti(Zaid, krt);
    zaisti(Zaid, krt);
    isvesti(Zaid);
    return 0;
}

void skaityti(vector <zaidejas> &Zaid, string &krt)
{
    int n;
    ifstream in("Duomenys.txt");
    in >> n;
    Zaid.resize(n);
    for (int i = 0; i < n; i++)
    {
        in >> Zaid[i].vard >> Zaid[i].pvrd;
        Zaid[i].tsk = 100;
    }
    in >> krt;
}

void zaisti(vector <zaidejas> &Zaid, string krt)
{
    vector <zaidejas> iskrtZaid;
    for (int i = 0; i < krt.length(); i++)
    {
        if (krt[i] == 'P')
            rikiuotiPagalPavardes(Zaid);
        if (krt[i] == 'V')
            rikiuotiPagalVardus(Zaid);
        if (krt[i] == '~')
            rikiuotiMinMax(Zaid);
        if (krt[i] == '-')
            salintiZaideja(Zaid, iskrtZaid);
        if (krt[i] == '+')
            grazintiZaideja(Zaid, iskrtZaid);
        pridetiTaskus(Zaid);
        /*/DEBUG
        for (int j = 0; j < Zaid.size(); j++)
            cout << Zaid[j].vard << " " << Zaid[j].tsk << endl;
        cout << endl;
        /*/
    }
}

void isvesti(vector <zaidejas> &Zaid)
{
    ofstream out("Laimetojas.txt");
    zaidejas laim;
    laim = laimetojas(Zaid);
    out << laim.vard << " " << laim.pvrd << " " << laim.tsk << endl;
}

void pridetiTaskus(vector <zaidejas> &Zaid)
{
    for (int i = 0; i < Zaid.size(); i++)
        Zaid[i].tsk += (Zaid.size() - i) * 10;
}

void salintiZaideja(vector <zaidejas> &Zaid, vector <zaidejas> &iskrtZaid)
{
    iskrtZaid.push_back(Zaid.back());
    Zaid.pop_back();
}

void grazintiZaideja(vector <zaidejas> &Zaid, vector <zaidejas> &iskrtZaid) //grazina i pabaiga
{
    if (iskrtZaid.size() != 0)
    {
        Zaid.push_back(iskrtZaid.back());
        iskrtZaid.pop_back();
    }
}

void rikiuotiMinMax(vector <zaidejas> &Zaid)
{
    vector <zaidejas> Tmp(Zaid);
    zaidejas tmp;
    for (int i = 0; i < Zaid.size() - 1; i++)
        for (int j = i; j < Zaid.size(); j++)
            if (Zaid[j].pvrd < Zaid[i].pvrd)
            {
                tmp = Zaid[i];
                Zaid[i] = Zaid[j];
                Zaid[j] = tmp;
            }
    for (int i = 1; i <= Zaid.size(); i++)
        if (i % 2 != 0)
        {
            Zaid[i - 1] = Tmp.front();
            Tmp.erase(Tmp.begin());
        }
        else
        {
            Zaid[i - 1] = Tmp.back();
            Tmp.pop_back();
        }
}

void rikiuotiPagalPavardes(vector <zaidejas> &Zaid)
{
    zaidejas tmp;
    for (int i = 0; i < Zaid.size() - 1; i++)
        for (int j = i; j < Zaid.size(); j++)
            if (Zaid[j].pvrd < Zaid[i].pvrd)
            {
                tmp = Zaid[i];
                Zaid[i] = Zaid[j];
                Zaid[j] = tmp;
            }
}

void rikiuotiPagalVardus(vector <zaidejas> &Zaid)
{
    zaidejas tmp;
    for (int i = 0; i < Zaid.size() - 1; i++)
        for (int j = i; j < Zaid.size(); j++)
            if (Zaid[j].vard < Zaid[i].vard)
            {
                tmp = Zaid[i];
                Zaid[i] = Zaid[j];
                Zaid[j] = tmp;
            }
}

zaidejas laimetojas(vector <zaidejas> &Zaid)
{
    int max = 0;
    for (int i = 0; i < Zaid.size(); i++)
        if (Zaid[i].tsk > Zaid[max].tsk)
            max = i;
    return Zaid[max];
}
