#include <iostream>
#include <fstream>

using namespace std;

struct knyga
{
    string kod, autr, pav;
    int yr;
    double kn;
};

struct knygos
{
    int sk;
    knyga Knyg[100];
};

struct pirkejas
{
    string vard, Kod[100];
    int knyguSk, pirktuKnyguSk;
    double png;
    knyga PirktosKnygos[100];
};

struct pirkejai
{
    int sk;
    pirkejas Prk[100];
};

void skaitytiKnygas(struct knygos &kng);
void skaitytiPirkejus(struct pirkejai &pirk);
void pirkimas(struct knygos kng, struct pirkejai &pirk);
void salintiParduota(struct knygos &kng, int nr);
void isvesti(struct pirkejai pirk);
int knygaPagalKoda(struct knygos kng, string kod);
bool arEgzistuoja(struct knygos kng, string kod);
bool arIpirks(int nr, double png, struct knygos kng);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    pirkejai pirk;
    knygos kng;
    skaitytiKnygas(kng);
    skaitytiPirkejus(pirk);
    pirkimas(kng, pirk);
    isvesti(pirk);
    return 0;
}

void skaitytiKnygas(struct knygos &kng)
{
    ifstream in("Knygos.txt");
    in >> kng.sk;
    for (int i = 0; i < kng.sk; i++)
    {
        in >> kng.Knyg[i].kod >> kng.Knyg[i].autr >> kng.Knyg[i].pav >> kng.Knyg[i].yr >> kng.Knyg[i].kn;
    }
}

void skaitytiPirkejus(struct pirkejai &pirk)
{
    ifstream in("Pirkejai.txt");
    in >> pirk.sk;
    for (int i = 0; i < pirk.sk; i++)
    {
        in >> pirk.Prk[i].vard >> pirk.Prk[i].png;
        in >> pirk.Prk[i].knyguSk;
        for (int j = 0; j < pirk.Prk[i].knyguSk; j++)
        {
            in >> pirk.Prk[i].Kod[j];
        }
        pirk.Prk[i].pirktuKnyguSk = 0;
    }
}

void pirkimas(struct knygos kng, struct pirkejai &pirk)
{
    for (int i = 0; i < pirk.sk; i++)
    {
        for (int j = 0; j < pirk.Prk[i].knyguSk; j++)
        {
            int knygNr;
            bool yra = false; //ðvariau antram if'e
            if (arEgzistuoja(kng, pirk.Prk[i].Kod[j]))
            {
                knygNr = knygaPagalKoda(kng, pirk.Prk[i].Kod[j]);
                yra = true;
            }
            if (arIpirks(knygNr, pirk.Prk[i].png, kng) && yra)
            {
                pirk.Prk[i].png -= kng.Knyg[knygNr].kn;
                pirk.Prk[i].PirktosKnygos[pirk.Prk[i].pirktuKnyguSk] = kng.Knyg[knygNr];
                pirk.Prk[i].pirktuKnyguSk++;
                salintiParduota(kng, knygNr);
            }
        }
    }
}

int knygaPagalKoda(struct knygos kng, string kod)
{
    for (int i = 0; i < kng.sk; i++)
    {
        if (kod == kng.Knyg[i].kod)
            return i;
    }
}

bool arEgzistuoja(struct knygos kng, string kod)
{
    for (int i = 0; i < kng.sk; i++)
    {
        if (kod == kng.Knyg[i].kod)
            return true;
    }
    return false;
}

bool arIpirks(int nr, double png, struct knygos kng)
{
    if (png > kng.Knyg[nr].kn)
        return true;
    else
        return false;
}

void salintiParduota(struct knygos &kng, int nr)
{
    if (nr + 1 != kng.sk)
    {
        kng.Knyg[nr] = kng.Knyg[kng.sk - 1];
    }
    kng.Knyg[kng.sk - 1] = {};
    kng.sk--;
}

void isvesti(struct pirkejai pirk)
{
    ofstream out("Rezultatai.txt");
    for (int i = 0; i < pirk.sk; i++)
    {
        out << pirk.Prk[i].vard << endl;
        out << "------------------------------------------------------------" << endl;
        if (pirk.Prk[i].pirktuKnyguSk != 0)
        {
            for (int j = 0; j < pirk.Prk[i].pirktuKnyguSk; j++)
            {
                out << pirk.Prk[i].PirktosKnygos[j].kod << " " << pirk.Prk[i].PirktosKnygos[j].autr << " ";
                out << pirk.Prk[i].PirktosKnygos[j].pav << " " << pirk.Prk[i].PirktosKnygos[j].yr << " ";
                out << pirk.Prk[i].PirktosKnygos[j].kn << endl;
            }
        }
        out << "------------------------------------------------------------" << endl;
    }
}
