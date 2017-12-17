#include <iostream>
#include <fstream>

using namespace std;

void skaityti(int &n, int Prk[], int Gr[]);

int main()
{
    int n, Prk[100], PrdtGr[2], Gr[2]; //Gr/PrdtGr masyvuose 1 elementas - 1kg, 2 elementas - 2kg kiekis
    return 0;
}

void skaityti(int &n, int Prk[], int Gr[])
{
    ifstream in("grikiai.txt");
    in >> Gr[0] >> Gr[1];
    for (int i = 0; i < n; i++)
        in >> Prk[i];
}

void pardavimas(int n, int Prk[], int Gr[])
{
    for (int i = 0; i < n; i++)
    {
        if (Gr[1] > 2 && Prk[i] >= 2)
        {
            if (Gr[1] )

        }
    }
}
