#include <iostream>
#include <fstream>

using namespace std;

void skaityti(int &sk, int &png, int Kodas[], int Kaina[]);
void taipNe(string KaPirkti[], int png, int Kaina[], int sk);
void isvesti(int Kodas[], string KaPirkti[], int sk, int n);
int kiekPirkti(string KaPirkti[], int sk);

int main()
{
    int sk, png, n, Kodas[1000], Kaina[1000];
    string KaPirkti[1000];
    skaityti(sk, png, Kodas, Kaina);
    taipNe(KaPirkti, png, Kaina, sk);
    n = kiekPirkti(KaPirkti, sk);
    isvesti(Kodas, KaPirkti, sk, n);
    return 0;
}

void skaityti(int &sk, int &png, int Kodas[], int Kaina[])
{
    ifstream in("Duomenys2.txt");
    in >> png;
    in >> sk;
    for (int i = 0; i < sk; i++)
        in >> Kodas[i] >> Kaina[i];
}

void taipNe(string KaPirkti[], int png, int Kaina[], int sk)
{
    for (int i = 0; i < sk; i++)
        if (png >= Kaina[i])
        {
            KaPirkti[i] = "TAIP";
            png -= Kaina[i];
            cout << png << endl;
        }
        else
            KaPirkti[i] = "NE";
}

int kiekPirkti(string KaPirkti[], int sk)
{
    int n = 0;
    for (int i = 0; i < sk; i++, n++)
        if (KaPirkti[i] == "NE" || i + 1 == sk)
            return n;
}

void isvesti(int Kodas[], string KaPirkti[], int sk, int n)
{
    ofstream out("Rezultatai2.txt");
    for (int i = 0; i < sk; i++)
        out << Kodas[i] << " " << KaPirkti[i] << endl;
    out << "Galima nusipirkt " << n << " prekes" << endl;
}
