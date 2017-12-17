#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <cmath>

using namespace std;

struct apskritis
{
    string pav;
    double lauz;
    double panaudLauz;
};

void skaityti(vector <apskritis> &Apskr);
void isvesti(vector <apskritis> Apskr);
void rusiuoti(vector <apskritis> &Apskr);
void iterpti(vector <apskritis> &Apskr, struct apskritis itrp);
double suma(vector <apskritis> Apskr, double apskritis::*member);
double skirtumuVidurkis(vector <apskritis> Apskr);
apskritis didziausia(vector <apskritis> Apskr, double apskritis::*member);
apskritis maziausia(vector <apskritis> Apskr, double apskritis::*member);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    vector <apskritis> Apskr;
    skaityti(Apskr);
    isvesti(Apskr);
    return 0;
}

void skaityti(vector <apskritis> &Apskr)
{
    int n;
    ifstream in("lauzas.txt");
    in >> n;
    Apskr.resize(n);
    for (int i = 0; i < n; i++)
        in >> Apskr[i].pav;
    for (int i = 0; i < n; i++)
        in >> Apskr[i].lauz;
    for (int i = 0; i < n; i++)
        in >> Apskr[i].panaudLauz;
}

void isvesti(vector <apskritis> Apskr)
{
    apskritis tmp;
    string trp = "---------------------------------------------\n";
    int nr;
    ofstream out("lauzasrez.txt");
    out << fixed << setprecision(1) << suma(Apskr, &apskritis::lauz) << endl << trp;
    out << fixed << setprecision(1) << suma(Apskr, &apskritis::panaudLauz) << endl << trp;
    tmp = didziausia(Apskr, &apskritis::lauz);
    out << fixed << setprecision(1) << tmp.pav << " " << tmp.lauz << endl << trp;
    tmp = maziausia(Apskr, &apskritis::panaudLauz);
    out << fixed << setprecision(1) << tmp.pav << " " << tmp.panaudLauz << endl << trp;
    out << fixed << setprecision(1) << skirtumuVidurkis(Apskr) << endl << trp;
    rusiuoti(Apskr);
    for (int i = 0; i < Apskr.size(); i++)
        out << Apskr[i].pav << " " << Apskr[i].panaudLauz << endl;
    out << trp;
    iterpti(Apskr, tmp);
    for (int i = 0; i < Apskr.size(); i++)
        out << Apskr[i].pav << " " << Apskr[i].panaudLauz << endl;
}

void iterpti(vector <apskritis> &Apskr, struct apskritis itrp)
{
    int pos = ceil(Apskr.size() / 2.0);
    Apskr.insert(Apskr.begin() + pos, itrp);
}

void rusiuoti(vector <apskritis> &Apskr)
{
    for (int i = 0; i < Apskr.size() - 1; i++)
        for (int j = i; j < Apskr.size(); j++)
            if (Apskr[i].panaudLauz < Apskr[j].panaudLauz || (Apskr[i].panaudLauz == Apskr[j].panaudLauz && Apskr[i].pav < Apskr[j].pav))
                swap(Apskr[i], Apskr[j]);
}

double suma(vector <apskritis> Apskr, double apskritis::*member)
{
    double sum = 0;
    for (int i = 0; i < Apskr.size(); i++)
        sum += Apskr[i].*member;
    return sum;
}

double skirtumuVidurkis(vector <apskritis> Apskr)
{
    double sum = 0;
    for (int i = 0; i < Apskr.size(); i++)
        sum += abs(Apskr[i].lauz - Apskr[i].panaudLauz);
    return sum / Apskr.size();
}

apskritis didziausia(vector <apskritis> Apskr, double apskritis::*member)
{
    int max = 0;
    for (int i = 0; i < Apskr.size(); i++)
        if (Apskr[i].*member > Apskr[max].*member)
            max = i;
    return Apskr[max];
}

apskritis maziausia(vector <apskritis> Apskr, double apskritis::*member)
{
    int min = 0;
    for (int i = Apskr.size() - 1; i >= 0; i--)
        if (Apskr[i].*member < Apskr[min].*member)
            min = i;
    return Apskr[min];
}
