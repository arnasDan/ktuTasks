#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

void perjungimai(int &sk, string &seka);

int main()
{
    int sk = 0;
    string seka = "";
    perjungimai(sk, seka);
    ofstream out("Rezultatai2.txt");
    out << sk << endl;
    out << seka << endl;
    return 0;
}

void perjungimai(int &sk, string &seka)
{
    int dab, kanalai, kitas, skirtumas;
    ifstream in("Duomenys2.txt");
    in >> kanalai >> dab;
    for (int i = 0; i < kanalai; i++)
    {
        in >> kitas;
        double skrt = dab-kitas;
        skirtumas = (int) abs(skrt);
        for (int j = 0; j < skirtumas; j++)
        {
            if (dab > kitas)
                seka += "K";
            else
                seka += "D";
            sk++;
        }
        dab = kitas;
    }
}
