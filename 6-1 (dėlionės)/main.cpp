#include <iostream>
#include <fstream>

using namespace std;

void skaityti(int &n, int Dal[]);
void isvestiLikucius(int Dal[], ofstream &out);
int delioniuSkaicius(int n, int Dal[]);

int main()
{
    int n, Dal[4] = {0};
    ofstream out("U1rez.txt");
    skaityti(n, Dal);
    out << delioniuSkaicius(n, Dal) << endl;
    isvestiLikucius(Dal, out);
    return 0;
}

void skaityti(int &n, int Dal[])
{
    int tmp;
    ifstream in("U1.txt");
    in >> n;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < 4; j++)
        {
            in >> tmp;
            Dal[j] += tmp;
        }
}

int delioniuSkaicius(int n, int Dal[])
{
    int sk = 0, rm;
    for (int i = 0; i < n; i++)
        if (Dal[0] >= 2 && Dal[1] >= 2 && Dal[2] >= 4 && Dal[3] >= 4)
        {
            rm = 2;
            sk++;
            for (int j = 0; j < 4; j++)
            {
                Dal[j] -= rm;
                if (j == 1)
                    rm = 4;
            }
        }
        else
            return sk;
}

void isvestiLikucius(int Dal[], ofstream &out)
{
    for (int i = 0; i < 4; i++)
        out << Dal[i] << endl;
}
