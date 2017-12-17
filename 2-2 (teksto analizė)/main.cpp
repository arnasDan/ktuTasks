#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct zodis
{
    string tkst;
    int sk;
};

string skaityti();
void isskirstymas(struct zodis Zodz[], int &zodSk, string tekstas);
void pasikartoja(string zodis, struct zodis Zodz[], int zodSk, bool &kartoj, int &i);
int zodziuSkaicius(string zodis, string tekstas);
void isvesti(int zodSk, struct zodis Zodz[]);

int main()
{
    zodis Zodz[1000];
    int zodSk = 0;
    setlocale(LC_ALL, "Lithuanian");
    string tekstas = skaityti();
    isskirstymas(Zodz, zodSk, tekstas);
    isvesti(zodSk, Zodz);
    return 0;
}

string skaityti()
{
    string tmp;
    ifstream in("Duomenys.txt");
    getline(in, tmp);
    return tmp;
}

void isskirstymas(struct zodis Zodz[], int &zodSk, string tekstas)
{
    bool kartoj;
    string tmp;
    int prad = 0, pab = 0, nr;
    while (pab < tekstas.length()-1)
    {
        pab = tekstas.find_first_of(" .,;:–!?()", prad);
        tmp = tekstas.substr(prad, pab-prad);
        if (tekstas[pab+1] == ' ')
            pab++;
        pasikartoja(tmp, Zodz, zodSk, kartoj, nr);
        if (!kartoj)
        {
            Zodz[zodSk].tkst = tmp;
            Zodz[zodSk].sk = 1;
            zodSk++;
            Zodz[nr].sk = zodziuSkaicius(tmp, tekstas);
        }
        prad = pab+1;
    }
}

void pasikartoja(string zodis, struct zodis Zodz[], int zodSk, bool &kartoj, int &i)
{
    for (i = 0; i < zodSk; i++)
    {
        if (zodis == Zodz[i].tkst)
        {
            kartoj = true;
            return;
        }
    }
    kartoj = false;
}

int zodziuSkaicius(string zodis, string tekstas) //is esmes butu galima anoj funkcijoj skaiciuot paprasciau, bet reikalavimuose buvo funkcija zodziam skaiciuot..:))
{
    string patr = " .,;:–!?()";
    int pos = 0, nr = 0;
    while (tekstas.find(zodis, pos) != string::npos)
    {
        pos = tekstas.find(zodis, pos);
        if (tekstas[pos-1] == ' ' || pos == 0)
            for (int i = 0; i < patr.length(); i++)
                if (tekstas[pos+zodis.length()] == patr[i])
                    nr++;
        if (pos + zodis.length() >= tekstas.length()) //jeigu gale nera skyrybos zenklo
            nr++;
        pos += zodis.length();
    }
    return nr;
}

void isvesti(int zodSk, struct zodis Zodz[])
{
    ofstream out("Rezultatai.txt");
    out << "Ið viso skirtingø þodþiø " << zodSk << endl;
    for (int i = 0; i < zodSk; i++)
    {
        out << i+1 << ". " << Zodz[i].tkst << " " << Zodz[i].sk << endl;
    }
}
