#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

void skaityti(int &n, int Kiaus[], int Obuol[], double Milt[], double Cukr[], double Laik[], double Tmp[]);
void isvesti(int n, int Kiaus[], int Obuol[], double Milt[], double Cukr[], double Laik[], double Tmp[], int kiausSum, int obuolSum, int vSk, int tSk, double miltVid, double cukrVid);
void salinti(int &n, int Kiaus[], int Obuol[], double Milt[], double Cukr[], double Laik[], double Tmp[]);
void salintiIsMasyvo(int n, double Arr[], int nr);
double vidurkis(double Arr[], int n);
int suma(int Arr[], int n);
int keli(double Arr[], int n, int min);

int main()
{
    int n, v, t, kiausSum, obuolSum, vSk, tSk, Kiaus[100], Obuol[100];
    double miltVid, cukrVid, Milt[100], Cukr[100], Laik[100], Tmp[100];
    skaityti(n, Kiaus, Obuol, Milt, Cukr, Laik, Tmp);
    cout << "Iveskite laika valandomis v: ";
    cin >> v;
    cout << "Iveskite temperatura t: ";
    cin >> t;
    kiausSum = suma(Kiaus, n);
    obuolSum = suma(Obuol, n);
    miltVid = vidurkis(Milt, n);
    cukrVid = vidurkis(Cukr, n);
    vSk = keli(Laik, n, v);
    tSk = keli(Tmp, n, t);
    salinti(n, Kiaus, Obuol, Milt, Cukr, Laik, Tmp);
    isvesti(n, Kiaus, Obuol, Milt, Cukr, Laik, Tmp, kiausSum, obuolSum, vSk, tSk, miltVid, cukrVid);
    return 0;
}

void skaityti(int &n, int Kiaus[], int Obuol[], double Milt[], double Cukr[], double Laik[], double Tmp[])
{
    ifstream in("pyragai.txt");
    in >> n;
    for (int i = 0; i < n; i++)
        in >> Kiaus[i] >> Obuol[i] >> Milt[i] >> Cukr[i] >> Laik[i] >> Tmp[i];
}

void isvesti(int n, int Kiaus[], int Obuol[], double Milt[], double Cukr[], double Laik[], double Tmp[], int kiausSum, int obuolSum, int vSk, int tSk, double miltVid, double cukrVid)
{
    ofstream out("pyragairez.txt");
    out << kiausSum << " " << obuolSum << endl;
    out << fixed << setprecision(1) << miltVid << " " << cukrVid << endl;
    out << vSk << endl;
    out << tSk << endl;
    for (int i = 0; i < n; i++)
        out << Kiaus[i] << " " << Obuol[i] << " " << Milt[i] << " " << Cukr[i] << " " << Laik[i] << " " << Tmp[i] << endl;
}

void salinti(int &n, int Kiaus[], int Obuol[], double Milt[], double Cukr[], double Laik[], double Tmp[])
{
    double max = 200.0;
    for (int i = 0; i < n; i++)
        if (Tmp[i] >= max)
        {
            if (i + 1 != n)
            {
                salintiIsMasyvo(n, (double*) Kiaus, i);
                salintiIsMasyvo(n, (double*) Obuol, i);
                salintiIsMasyvo(n, Milt, i);
                salintiIsMasyvo(n, Cukr, i);
                salintiIsMasyvo(n, Laik, i);
                salintiIsMasyvo(n, Tmp, i);
            }
            n--;
            i--;
        }
}

void salintiIsMasyvo(int n, double Arr[], int nr)
{
    for (int i = nr; i < n; i++)
        Arr[i] = Arr[i + 1];
    Arr[n - 1] = 0;
}

double vidurkis(double Arr[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += Arr[i];
    return (sum / n);
}

int suma(int Arr[], int n)
{
    int sum = 0;
    for (int i = 0; i < n; i++)
        sum += Arr[i];
    return sum;
}

int keli(double Arr[], int n, int min)
{
    int k = 0;
    for (int i = 0; i < n; i++)
        if (Arr[i] >= min)
            k++;
    return k;
}
