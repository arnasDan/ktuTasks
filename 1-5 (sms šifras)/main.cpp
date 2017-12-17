#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <math.h>

using namespace std;

struct mygtukai
{
    string kod[5];
    char raid[5];
};

void raktas(struct mygtukai Myg[]);
void skaityti(char Zinute[]);
void issifravimas(struct mygtukai Myg[], char Rez[], char Zinute[], int &rd);
void isvesti(int rd, char Rez[]);

int main()
{
    mygtukai Myg[10];
    char Zinute[1000], Rez[1000];
    int rd = 0;
    raktas(Myg);
    skaityti(Zinute);
    issifravimas(Myg, Rez, Zinute, rd);
    isvesti(rd, Rez);
    return 0;
}

void skaityti(char Zinute[])
{
    int n;
    ifstream in("Duomenys4.txt");
    in >> n;
    for (int i = 0; i < n; i++)
    {
        in >> Zinute[i];
    }
}

void raktas(struct mygtukai Myg[])
{
    int sk = 2;
    int i = 97;
    while (i < 123)
    {
        if (sk != 7 && sk != 9)
        {
            Myg[sk].raid = {i, i+1, i+2};
            i += 3;
            //debug cout << Myg[sk].raid << " ";
            sk++;
        }
        else
        {
            Myg[sk].raid = {i, i+1, i+2, i+3};
            i += 4;
            //debug cout << Myg[sk].raid << " ";
            sk++;
        }

    }
    for (int j = 2; j < 10; j++)
    {
        int max, keep, skc = j;
        if (j != 7 && j != 9)
            max = 3;
        else max = 4;
        for (int k = 0; k < max; k++)
        {
            char Tmp[5];
            if (k != 0)
                skc = keep + j * pow(10, k);
            snprintf(Tmp, 5, "%d", skc);
            Myg[j].kod[k] = Tmp;
            keep = skc;
            //debug cout << Myg[j].kod[k] << " ";
        }
    }
}

void issifravimas(struct mygtukai Myg[], char Rez[], char Zinute[], int &rd)
{
    int i = 0, sk = 0, zero = 0;
    char Tmp[5];
    memset(Tmp,'\0',5); //be sito pirmos raides simboliuose is kazkur siuksles
    bool zerotest = false;
    while (Zinute[i] != '\0')
    {
        bool stop;
        if (Zinute[i] != '0' && Zinute[i] != '1')
        {
            Tmp[sk] = Zinute[i];
            sk++;
        }
        else if (sk != 0)
        {
            int j = 2;
            stop = false;
            while (j < 10 && !stop)
            {
                int max;
                if (j == 7 || j == 9)
                    max = 4;
                else max = 3;
                int k = 0;
                while (k < max && !stop)
                {
                    if (strcmp(Tmp, Myg[j].kod[k].c_str()) == 0)
                    {
                        Rez[rd] = Myg[j].raid[k];
                        rd++;
                        stop = true;
                        break;
                    }
                        k++;
                }
                if (stop)
                    break;
                j++;
            }
            memset(Tmp,'\0',5);
            sk = 0;
        }
        if (Zinute[i] == '0')
        {
            zero++;
            zerotest = true;
        }
        if (zerotest && Zinute[i] != '0')
        {
            if (zero == 2)
            {
                Rez[rd] = ' ';
                rd++;
            }
            zero = 0;
        }
        if (Zinute[i] == '1')
            break;
        i++;
    }
    Rez[rd] = '.';
    rd++;
}

void isvesti(int rd, char Rez[])
{
    ofstream out("Rezultatai4.txt");
    for (int i = 0; i < rd; i++)
    {
        out << Rez[i];
    }
}
