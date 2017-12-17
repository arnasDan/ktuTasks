#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

void skaitytiPrekes(struct preke Srs[], int &n);
void rikiuoti(struct preke Srs[], int n);
void pakeisti(struct preke Srs[], int &n);
void iterpti(struct preke Srs[], struct preke prk, int &n);
void salinti(struct preke Srs[], int &n, string pav);
void isvesti(struct preke Srs[], int n, ofstream& out);

struct preke
{
    string pav;
    double kain;
};

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    ofstream out("rezultatai.txt");
    int n = 0;
    preke Srs[100];
    skaitytiPrekes(Srs, n);
    rikiuoti(Srs, n);
    out << "Surikiuoti pradiniai duomenys" << endl;
    isvesti(Srs, n, out);
    pakeisti(Srs, n);
    out << endl << "Po pakeitimø" << endl;
    isvesti(Srs, n, out);
}

void skaitytiPrekes(struct preke Srs[], int &n)
{
    ifstream in("prekes.txt");
    while (!in.eof())
    {
        getline(in, Srs[n].pav, '-');
        Srs[n].pav = Srs[n].pav.substr(0, Srs[n].pav.length() - 1);
        if (Srs[n].pav == "") //jeigu tik tuscia eilute
            break;
        in.ignore(1, ' ');
        in >> Srs[n].kain;
        in.ignore(1, '\n');
        n++;
    }
}

void rikiuoti(struct preke Srs[], int n) //burbulo metodas
{
    preke tmp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i; j < n; j++)
            if (Srs[j].kain > Srs[i].kain || (Srs[j].kain == Srs[i].kain && Srs[j].pav < Srs[i].pav))
            {
                tmp = Srs[i];
                Srs[i] = Srs[j];
                Srs[j] = tmp;
            }
}

void pakeisti(struct preke Srs[], int &n)
{
    ifstream in("pakeitimai.txt");
    preke tmp;
    string plusmin;
    while (!in.eof())
    {
        getline(in, plusmin, ' ');
        if (plusmin == "") //jeigu tik tuscia eilute
            break;
        getline(in, tmp.pav, '-');
        tmp.pav = tmp.pav.substr(0, tmp.pav.length() - 1);
        in.ignore(1, ' ');
        in >> tmp.kain;
        in.ignore(1, '\n');
        if (plusmin == "+")
            iterpti(Srs, tmp, n);
        else if (plusmin == "-")
            salinti(Srs, n, tmp.pav);
    }
}

void iterpti(struct preke Srs[], struct preke prk, int &n)
{
    int pos;
    for (int i = 0; i < n; i++)
    {
        if (Srs[i].kain <= prk.kain)
        {
            pos = i;
            for (int j = pos; j < n; j++)
                if (Srs[j].kain == prk.kain && prk.pav > Srs[j].pav)
                    pos++;
                else if (Srs[j].kain != prk.kain)
                    break;
            break;
        }
        if (i + 1 == n)
            pos = i + 1;
    }
    for (int i = n; i > pos; i--)
        Srs[i] = Srs[i - 1];
    Srs[pos] = prk;
    n++;
}

void salinti(struct preke Srs[], int &n, string pav)
{
    preke tuscias;
    int pos;
    for (int i = 0; i < n; i++)
        if (Srs[i].pav == pav)
        {
            pos = i;
            break;
        }
    if (pos + 1 != n)
        for (int i = pos; i < n; i++)
            Srs[i] = Srs[i + 1];
    Srs[n - 1] = tuscias;
    n--;
}

void isvesti(struct preke Srs[], int n, ofstream& out)
{
    out << "---------------------------------" << endl;
    out << "|     Pavadinimas       | Kaina |" << endl;
    out << "---------------------------------" << endl;
    for (int i = 0; i < n; i++)
    {
        out << "|" << setw(5) << ' ' << Srs[i].pav << setw(18 - Srs[i].pav.length()) << ' ' << '|' << setw(7) << fixed << setprecision(2) << Srs[i].kain << '|' << endl;
        out << "---------------------------------" << endl;
    }
}

