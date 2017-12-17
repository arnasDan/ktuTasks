#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

double sanaudos (double sanaud, int nr);
void isvada (string &rez, int benz, int dyz);

int main()
{
    double dyz, benz; //viskas ai�ku manau
    string rez; //rezultat� string'as
    ifstream in("Duomenys1.txt"); //�siloadina failas
    in >> benz; //nuskaito (�sivaizduok, kad cin)
    in >> dyz; //nuskaito
    for (int i = 0; i < 2; i++) //max dvi ma�inos, tai iki dviej�
    {
        if (i == 0) benz = sanaudos(benz, i); //jeigu benzinas, tada siun�ia jo s�naudas ir numer� � funkcij� sanaudos, i� kurios
        //gr��ta double ir yra paskiriamas benz kintamajam
        else dyz = sanaudos (dyz, i); //tas pats, kas su benzinu, tik dyzelis
    isvada(rez, benz, dyz); //keliasi � isvada funkcij�
    ofstream out("Rezultatai1.txt"); //�siveda rezultat� fail�
    out << fixed << setprecision(2) << benz << endl; //i�veda (�sivaizduok, kad cout)
    out << fixed << setprecision(2) << dyz << endl; //i�veda
    out << rez; //i�veda
    return 0;
}
double sanaudos (double sanaud, int nr) //i� ano apra�o pasiima sanaud (vienam - benzino, kitam dyzelio), ir numer� (ten buvo i)
{
    double kuroKaina; //ai�ku
    int autoKaina, km = 18000*2; //ai�ku
    if (nr == 0) //jeigu benzinas, nr 0
    {
        autoKaina = 2500; //benzino duomenys i� apra�o
        kuroKaina = 1.12;
    }
    else //jeigu dyzelis, nr 1, ne 0
    {
        autoKaina = 3200; //dyzelio duomenys i� apra�o
        kuroKaina = 0.99;
    }
    return autoKaina + sanaud / 100 * km * kuroKaina; //gr��ina �it� kaip double (vir�uj)
}
void isvada(string &rez, int benz, int dyz) //i� apra�o pareina rez, benz, ir dyz. & rei�kia, kad kokia �ia rez reik�m� gausis,
//toki� kels � pirm� kintam�j� ten
{
    if (benz < dyz) //jeigu benzino s�naudos ma�esn�s
    {
        rez = "Geriau apsimoka pirkti benzinu varom� automobil�."; //string'ui rez prisiskiria �itas; gr�� � main funkcij�
    }
    else rez = "Geriau apsimoka pirkti dyzelinu varom� automobil�."; //string'ui rez prisiskiria �itas; gr�� � main funkcij�
}
