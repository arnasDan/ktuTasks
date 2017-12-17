#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

struct knyga
{
    string kod;
    string autr;
    string pav;
    int metai;
    double kaina;
};

struct knygos //is esmes nereikalingas visiskai, jeigu su vektoriais, bet reikalavimuose..
{
    vector <knyga> Kng;
    int n;
};

void skaityti(struct knygos &k, string &duomFail);
void isvesti(struct knygos k);
void salinti(struct knygos &k);
void iterpti(struct knygos &k);
void rikiuoti(struct knygos &k);
void rikiuotiMazejanciai(struct knygos &k);
void rikiuotiDidejanciai(struct knygos &k);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    knygos k;
    k.n = 0;
    bool baigti = false;
    string kmnd, duomFail;
    while (!baigti)
    {
        cout << "Skaityti duomenis is failo(skaityti)" << endl;
        cout << "Rikiuoti duomenis(rikiuoti)" << endl;
        cout << "Iterpti nauja irasa(iterpti)" << endl;
        cout << "Salinti irasa(salinti)" << endl;
        cout << "Baigti(baigti)" << endl;
        cout << "Iveskite komanda: ";
        cin >> kmnd;
        if (kmnd == "skaityti")
            skaityti(k, duomFail);
        else if (kmnd == "baigti")
            baigti = true;
        else if (kmnd == "salinti")
            salinti(k);
        else if (kmnd == "rikiuoti")
            rikiuoti(k);
        else if (kmnd == "iterpti")
            iterpti(k);
        else cout << "Komanda nerasta!" << endl;
        cout << endl;
    }
    return 0;
}

void skaityti(struct knygos &k, string &duomFail)
{
    string yn = "Y";
    while (yn == "Y")
    {
        cout << "Naudoti nauja duomenu faila? (Y/N): ";
        cin >> yn;
        if (yn == "Y" || yn == "N")
        {
            if (yn == "N" && duomFail.empty())
            {
                cout << "Dar neivestas joks duomenu failas!" << endl;
                yn = "Y";
            }
            if (yn == "Y")
            {
                cout << "Iveskite duomenu failo varda: ";
                cin >> duomFail;
                ifstream in(duomFail.c_str());
                if (in.good())
                {
                    in >> k.n;
                    k.Kng.resize(k.n);
                    for (int i = 0; i < k.n; i++)
                        in >> k.Kng[i].kod >> k.Kng[i].autr >> k.Kng[i].pav >> k.Kng[i].metai >> k.Kng[i].kaina;
                    isvesti(k);
                }
                else
                    cout << "Netinkamas failas/Failas nerastas!" << endl;
            }
        }
        else
        {
            cout << "(Y/N)!" << endl;
            yn = "Y";
        }
    }
}

void isvesti(struct knygos k)
{
    cout << endl;
    cout << "|-----------|--------------------|-----------------------------|-------|-----------|" << endl;
    cout << "|   Kodas   |      Autorius      |         Pavadinimas         | Metai |   Kaina   |" << endl;
    cout << "|-----------|--------------------|-----------------------------|-------|-----------|" << endl;
    for (int i = 0; i < k.n; i++)
    {
        cout << "|   " << setw(8) << left << k.Kng[i].kod << "|   " << setw(17) << k.Kng[i].autr << "|   ";
        cout << setw(26) << k.Kng[i].pav << "| "  << setw(6) << k.Kng[i].metai << "|   " << setw(8) << left << fixed << setprecision(2) << k.Kng[i].kaina << "|" << endl;
        cout << "|-----------|--------------------|-----------------------------|-------|-----------|" << endl;
    }
}

void salinti(struct knygos &k)
{
    string yn = "Y", kod;
    if (k.n > 0)
        while (yn == "Y")
        {
            cout << "Iveskite norimos pasalinti knygos koda: ";
            cin >> kod;
            for (int i = 0; i < k.n; i++)
            {
                if (k.Kng[i].kod == kod)
                {
                    k.Kng.erase(k.Kng.begin() + i);
                    k.n--;
                    isvesti(k);
                    break;
                }
                if (i + 1 == k.n)
                    cout << "Knyga su nurodytu kodu nerasta!" << endl;
            }
            while (true)
            {
                cout << "Salinti kita knyga? (Y/N): ";
                cin >> yn;
                if (yn == "Y" || yn == "N")
                    break;
                else
                    cout << "(Y/N)!" << endl;
            }
        }
    else
        cout << "Nera ka salinti!" << endl;
}

void iterpti(struct knygos &k)
{
    string yn = "Y";
    knyga tmp;
    while (yn == "Y")
    {
        cout << "Iveskite norimos iterpti knygos koda: ";
        cin >> tmp.kod;
        cout << "Iveskite autoriu: ";
        cin >> tmp.autr;
        cout << "Iveskite pavadinima: ";
        cin >> tmp.pav;
        while(true)
        {
            cout << "Iveskite isleidimo metus: ";
            cin >> tmp.metai;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits <int> ::max(), '\n');
                cout << "Iveskite skaiciu!" << endl;
            }
            else
                break;
        }
        cin.ignore(numeric_limits <int> ::max(), '\n');
        while(true)
        {
            cout << "Iveskite kaina: ";
            cin >> tmp.kaina;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(numeric_limits <double> ::max(), '\n');
                cout << "Iveskite skaiciu!" << endl;
            }
            else
                break;
        }
        cin.ignore(numeric_limits <double> ::max(), '\n');
        k.Kng.push_back(tmp);
        k.n++;
        isvesti(k);
        while (true)
        {
            cout << "Prideti dar viena knyga? (Y/N): ";
            cin >> yn;
            if (yn == "Y" || yn == "N")
                break;
            else
                cout << "(Y/N)!" << endl;
        }
    }
}

void rikiuoti(struct knygos &k)
{
    string dm;
    if (k.n > 0)
    {
        while(true)
        {
            cout << "Rusiuoti didejanciai ar mazejanciai? (D/M): ";
            cin >> dm;
            if (dm == "D" || dm == "M")
                break;
            else
                cout << "(D/M)!" << endl;
        }
        if (dm == "D")
            rikiuotiDidejanciai(k);
        else
            rikiuotiMazejanciai(k);
    }
    else
        cout << "Nera ka rikiuoti!" << endl;
}

void rikiuotiDidejanciai(struct knygos &k)
{
    knyga tmp;
    for (int i = 0; i < k.n - 1; i++)
        for (int j = i; j < k.n; j++)
            if (k.Kng[j].kaina < k.Kng[i].kaina || (k.Kng[j].kaina == k.Kng[i].kaina && k.Kng[j].pav < k.Kng[i].pav))
            {
                tmp = k.Kng[i];
                k.Kng[i] = k.Kng[j];
                k.Kng[j] = tmp;
            }
    isvesti(k);
}

void rikiuotiMazejanciai(struct knygos &k)
{
    knyga tmp;
    for (int i = 0; i < k.n - 1; i++)
        for (int j = i; j < k.n; j++)
            if (k.Kng[j].kaina > k.Kng[i].kaina || (k.Kng[j].kaina == k.Kng[i].kaina && k.Kng[j].pav < k.Kng[i].pav))
            {
                tmp = k.Kng[i];
                k.Kng[i] = k.Kng[j];
                k.Kng[j] = tmp;
            }
    isvesti(k);
}
