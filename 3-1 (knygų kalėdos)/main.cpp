#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void skaityti(int Kiekis[], double Kaina[], int &sk);
void pilnaKaina(int Kiekis[], double Kaina[], double PilnaKaina[], int sk);
void isvesti(int Kiekis[], double Kaina[], double PilnaKaina[], double visuKaina, int virsPenkiu, int sk);
int daugiauNeiPenki(int Kiekis[], int sk);
double visuSuma(double PilnaKaina[], int sk);

int main()
{
    int Kiekis[1000], sk, virsPenkiu;
    double Kaina[1000], PilnaKaina[1000], visuKaina;
    skaityti(Kiekis, Kaina, sk);
    pilnaKaina(Kiekis, Kaina, PilnaKaina, sk);
    visuKaina = visuSuma(PilnaKaina, sk);
    virsPenkiu = daugiauNeiPenki(Kiekis, sk);
    isvesti(Kiekis, Kaina, PilnaKaina, visuKaina, virsPenkiu, sk);
    return 0;
}

void skaityti(int Kiekis[], double Kaina[], int &sk)
{
    ifstream in("Duomenys1.txt");
    in >> sk;
    for (int i = 0; i < sk; i++)
    {
        in >> Kaina[i] >> Kiekis[i];
    }
}

void pilnaKaina(int Kiekis[], double Kaina[], double PilnaKaina[], int sk)
{
    for (int i = 0; i < sk; i++)
        PilnaKaina[i] = Kiekis[i] * Kaina[i];
}

double visuSuma(double PilnaKaina[], int sk)
{
    double sum = 0;
    for (int i = 0; i < sk; i++)
        sum += PilnaKaina[i];
    return sum;
}

int daugiauNeiPenki(int Kiekis[], int sk)
{
    int n = 0;
    for (int i = 0; i < sk; i++)
        if (Kiekis[i] > 5)
            n++;
    return n;
}

void isvesti(int Kiekis[], double Kaina[], double PilnaKaina[], double visuKaina, int virsPenkiu, int sk)
{
    ofstream out("Rezultatai1.txt");
    for (int i = 0; i < sk; i++)
        out << fixed << setprecision(2) << Kaina[i] << " " << Kiekis[i] << " " << PilnaKaina[i] << endl;
    out << fixed << setprecision(2) << visuKaina << endl;
    out << virsPenkiu << endl;
}
