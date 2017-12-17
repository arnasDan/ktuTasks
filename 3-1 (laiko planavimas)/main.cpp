#include <iostream>
#include <fstream>

using namespace std;

struct uzduotis
{
    int plT;
    int rlT;
    bool atlikta;
};

void skaityti(struct uzduotis Uzd[], int &n, int &atliktosUzduotys);
void isvesti(int sk, int pl, int rl, double vid);
int plLaikSum(struct uzduotis Uzd[], int n);
int rlLaikSum(struct uzduotis Uzd[], int n);
double rlLaikVid(int n, int sum);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    uzduotis Uzd[100];
    int n = 0, planuotasLaikas, realusLaikas, atliktosUzduotys = 0;
    double vidutinisLaikas;
    skaityti(Uzd, n, atliktosUzduotys);
    planuotasLaikas = plLaikSum(Uzd, n);
    realusLaikas = rlLaikSum(Uzd, n);
    vidutinisLaikas = rlLaikVid(atliktosUzduotys, realusLaikas);
    isvesti(atliktosUzduotys, planuotasLaikas, realusLaikas, vidutinisLaikas);
    return 0;
}

void skaityti(struct uzduotis Uzd[], int &n, int &atliktosUzduotys)
{
    ifstream in("Duomenys1.txt");
    while (!in.eof())
    {
        string str;
        getline(in, str, ',');
        in >> Uzd[n].plT >> Uzd[n].rlT;
        if (Uzd[n].rlT != 0)
        {
            atliktosUzduotys++;
            Uzd[n].atlikta = true;
        }
        n++;
    }
}

int plLaikSum(struct uzduotis Uzd[], int n)
{
    int suma = 0;
    for (int i = 0; i < n; i++)
    {
        suma += Uzd[i].plT;
    }
    return suma;
}

int rlLaikSum(struct uzduotis Uzd[], int n)
{
    int suma = 0;
    for (int i = 0; i < n; i++)
    {
        suma += Uzd[i].rlT;
    }
    return suma;
}

double rlLaikVid(int n, int sum)
{
    return (double) sum / n;
}

void isvesti(int sk, int pl, int rl, double vid)
{
    ofstream out("Rezultatai1.txt");
    out << "Ið viso Petriukas buvo suplanavæs uþtrukti " << pl << " minutes" << endl;
    out << "Ið viso Petriukas uþtruko " << rl << " minutes" << endl;
    out << "Petriukas vykdë " << sk << " uþduotis, joms vidutiniðkai skyrë po " << vid << " minutes" << endl;
}
