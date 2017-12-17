#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct stotis
{
    string pav;
    double Tmp[100];
    double vid;
    int nr;
};

struct metai
{
    int pr;
    int n;
};

void skaityti(vector <stotis> &St, struct metai &m);
void isvesti(vector <stotis> St, struct metai m);
void rusiuoti(vector <stotis> &St);
void salintiAuksciausia(vector <stotis> &St);
void isvestiSarasa(vector <stotis> St, ofstream &out, string trp);
double vidurkis(double Tmp[], int n);
stotis maziausia(vector <stotis> St, int mN);
stotis didziausia(vector <stotis> St,  int mN);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    struct metai m;
    vector <stotis> St;
    skaityti(St, m);
    isvesti(St, m);
    return 0;
}

void skaityti(vector <stotis> &St, struct metai &m)
{
    int nSt, mGl;
    ifstream in("temperatura.txt");
    in >> nSt >> m.pr >> mGl;
    m.n = mGl - m.pr + 1;
    St.resize(nSt);
    for (int i = 0; i < nSt; i++)
        in >> St[i].pav;
    for (int i = 0; i < nSt; i++)
    {
        for (int j = 0; j < m.n; j++)
            in >> St[i].Tmp[j];
        St[i].vid = vidurkis(St[i].Tmp, m.n);
    }
}

void isvesti(vector <stotis> St, struct metai m)
{
    string trp = "---------------------------------------------\n";
    ofstream out("temperaturarez.txt");
    stotis tmp = maziausia(St, m.n);
    out << tmp.pav << " " << tmp.Tmp[tmp.nr] << " " << m.pr + tmp.nr << endl << trp;
    tmp = didziausia(St, m.n);
    out << tmp.pav << " " << tmp.Tmp[tmp.nr] << " " << m.pr + tmp.nr << endl << trp;
    isvestiSarasa(St, out, trp);
    rusiuoti(St);
    isvestiSarasa(St, out, trp);
    salintiAuksciausia(St);
    isvestiSarasa(St, out, trp);
}

void rusiuoti(vector <stotis> &St)
{
    for (int i = 0; i < St.size() - 1; i++)
        for (int j = i; j < St.size(); j++)
            if (St[i].vid > St[j].vid)
                swap(St[i], St[j]);
}

void salintiAuksciausia(vector <stotis> &St)
{
    int max = 0;
    for (int i = 0; i < St.size(); i++)
        if (St[i].vid > St[max].vid)
            max = i;
    St.erase(St.begin() + max);
}

void isvestiSarasa(vector <stotis> St, ofstream &out, string trp)
{
    for (int i = 0; i < St.size(); i++)
        out << St[i].pav << " " << fixed << setprecision(1) << St[i].vid << endl;
    out << trp;
}

stotis maziausia(vector <stotis> St, int mN)
{
    int minI = 0, minJ = 0;
    for (int i = 0; i < St.size(); i++)
        for (int j = 0; j < mN; j++)
            if (St[i].Tmp[j] < St[minI].Tmp[minJ])
            {
                minI = i;
                minJ = j;
            }
    stotis rtrn = St[minI];
    rtrn.nr = minJ;
    return rtrn;
}

stotis didziausia(vector <stotis> St,  int mN)
{
    int maxI = 0, maxJ = 0;
    for (int i = St.size() - 1; i >= 0; i--)
        for (int j = 0; j < mN; j++)
            if (St[i].Tmp[j] > St[maxI].Tmp[maxJ])
            {
                maxI = i;
                maxJ = j;
            }
    stotis rtrn = St[maxI];
    rtrn.nr = maxJ;
    return rtrn;
}

double vidurkis(double Tmp[], int n)
{
    double sum = 0;
    for (int i = 0; i < n; i++)
        sum += Tmp[i];
    return sum / n;
}
