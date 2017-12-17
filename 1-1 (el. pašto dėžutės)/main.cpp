#include <iostream>
#include <fstream>

using namespace std;

void skaityti(int &minPav, int &minDom, char Adresas[], int &dydis);
void patikrinimas(int minPav, int minDom, char Adresas[], char Simboliai[], int dydis);

int main()
{
    char Simboliai[50]={'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', 'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'z', 'x', 'c', 'v', 'b', 'n', 'm', '@', '.'};
    int minPav, minDom;
    int dydis = 0;
    char Adresas[50];
    skaityti(minPav, minDom, Adresas, dydis);
    patikrinimas(minPav, minDom, Adresas, Simboliai, dydis);
    return 0;
}

void skaityti(int &minPav, int &minDom, char Adresas[], int &dydis)
{
    ifstream in("email.txt");
    in >> minPav >> minDom;
    in.ignore(1, '\n');
    in.getline(Adresas, 50);
    //debug cout << Adresas << endl;
    for (int i = 0; i < 50; i++)
    {
        if (Adresas[i] != '\0') dydis += 1;
        else break;
    }
}

void patikrinimas(int minPav, int minDom, char Adresas[], char Simboliai[], int dydis)
{
    int pav = 0;
    int dom = 0;
    bool netinkamasSimbolis;
    bool blogas = false, pirmaDalis = false;
    for (int i = 0; i < dydis; i++)
    {
        netinkamasSimbolis = true;
        for (int j = 0; j < 28; j++)
        {

            if (Adresas[i] == Simboliai[j])
            {
                netinkamasSimbolis = false;
            }
            //debug cout << Adresas[i] << Simboliai[j] << " " << endl;
        }
        if(Adresas[i] == '@')
            pirmaDalis = true;
        if (netinkamasSimbolis == true)
        {
            cout << "Email neteisingas." << endl << "Yra neleistinu simboliu." << endl;
            blogas = true;
            break;
        }
        if (Adresas[i] != '.' && pirmaDalis == true)
        {
            pav += 1;
        }
        if (Adresas[i] == '.')
        {
            pirmaDalis = false;
            if (pav < minPav)
            {
                cout << "Email neteisingas." << endl << "Per trumpas pasto dezutes pavadinimas." << endl;
                blogas = true;
                break;
            }
        }
        if (pirmaDalis == false && Adresas[i] != '.' && pav != 0)
        {
            dom += 1;
        }
        if (i == dydis-1 && dom < minDom)
        {
            //debug cout << i << " " << dom << " " << minDom << endl;
            cout << "Email neteisingas." << endl << "Per trumpas domeno pavadinimas." << endl;
            blogas = true;
        }
    }
    if (!blogas) cout << "Email teisingas";
}
