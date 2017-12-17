#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include <algorithm>

using namespace std;

void skaityti(int &n, int Nr[], double Tsk[]);
void rusiuotiPagalEiliskuma(int n, int Nr[], double Tsk[]);
void rusiuotiPagalTaskus(int n, int Nr[], double Tsk[]);
void isvestiSarasa(int n, int Nr[], double Tsk[], ofstream &out);
void isvestiGeriausius(int n, int Nr[], double Tsk[], ofstream &out);
void isvestiBlogiausius(int n, int Nr[], double Tsk[], ofstream &out);
double didziausia(int n, double Tsk[]);
double maziausia(int n, double Tsk[]);

int main()
{
    int n, Nr[101];
    double Tsk[101] = {0};
    ofstream out("sachmatai2rez.txt");
    out << "Sportininkø rezultatai:" << endl;
    skaityti(n, Nr, Tsk);
    rusiuotiPagalEiliskuma(n, Nr, Tsk);
    isvestiSarasa(n, Nr, Tsk, out);
    isvestiBlogiausius(n, Nr, Tsk, out);
    isvestiGeriausius(n, Nr, Tsk, out);
    rusiuotiPagalTaskus(n, Nr, Tsk);
    out << "Surikiuotas sàraðas:" << endl;
    isvestiSarasa(n, Nr, Tsk, out);
    return 0;
}

void skaityti(int &n, int Nr[], double Tsk[])
{
    int tmp;
    ifstream in("sachmatai2.txt");
    in >> n;
    for (int i = 0; i < n; i++)
    {
        in >> Nr[i];
        for (int j = 2; j >= 0; j--)
        {
            in >> tmp;
            Tsk[i] += tmp * (j / 2.0);
        }
    }
}

void rusiuotiPagalEiliskuma(int n, int Nr[], double Tsk[])
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i; j < n; j++)
            if (Nr[i] > Nr[j])
            {
                swap(Nr[i], Nr[j]);
                swap(Tsk[i], Tsk[j]);
            }
}

void rusiuotiPagalTaskus(int n, int Nr[], double Tsk[])
{
    for (int i = 0; i < n - 1; i++)
        for (int j = i; j < n; j++)
            if (Tsk[i] < Tsk[j] || Tsk[i] == Tsk[j] && Nr[i] < Nr[j])
            {
                swap(Nr[i], Nr[j]);
                swap(Tsk[i], Tsk[j]);
            }
}

void isvestiSarasa(int n, int Nr[], double Tsk[], ofstream &out)
{
    for (int i = 0; i < n; i++)
        out << Nr[i] << " " << fixed << setprecision(1) << Tsk[i] << endl;
}

void isvestiGeriausius(int n, int Nr[], double Tsk[], ofstream &out)
{
    out << "Daugiausiai taðkø surinkæ sportininkai:" << endl;
    int max = didziausia(n, Tsk);
    for (int i = n - 1; i >= 0; i--)
        if (Tsk[i] == max)
            out << Nr[i] << " ";
    out << endl;
}

void isvestiBlogiausius(int n, int Nr[], double Tsk[], ofstream &out)
{
    out << "Maþiausiai taðkø surinkæ sportininkai:" << endl;
    double min = maziausia(n, Tsk);
    for (int i = 0; i < n; i++)
        if (Tsk[i] == min)
            out << Nr[i] << " ";
    out << endl;
}

double didziausia(int n, double Tsk[])
{
    double max = 0;
    for (int i = 0; i < n; i++)
        if (Tsk[i] > max)
            max = Tsk[i];
    return max;
}

double maziausia(int n, double Tsk[])
{
    double min = numeric_limits <double>::max();
    for (int i = 0; i < n; i++)
        if (Tsk[i] < min)
            min = Tsk[i];
    return min;
}
