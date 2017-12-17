#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

double sanaudos (double sanaud, int nr);
void isvada (string &rez, int benz, int dyz);

int main()
{
    double dyz, benz; //viskas aiðku manau
    string rez; //rezultatø string'as
    ifstream in("Duomenys1.txt"); //ásiloadina failas
    in >> benz; //nuskaito (ásivaizduok, kad cin)
    in >> dyz; //nuskaito
    for (int i = 0; i < 2; i++) //max dvi maðinos, tai iki dviejø
    {
        if (i == 0) benz = sanaudos(benz, i); //jeigu benzinas, tada siunèia jo sànaudas ir numerá á funkcijà sanaudos, ið kurios
        //gráþta double ir yra paskiriamas benz kintamajam
        else dyz = sanaudos (dyz, i); //tas pats, kas su benzinu, tik dyzelis
    isvada(rez, benz, dyz); //keliasi á isvada funkcijà
    ofstream out("Rezultatai1.txt"); //ásiveda rezultatø failà
    out << fixed << setprecision(2) << benz << endl; //iðveda (ásivaizduok, kad cout)
    out << fixed << setprecision(2) << dyz << endl; //iðveda
    out << rez; //iðveda
    return 0;
}
double sanaudos (double sanaud, int nr) //ið ano apraðo pasiima sanaud (vienam - benzino, kitam dyzelio), ir numerá (ten buvo i)
{
    double kuroKaina; //aiðku
    int autoKaina, km = 18000*2; //aiðku
    if (nr == 0) //jeigu benzinas, nr 0
    {
        autoKaina = 2500; //benzino duomenys ið apraðo
        kuroKaina = 1.12;
    }
    else //jeigu dyzelis, nr 1, ne 0
    {
        autoKaina = 3200; //dyzelio duomenys ið apraðo
        kuroKaina = 0.99;
    }
    return autoKaina + sanaud / 100 * km * kuroKaina; //gràþina ðità kaip double (virðuj)
}
void isvada(string &rez, int benz, int dyz) //ið apraðo pareina rez, benz, ir dyz. & reiðkia, kad kokia èia rez reikðmë gausis,
//tokià kels á pirmà kintamàjá ten
{
    if (benz < dyz) //jeigu benzino sànaudos maþesnës
    {
        rez = "Geriau apsimoka pirkti benzinu varomà automobilá."; //string'ui rez prisiskiria ðitas; gráð á main funkcijà
    }
    else rez = "Geriau apsimoka pirkti dyzelinu varomà automobilá."; //string'ui rez prisiskiria ðitas; gráð á main funkcijà
}
