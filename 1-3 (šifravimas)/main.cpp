#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

using namespace std;

struct sifras
{
    char raid[2];
    char simb[2];
    int ascii;
    int kodascii[10];
};
struct zinute
{
    string vardas;
    int diena;
    char Tekstas[500];
};

void sifrasSkaityti(struct sifras Sifras[]);
void zinuteSkaityti(struct zinute Zinute[], int &n);
void sifravimas(struct zinute Zinute[], struct sifras Sifras[], int n);
void issifravimas(struct zinute Zinute[], struct sifras Sifras[], int n);
void isvesti(struct zinute Zinute[], struct sifras Sifras[], int n);
int faktorialas(int diena);

int main()
{
    int n;
    setlocale(LC_ALL, "English_Australia.1252");
    zinute Zinute[10];
    sifras Sifras[25];
    sifrasSkaityti(Sifras);
    zinuteSkaityti(Zinute, n);
    sifravimas(Zinute, Sifras, n);
    isvesti(Zinute, Sifras, n);
    return 0;
}
void sifrasSkaityti(struct sifras Sifras[])
{
    ifstream in("Sifras.txt");
    string raid, simb;
    for (int i = 0; i < 25; i++)
    {
        getline(in, raid, ' ');
        getline(in, simb, '\n');
        strcpy(Sifras[i].raid, raid.c_str());
        strcpy(Sifras[i].simb, simb.c_str());
        Sifras[i].ascii = Sifras[i].simb[0];
        cout << Sifras[i].raid << " " << Sifras[i].simb << " " << Sifras[i].ascii << endl;
    }
}
void zinuteSkaityti(struct zinute Zinute[], int &n)
{
    ifstream in("Zinute.txt");
    in >> n;
    in.ignore(1, '\n');
    for (int i = 0; i < n; i++)
    {
        in >> Zinute[i].diena;
        getline(in, Zinute[i].vardas);
        in.getline(Zinute[i].Tekstas, 1000);
        //debug cout << Zinute[i].diena << " " << Zinute[i].vardas << endl << Zinute[i].Tekstas << endl;;
    }
}

void sifravimas(struct zinute Zinute[], struct sifras Sifras[], int n)
{
    for (int i = 0; i < n; i++)
    {
        if (Zinute[i].diena == 1)
        {
            for (int j = 0; j < strlen(Zinute[i].Tekstas); j++)
            {
                for (int k = 0; k < 25; k++)
                {

                    if (Zinute[i].Tekstas[j] == Sifras[k].raid[0])
                    {
                        Zinute[i].Tekstas[j] = Sifras[k].ascii;
                        Sifras[k].kodascii[i] = Zinute[i].Tekstas[j];
                        break;
                        //debug cout << Zinute[i].Tekstas[j];
                    }
                }
            }
        }
        else
        {
            for (int j = 0; j < strlen(Zinute[i].Tekstas); j++)
            {
                for (int k = 0; k < 25; k++)
                {
                    if (Zinute[i].Tekstas[j] == Sifras[k].raid[0])
                    {
                        Zinute[i].Tekstas[j] = Sifras[k].ascii+faktorialas(Zinute[i].diena);
                        Sifras[k].kodascii[i] = Zinute[i].Tekstas[j];
                        break;
                        //debug cout << Zinute[i].Tekstas[j];
                    }
                }
            }
        }
    }
}
void issifravimas(struct zinute Zinute[], struct sifras Sifras[], int i)
{
    if (Zinute[i].diena == 1)
        {
        for (int j = 0; j < strlen(Zinute[i].Tekstas); j++)
        {
            for (int k = 0; k < 25; k++)
            {

                if (Zinute[i].Tekstas[j] == Sifras[k].simb[0])
                {
                    Zinute[i].Tekstas[j] = Sifras[k].raid[0];
                    //debug cout << Zinute[i].Tekstas[j];
                }
            }
        }
    }
    else
    {
        for (int j = 0; j < strlen(Zinute[i].Tekstas); j++)
        {
            for (int k = 0; k < 25; k++)
            {
                if (Sifras[k].kodascii[i] > 0 && Sifras[k].kodascii[i] < 127) /*/ be sitos salygos vietoj J atsiranda B/*/
                {
                    if (Zinute[i].Tekstas[j] == Sifras[k].ascii+6)
                    {
                        Zinute[i].Tekstas[j] = Sifras[k].raid[0];
                        break;
                    }
                }
                else if (Zinute[i].Tekstas[j] == Sifras[k].kodascii[i])
                {
                    Zinute[i].Tekstas[j] = Sifras[k].raid[0];
                    break;
                }
            }
        }
    }
}
int faktorialas(int diena)
{
    int fktr = 1;
    for(int i = 1; i <= diena; i++)
        fktr *= i;
    return fktr;
}
void isvesti(struct zinute Zinute[], struct sifras Sifras[], int n)
{
    string savD[8] = {"Pirmadienis", "Antradienis", "Treciadienis", "Ketvirtadienis", "Penktadienis", "Sestadienis", "Sekmadienis"};
    ofstream out("Rezultatai2.txt");
    for (int i = 0; i < n; i++)
    {
        out << "-----------------------------------------------------------------------------------------------------" << endl;
        out << "Siuntejas: " << Zinute[i].vardas << endl;
        out << "Gauta: " << savD[Zinute[i].diena] << endl;
        out << "Sifruota zinute: " << Zinute[i].Tekstas << endl;
        issifravimas(Zinute, Sifras, i);
        out << "Issifruota zinute: " << Zinute[i].Tekstas << endl;
        out << "-----------------------------------------------------------------------------------------------------" << endl;
    }
}
