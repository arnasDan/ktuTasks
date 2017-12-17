#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;

void skaityti(struct zodz &zod);
bool pakilus(string zodis, string abc);
bool palindromas(string zodis);
void skaiciavimas(struct zodz zod, int &pal, int &pak);
void isvesti(int pal, int pak);

struct zodz
{
    int sk;
    string zodziai[100];
    string abc;
};

int main()
{
    int pal = 0, pak = 0;
    zodz zod;
    setlocale(LC_ALL, "Lithuanian");
    skaityti(zod);
    skaiciavimas(zod, pal, pak);
    isvesti(pal, pak);
    return 0;
}

void skaityti(struct zodz &zod)
{
    ifstream in("Duomenys.txt");
    in >> zod.sk;
    for (int i = 0; i < zod.sk; i++)
    {
        in >> zod.zodziai[i];
        transform(zod.zodziai[i].begin(), zod.zodziai[i].end(), zod.zodziai[i].begin(), ::tolower);
        //debug cout << zod.zodziai[i] << endl;
    }
    zod.abc = "aàbcèdeæëfghiáyjklmnoprsðtuøûvzþ";
}

bool pakilus(string zodis, string abc)
{
    int prev = -1, cur, j;
    for (int i = 0; i < zodis.length(); i++)
    {
        j = 0;
        while (j < abc.length())
        {
            if (zodis[i] == abc[j])
            {
                cur = j;
                break;
            }
            j++;
        }
        if (cur > prev)
        {
            prev = cur;
        }
        else
            return false;
    }
    return true;
}

bool palindromas(string zodis)
{
    if (zodis == string(zodis.rbegin(), zodis.rend()))
        return true;
    else
        return false;
}

void skaiciavimas(struct zodz zod, int &pal, int &pak)
{
    for (int i = 0; i < zod.sk; i++)
    {
        if (pakilus(zod.zodziai[i], zod.abc))
            pak++;
        if (palindromas(zod.zodziai[i]))
            pal++;
    }
}

void isvesti(int pal, int pak)
{
    ofstream out("Rezultatai.txt");
    if (pal == pak)
        out << ":|" << endl;
    else if (pal > pak)
        out << ":(" << endl;
        else
            out << ":)" << endl;
}
