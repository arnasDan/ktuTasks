#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void skaityti(double &plytaS, double &sienaS, int &palete);
double plotas(double a, double b);
void kiekis(double plytaS, double sienaS, int palete, int &plytos, int &paletes);

int main()
{
    double plytaS, sienaS;
    int palete, plytos, paletes;
    skaityti(plytaS, sienaS, palete);
    kiekis(plytaS, sienaS, palete, plytos, paletes);
    ofstream out("Rezultatai1.txt");
    out << plytos << " " << paletes << endl;
    return 0;
}

void skaityti(double &plytaS, double &sienaS, int &palete)
{
    double a, b, langasS;
    ifstream in("Duomenys1.txt");
    in >> a >> b;
    plytaS = plotas(a, b);
    in >> a >> b;
    sienaS = plotas(a, b);
    in >> a >> b;
    langasS = plotas(a, b);
    sienaS -= langasS;
    in >> palete;
}

double plotas(double a, double b)
{
    return (a*b);
}

void kiekis(double plytaS, double sienaS, int palete, int &plytos, int &paletes)
{
    double tmp;
    tmp = sienaS / plytaS; //plytos
    plytos = ceil(tmp);
    tmp /= palete; //paletes
    paletes = ceil(tmp);

}
