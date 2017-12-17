#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>

using namespace std;

struct mokinys
{
    string vard;
    int grSk;
    string Gr[100];
    int blgSk;
    string Blg[100];
};

struct pamoka
{
    string pav;
    int grSk;
    string MokGr[100];
    int blgSk;
    string MokBlg[100];
};

struct dgs
{
    int sk;
    string Pav[100];
    int mokSk;
};

struct skrtm
{
    int sk;
    string Pav[100];
    int skrt;
};

void skaityti(struct mokinys Mok[], int &mokSk);
void formuotiPamoka(struct mokinys Mok[], struct pamoka Pam[], int mokSk, int &pamSk);
void suprantaDaugiausia(struct pamoka Pam[], int pamSk, struct dgs &grMax);
void nesuprantaDaugiausia(struct pamoka Pam[], int pamSk, struct dgs &grMax);
void didziausiasSkirtumas(struct pamoka Pam[], int pamSk, struct skrtm &skrtMax);
void isvesti(struct pamoka Pam[], struct skrtm skrtMax, struct dgs blgMax, struct dgs grMax, struct mokinys Mok[], int mokSk, int pamSk);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    int mokSk, pamSk = 0;
    pamoka Pam[100];
    mokinys Mok[100];
    dgs grMax;
    dgs blgMax;
    skrtm skrtMax;
    skaityti(Mok, mokSk);
    formuotiPamoka(Mok, Pam, mokSk, pamSk);
    suprantaDaugiausia(Pam, pamSk, grMax);
    nesuprantaDaugiausia(Pam, pamSk, blgMax);
    didziausiasSkirtumas(Pam, pamSk, skrtMax);
    isvesti(Pam, skrtMax, blgMax, grMax, Mok, mokSk, pamSk);
    return 0;
}

void skaityti(struct mokinys Mok[], int &mokSk)
{
    ifstream in("klase.txt");
    in >> mokSk;
    in.ignore(1, '\n');
    for (int i = 0; i < mokSk; i++)
    {
        getline(in, Mok[i].vard, '\n');
        in >> Mok[i].grSk;
        in.ignore(1, '\n');
        for (int j = 0; j < Mok[i].grSk; j++)
            getline(in, Mok[i].Gr[j], '\n');
        in >> Mok[i].blgSk;
        in.ignore(1, '\n');
        for (int j = 0; j < Mok[i].blgSk; j++)
            getline(in, Mok[i].Blg[j], '\n');
    }
}

void formuotiPamoka(struct mokinys Mok[], struct pamoka Pam[], int mokSk, int &pamSk)
{
    for (int i = 0; i < mokSk; i++)
    {
        for (int j = 0; j < Mok[i].grSk; j++)
        {
            bool jauYra = false;
            for (int k = 0; k < pamSk; k++)
                if (Mok[i].Gr[j] == Pam[k].pav)
                {
                    Pam[k].MokGr[Pam[k].grSk] = Mok[i].vard;
                    Pam[k].grSk++;
                    jauYra = true;
                }
            if (!jauYra)
            {
                Pam[pamSk].pav = Mok[i].Gr[j];
                Pam[pamSk].MokGr[0] = Mok[i].vard;
                Pam[pamSk].grSk = 1;
                pamSk++;
            }
        }
        for (int j = 0; j < Mok[i].blgSk; j++)
        {
            bool jauYra = false;
            for (int k = 0; k < pamSk; k++)
                if (Mok[i].Blg[j] == Pam[k].pav)
                {
                    Pam[k].MokBlg[Pam[k].blgSk] = Mok[i].vard;
                    Pam[k].blgSk++;
                    jauYra = true;
                }
            if (!jauYra)
            {
                Pam[pamSk].pav = Mok[i].Blg[j];
                Pam[pamSk].MokBlg[0] = Mok[i].vard;
                Pam[pamSk].blgSk = 1;
                pamSk++;
            }
        }
    }
}

void suprantaDaugiausia(struct pamoka Pam[], int pamSk, struct dgs &grMax)
{
    dgs tuscias;
    tuscias.sk = 1;
    grMax.mokSk = -1;
    for (int i = 0; i < pamSk; i++)
    {
        if (Pam[i].grSk > grMax.mokSk)
        {
            grMax = tuscias;
            grMax.Pav[0] = Pam[i].pav;
            grMax.mokSk = Pam[i].grSk;
        }
        else if (Pam[i].grSk == grMax.mokSk)
        {
            grMax.Pav[grMax.sk] = Pam[i].pav;
            grMax.sk++;
        }
    }
}

void nesuprantaDaugiausia(struct pamoka Pam[], int pamSk, struct dgs &blgMax)
{
    dgs tuscias;
    tuscias.sk = 1;
    blgMax.mokSk = -1;
    for (int i = 0; i < pamSk; i++)
    {
        if (Pam[i].blgSk > blgMax.mokSk)
        {
            blgMax = tuscias;
            blgMax.Pav[0] = Pam[i].pav;
            blgMax.mokSk = Pam[i].blgSk;
        }
        else if (Pam[i].blgSk == blgMax.mokSk)
        {
            blgMax.Pav[blgMax.sk] = Pam[i].pav;
            blgMax.sk++;
        }
    }
}

void didziausiasSkirtumas(struct pamoka Pam[], int pamSk, struct skrtm &skrtMax)
{
    skrtm tuscias;
    tuscias.sk = 1;
    skrtMax.skrt = -1;
    for (int i = 0; i < pamSk; i++)
    {
        if (fabs(Pam[i].blgSk - Pam[i].grSk) > skrtMax.skrt) //abs neveikia kazkodel
        {
            skrtMax = tuscias;
            skrtMax.Pav[0] = Pam[i].pav;
            skrtMax.skrt = fabs(Pam[i].blgSk - Pam[i].grSk);
        }
        else if (fabs(Pam[i].blgSk - Pam[i].grSk) == skrtMax.skrt)
        {
            skrtMax.Pav[skrtMax.sk] = Pam[i].pav;
            skrtMax.sk++;
        }
    }
}

void isvesti(struct pamoka Pam[], struct skrtm skrtMax, struct dgs blgMax, struct dgs grMax, struct mokinys Mok[], int mokSk, int pamSk)
{
    ofstream out("pamokos.txt");
    out << "-----------------------------------------------------------------------" << endl;
    out << "|Mokinys" << setw(16) << '|' <<  " Puikiai moka" << setw(11) << '|' << " Nemoka" << setw(17) << "|" << endl;
    out << "-----------------------------------------------------------------------" << endl;
    for (int i = 0; i < mokSk; i++)
    {
        out << "|" << setw(21) << Mok[i].vard << " | " << setw(21) << Mok[i].Gr[0] << " | " << setw(21) << Mok[i].Blg[0] << " |" << endl;
        int max = Mok[i].grSk;
        if (Mok[i].blgSk > max)
             max = Mok[i].blgSk;
        for (int j = 1; j < max; j++)
        {
            out << "|" << setw(24)  << " | " << setw(21) << Mok[i].Gr[j] << " | " << setw(21) << Mok[i].Blg[j] << " |" << endl;
        }
        out << "-----------------------------------------------------------------------" << endl;
    }
    out << endl;
    out << "-----------------------------------------------------------------------" << endl;
    out << "|Pavadinimas" << setw(12) << '|' <<  " Mokantys mokiniai" << setw(6) << '|' << " Nemokantys mokiniai" << setw(4) << "|" << endl;
    out << "-----------------------------------------------------------------------" << endl;
    for (int i = 0; i < pamSk; i++)
    {
        out << "|" << setw(21) << Pam[i].pav << " | " << setw(21) << Pam[i].MokGr[0] << " | " << setw(21) << Pam[i].MokBlg[0] << " |" << endl;
        int max = Pam[i].grSk;
        if (Pam[i].blgSk > max)
             max = Pam[i].blgSk;
        for (int j = 1; j < max; j++)
        {
            out << "|" << setw(24)  << " | " << setw(21) << Pam[i].MokGr[j] << " | " << setw(21) << Pam[i].MokBlg[j] << " |" << endl;
        }
        out << "-----------------------------------------------------------------------" << endl;
    }
    out << endl;
    out << grMax.mokSk << " mokiniai supranta ";
    for (int i = 0; i < grMax.sk; i++)
    {
        out << grMax.Pav[i];
        if (i + 1 != grMax.sk)
            out << ", ";
    }
    out << "." << endl;
    out << blgMax.mokSk << " mokiniai nesupranta ";
    for (int i = 0; i < blgMax.sk; i++)
    {
        out << blgMax.Pav[i];
        if (i + 1 != blgMax.sk)
            out << ", ";
    }
    out << "." << endl;
    out << "Didþiausias skirtumas yra: ";
    for (int i = 0; i < skrtMax.sk; i++)
        out << skrtMax.Pav[i] << ";";
    out << " skirtumas " << skrtMax.skrt << " mokiniai." << endl;
}
