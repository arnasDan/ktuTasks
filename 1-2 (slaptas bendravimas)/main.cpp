#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void skaityti(int &raktas, char Zinute[]);
void issifravimas(int raktas, char Zinute[], int &sk);
int perstumti(char Zinute[], int raktas, int sk);

int main()
{
    int raktas, sk = 0;
    char Zinute[50];
    skaityti(raktas, Zinute);
    setlocale(LC_ALL, "Lithuanian");
    issifravimas(raktas, Zinute, sk);
    ofstream out("Rezultatai1.txt");
    out << "Iğğifruota şinutë:" << endl;
    for (int i = 0; i<sk; i++)
    {
        out << Zinute[i];
    }
    return 0;
}
void skaityti(int &raktas, char Zinute[])
{
    ifstream in("Duomenys1.txt");
    in >> raktas;
    in.getline(Zinute, 1);
    in.getline(Zinute, 50);
}
void issifravimas(int raktas, char Zinute[], int &sk)
{
    int zodSk = 0;
    while (Zinute[sk] != 0)
    {
        Zinute[sk] = perstumti(Zinute, raktas, sk);
        if (Zinute[sk] == 'x')
        {
            raktas += zodSk;
            Zinute [sk] = ' ';
            zodSk = -1;
            cout << raktas << endl;
        }
        sk++;
        zodSk++;
    }
    //sk++; Zinute[sk]='\0';
}
int perstumti(char Zinute[], int raktas, int sk)
{
    int ascii = (int) Zinute[sk];
    if ((ascii - raktas) < 97) ascii += 26;
    ascii -= raktas;
    //cout << Ascii;
    return ascii;
}
