#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;
struct trumpinimas
{
    char sutr[10];
    char reiksme[100];
    int lstr;
    int lrks;
};

void skaityti(int &n, char Tekst[], struct trumpinimas Trump[]);
void prailg(int &n, char Tekst[], struct trumpinimas Trump[], char IlgTekst[]);
void check(int n, struct trumpinimas Trump[], char Tekst[], int k, bool &paejo, int &nr);

int main()
{
    trumpinimas Trump[50];
    int n;
    char Tekst[500];
    char IlgTekst[500];
    skaityti(n, Tekst, Trump);
    prailg(n, Tekst, Trump, IlgTekst);
    ofstream out("Rezultatai3.txt");
    out << IlgTekst;
    return 0;
}
void skaityti(int &n, char Tekst[], struct trumpinimas Trump[])
{
    string sutr, reiksme;
    ifstream in("Duomenys3.txt");
    in >> n;
    in.ignore(1, '\n');
    for (int i = 0; i < n; i++)
    {
            getline(in, sutr, ' ');
            getline(in, reiksme, '\n');
            strcpy(Trump[i].sutr, sutr.c_str());
            strcpy(Trump[i].reiksme, reiksme.c_str());
            Trump[i].lstr = strlen(Trump[i].sutr);
            Trump[i].lrks = strlen(Trump[i].reiksme);
    }
    in.getline(Tekst, 500);
}
void prailg(int &n, char Tekst[], struct trumpinimas Trump[], char IlgTekst[])
{
    int nr, k = 0;
    bool paejo;
    strcpy (IlgTekst, Tekst);
    for (int i = 0; i < strlen(IlgTekst); i++)
    {
        if (Tekst[i] == '[')
        {
            check(n, Trump, Tekst, i, paejo, nr);
            if (paejo)
            {
                for (int j = 0; j < Trump[nr].lrks; j++)
                {

                    IlgTekst[k] = Trump[nr].reiksme[j];
                    k++;
                    //cout << Trump[nr].reiksme;
                }
                i += Trump[nr].lstr+1;
            }
        }
        else
        {
            IlgTekst[k] = Tekst[i];
            k++;
        }

    }
}
void check(int n, struct trumpinimas Trump[], char Tekst[], int k, bool &paejo, int &nr)
{
    int ilg = 0;
    bool pr = false;
    paejo = false;
    char Tikr[100];
    for (int i = k; i < strlen(Tekst); i++)
    {

        if (pr && Tekst[i] != ']')
        {
            Tikr[ilg] = Tekst[i];
            ilg++;
        }
        if (Tekst[i] == '[')
        {
            pr = true;
        }
        if (Tekst[i] == ']')
        {
            pr = false;
            //cout << Tikr << " ";
            for (int j = 0; j < n; j++)
                if(strcmp(Tikr, Trump[j].sutr) == 0)
                {
                    paejo = true;
                    nr = j;

                }
            memset(Tikr,'\0',ilg);
            ilg = 0;
            break;
        }

    }
}
