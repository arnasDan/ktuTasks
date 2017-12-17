#include <iostream>
#include <fstream>

using namespace std;

struct mokytojas
{
    string vard;
    string pvrd;
    string dalyk;
    int mokSk;
    int vidSum;
};

struct mokinys
{
    string dalyk;
    int vid;
};

void skaityti(struct mokytojas Mokyt[], int &mokytSk, struct mokinys Mok[], int &mokSk);
void mokiniuSkaicius(struct mokytojas Mokyt[], int &mokytSk, struct mokinys Mok[], int &mokSk);
void isvesti(struct mokytojas Mokyt[], int mokytSk, int maxSk, int maxVid);
int daugiausiaMokiniu(struct mokytojas Mokyt[], int &mokytSk);
int geriausiasVidurkis(struct mokytojas Mokyt[], int &mokytSk);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    int mokytSk, mokSk, maxSk, maxVid;
    mokytojas Mokyt[100];
    mokinys Mok[100];
    skaityti(Mokyt, mokytSk, Mok, mokSk);
    mokiniuSkaicius(Mokyt, mokytSk, Mok, mokSk);
    maxSk = daugiausiaMokiniu(Mokyt, mokytSk);
    maxVid = geriausiasVidurkis(Mokyt, mokytSk);
    isvesti (Mokyt, mokytSk, maxSk, maxVid);
    return 0;
}

void skaityti(struct mokytojas Mokyt[], int &mokytSk, struct mokinys Mok[], int &mokSk)
{
    ifstream in("Mokytojai.txt");
    in >> mokytSk;
    for (int i = 0; i < mokytSk; i++)
    {
        in >> Mokyt[i].vard >> Mokyt[i].pvrd >> Mokyt[i].dalyk;
        Mokyt[i].mokSk = 0;
        Mokyt[i].vidSum = 0;
    }
    ifstream min("Mokiniai.txt");
    min >> mokSk;
    for (int i = 0; i < mokSk; i++)
    {
        min.ignore(64, ' ');
        min.ignore(64, ' ');
        min >> Mok[i].dalyk >> Mok[i].vid;
    }
}

void mokiniuSkaicius(struct mokytojas Mokyt[], int &mokytSk, struct mokinys Mok[], int &mokSk)
{
    for (int i = 0; i < mokSk; i++)
        for (int j = 0; j < mokytSk; j++)
        {
            if (Mok[i].dalyk == Mokyt[j].dalyk)
            {
                Mokyt[j].mokSk++;
                Mokyt[j].vidSum += Mok[i].vid;
                break;
            }
        }
}

int daugiausiaMokiniu(struct mokytojas Mokyt[], int &mokytSk)
{
    int max = 0;
    for (int i = 0; i < mokytSk; i++)
        if (Mokyt[i].mokSk > Mokyt[max].mokSk)
            max = i;
    return max;
}

int geriausiasVidurkis(struct mokytojas Mokyt[], int &mokytSk)
{
    int max = 0;
    for (int i = 0; i < mokytSk; i++)
        if (Mokyt[i].vidSum / Mokyt[i].mokSk > Mokyt[max].vidSum / Mokyt[max].mokSk)
            max = i;
    return max;
}

void isvesti(struct mokytojas Mokyt[], int mokytSk, int maxSk, int maxVid)
{
    ofstream out("Rezultatai.txt");
    for (int i = 0; i < mokytSk; i++)
        out << Mokyt[i].pvrd << " " << Mokyt[i].mokSk << endl;
    out << "Daugiausia mokiniø turi: " << Mokyt[maxSk].vard << " " << Mokyt[maxSk].pvrd << endl;
    out << "Geriausiai mokiniai mokosi pas: " << Mokyt[maxVid].vard << " " << Mokyt[maxVid].pvrd << endl;
}
