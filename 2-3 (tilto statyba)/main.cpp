#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void reikalingiPoliai(int polSk, int ilgis, int seklSk, int &reikPolSk, string &isvada);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    int polSk, ilgis, seklSk, reikPolSk;
    string isvada;
    ifstream in("Duomenys3.txt");
    in >> polSk >> ilgis >> seklSk;
    reikalingiPoliai(polSk, ilgis, seklSk, reikPolSk, isvada);
    ofstream out("Rezultatai3.txt");
    out << isvada << endl;
    out << reikPolSk << endl;
    return 0;
}

void reikalingiPoliai(int polSk, int ilgis, int seklSk, int &reikPolSk, string &isvada)
{
    polSk -= seklSk * 4;
    while(ilgis > 0)
    {
        polSk -= 8;
        ilgis--;
    }
    reikPolSk = polSk;
    if(reikPolSk >= 0)
        isvada = "Poliø uþteks tiltui pastatyti";
    else
        isvada = "Poliø neuþteks tiltui pastatyti";
}
