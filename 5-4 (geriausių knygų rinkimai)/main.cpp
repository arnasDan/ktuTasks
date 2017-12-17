#include <iostream>
#include <fstream>

using namespace std;

void skaityti(int Nr[], int Tsk[], int &n);
void rusiuoti(int Nr[], int Tsk[], int n);
void sukeisti(int Nr[], int Tsk[], int n, int min, int max);
void isvestiSarasa(int Nr[], int Tsk[], int n, ofstream& out);
void isvestiBlogiausias(int Nr[], int Tsk[], int n, int min, ofstream& out);
void isvestiGeriausias(int Nr[], int Tsk[], int n, int max, ofstream& out);
int maziausia(int Arr[], int n);
int didziausia(int Tsk[], int n);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    ofstream out("knygos1rez.txt");
    int n, min, max, Nr[22], Tsk[22] = {0};
    skaityti(Nr, Tsk, n);
    rusiuoti(Nr, Tsk, n);
    min = maziausia(Tsk, n);
    max = didziausia(Tsk, n);
    out << "Knygø ávertinimai:" << endl;
    isvestiSarasa(Nr, Tsk, n, out);
    isvestiBlogiausias(Nr, Tsk, n, min, out);
    isvestiGeriausias(Nr, Tsk, n, max, out);
    sukeisti(Nr, Tsk, n, min, max);
    out << "Naujas sàraðas:" << endl;
    isvestiSarasa(Nr, Tsk, n, out);
    return 0;
}

void skaityti(int Nr[], int Tsk[], int &n)
{
    int m;
    ifstream in("knygos1.txt");
    in >> n;
    in >> m;
    for (int i = 0; i < n; i++)
    {
        int Tmp[12];
        in >> Nr[i];
        for (int j = 0; j < m; j++)
            in >> Tmp[j];
        Tsk[i] = maziausia(Tmp, m) + didziausia(Tmp, m);
    }
}

void rusiuoti(int Nr[], int Tsk[], int n)
{
    int tmp;
    for (int i = 0; i < n - 1; i++)
        for (int j = i; j < n; j++)
            if(Nr[j] < Nr[i])
            {
                tmp = Nr[i];
                Nr[i] = Nr[j];
                Nr[j] = tmp;
                tmp = Tsk[i];
                Tsk[i] = Tsk[j];
                Tsk[j] = tmp;
            }
}

void sukeisti(int Nr[], int Tsk[], int n, int min, int max)
{
    int minPos, maxPos, tmp;
    for (int i = 0; i < n; i++)
        if (Tsk[i] == min)
        {
            minPos = i;
            break;
        }
    for (int i = 0; i < n; i++)
        if (Tsk[i] == max)
        {
            maxPos = i;
            break;
        }
    tmp = Nr[minPos];
    Nr[minPos] = Nr[maxPos];
    Nr[maxPos] = tmp;
    tmp = Tsk[minPos];
    Tsk[minPos] = Tsk[maxPos];
    Tsk[maxPos] = tmp;
}

void isvestiBlogiausias(int Nr[], int Tsk[], int n, int min, ofstream& out)
{
    out << "Blogiausiai ávertintos knygos:" << endl;
    for (int i = n - 1; i >= 0; i--)
        if (Tsk[i] == min)
            out << Nr[i] << " ";
    out << endl;
}

void isvestiGeriausias(int Nr[], int Tsk[], int n, int max, ofstream& out)
{
    out << "Geriausiai ávertintos knygos:" << endl;
    for (int i = 0; i < n; i++)
        if (Tsk[i] == max)
            out << Nr[i] << " ";
    out << endl;
}

void isvestiSarasa(int Nr[], int Tsk[], int n, ofstream& out)
{
    for (int i = 0; i < n; i++)
        out << Nr[i] << " " << Tsk[i] << endl;
}

int maziausia(int Arr[], int n)
{
    int min = 99999;
    for (int i = 0; i < n; i++)
        if (Arr[i] < min)
            min = Arr[i];
    return min;
}

int didziausia(int Tsk[], int n)
{
    int max = 0;
    for (int i = 0; i < n; i++)
        if (Tsk[i] > max)
            max = Tsk[i];
    return max;
}
