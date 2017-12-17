#include <iostream>
#include <fstream>

using namespace std;

void zaisti(int Tsk[], int Zaid[], int &n);
void isvestiZaidejus(int Tsk[], int Zaid[], int n, ofstream& out);
void isvestiMaziausius(int Tsk[], int Zaid[], int n, int min, ofstream& out);
void isvestiDidziausius(int Tsk[], int Zaid[], int n, int max, ofstream& out);
void iterpti(int Tsk[], int Zaid[], int &n, int min, int max);
void iterptiIMasyva(int Arr[], int &n, int sk, int pos);
void rastiMinMaxVietas(int Tsk[], int n, int min, int max, int &posMin, int &posMax);
int maziausia(int Tsk[], int n);
int didziausia(int Tsk[], int n);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    ofstream out("zaidimas1rez.txt");
    int Tsk[22], Zaid[22], n, min, max;
    zaisti(Tsk, Zaid, n);
    min = maziausia(Tsk, n);
    max = didziausia(Tsk, n);
    out << "Þaidëjai ir jø surinkti taðkai:" << endl;
    isvestiZaidejus(Tsk, Zaid, n, out);
    isvestiMaziausius(Tsk, Zaid, n, min, out);
    isvestiDidziausius(Tsk, Zaid, n, max, out);
    iterpti(Tsk, Zaid, n, min, max);
    out << "Po áterpimo:" << endl;
    isvestiZaidejus(Tsk, Zaid, n, out);
    return 0;
}

void zaisti(int Tsk[], int Zaid[], int &n)
{
    int nEj, tmp1, tmp2, cntr = 1;
    ifstream in("zaidimas1.txt");
    in >> nEj;
    for (n = 0; n < nEj; n++)
    {
        in >> tmp1 >> tmp2;
        if (tmp1 == Zaid[0])
            break;
        Zaid[n] = tmp1;
        Tsk[n] = tmp2;
    }
    if (tmp1 == Zaid[0])
    {
        tmp2 += Zaid[0];
        nEj -= n + 1;
        for (int i = 0; i < nEj; i++)
        {
            in >> tmp1 >> tmp2;
            Tsk[cntr] += tmp2;
            if (cntr + 1 ==
                 n)
                cntr = 0;
            else
                cntr++;
        }
    }
}

void isvestiZaidejus(int Tsk[], int Zaid[], int n, ofstream& out)
{
    for (int i = 0; i < n; i++)
        out << Zaid[i] << " " << Tsk[i] << endl;
}

void isvestiMaziausius(int Tsk[], int Zaid[], int n, int min, ofstream& out)
{
    out << "Maþiausiai taðkø surinko:" << endl;
    for (int i = n - 1; i >= 0; i--)
        if (Tsk[i] == min)
            out << Zaid[i] << " ";
    out << endl;
}

void isvestiDidziausius(int Tsk[], int Zaid[], int n, int max, ofstream& out)
{
    out << "Daugiausiai taðkø surinko:" << endl;
    for (int i = 0; i < n; i++)
        if (Tsk[i] == max)
            out << Zaid[i] << " ";
    out << endl;
}

void iterpti(int Tsk[], int Zaid[], int &n, int min, int max)
{
    int posMax, posMin;
    rastiMinMaxVietas(Tsk, n, min, max, posMin, posMax);
    iterptiIMasyva(Tsk, n, Tsk[posMax], posMin);
    iterptiIMasyva(Zaid, n, Zaid[posMax], posMin);
    n++;
    rastiMinMaxVietas(Tsk, n, min, max, posMin, posMax);
    iterptiIMasyva(Tsk, n, Tsk[posMin], posMax);
    iterptiIMasyva(Zaid, n, Zaid[posMin], posMax);
    n++;
}

void iterptiIMasyva(int Arr[], int &n, int sk, int pos)
{
    for (int i = n; i > pos; i--)
        Arr[i] = Arr[i - 1];
    Arr[pos] = sk;
}

void rastiMinMaxVietas(int Tsk[], int n, int min, int max, int &posMin, int &posMax)
{
    for (int i = 0; i < n; i++)
        if (Tsk[i] == max)
        {
            posMax = i;
            break;
        }
    for (int i = n - 1; i >= 0; i--)
        if (Tsk[i] == min)
        {
            posMin = i;
            break;
        }
}

int maziausia(int Tsk[], int n)
{
    int min = 9999;
    for (int i = 0; i < n; i++)
        if (Tsk[i] < min)
            min = Tsk[i];
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
