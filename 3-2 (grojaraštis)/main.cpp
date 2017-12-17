#include <iostream>
#include <fstream>

using namespace std;

struct daina
{
    string atlikejas;
    int min;
    int s;
};

struct atlikejas
{
    string vardas;
    int n;
    int trukme;
};

void skaityti(struct daina Dain[], int &n);
int vidutineTrukme(struct daina Dain[], int n);
void atlikejoDainos(struct daina Dain[], struct atlikejas &atlk, int n);
void isvesti (struct atlikejas atlk, int vid);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    int n, vid;
    daina Dain[500];
    atlikejas atlk;
    skaityti(Dain, n);
    vid = vidutineTrukme(Dain, n);
    atlikejoDainos(Dain, atlk, n);
    isvesti(atlk, vid);
    return 0;
}

void skaityti(struct daina Dain[], int &n)
{
   ifstream in("Dainos.txt");
   in >> n;
   in.ignore(16, '\n');
   for (int i = 0; i < n; i++)
   {
       getline(in, Dain[i].atlikejas, '-');
       in.ignore(256, ',');
       in >> Dain[i].min >> Dain[i].s;
       in.ignore(16, '\n');
   }
}

int vidutineTrukme(struct daina Dain[], int n)
{
    int sumS = 0;
    for (int i = 0; i < n; i++)
    {
        sumS += (Dain[i].s + Dain[i].min * 60);
    }
    return sumS / n;
}

void atlikejoDainos(struct daina Dain[], struct atlikejas &atlk, int n)
{
    int sum = 0;
    atlk.n = 0;
    getline(cin, atlk.vardas, '\n');
    for (int i = 0; i < n; i++)
    {
        if (atlk.vardas == Dain[i].atlikejas)
        {
            atlk.n++;
            sum += (Dain[i].s + Dain[i].min * 60);
        }
    }
    atlk.trukme = sum + 5 * (atlk.n - 1);
}

void isvesti (struct atlikejas atlk, int vid)
{
    ofstream out("Rezultatai.txt");
    out << "Atlikëjo " << atlk.vardas << " dainø kiekis: " << atlk.n << endl;
    out << "Jas perklausyti uþtruks " << atlk.trukme/60 << "m " << atlk.trukme%60 << "s" << endl;
    out << "Visø dainø trukmës vidurkis: " << vid/60 << "m " << vid%60 << "s" << endl;
}
