#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

void trukme(int &min, int &max, double medvKg, double ktKg);
void kaina(double &min, double &max, double valKaina, int minT, int maxT);

int main()
{
    setlocale(LC_ALL, "Lithuanian");
    int studSk, minT, maxT, maxVT, maxStudSk = 0;
    double medvKg, ktKg, valKaina, minK, maxK;
    ifstream in("Duomenys5.txt");
    in >> studSk >> valKaina;
    maxVT = 12*60*3;
    ofstream out("Rezultatai5.txt");
    for (int i = 0; i < studSk; i++)
    {
        in >> medvKg >> ktKg;
        trukme(minT, maxT, medvKg, ktKg);
        kaina(minK, maxK, valKaina, minT, maxT);
        out << fixed << setprecision(2) << minT << "-" << maxT << " " << minK << "-" << maxK << endl;
        maxVT -= maxT;
        if (maxVT >= 0)
            maxStudSk++;
    }
    out << "Rûbus suspës iðskalbti: " << maxStudSk << " studentai" << endl;
    return 0;
}

void trukme(int &min, int &max, double medvKg, double ktKg)
{
    int minMedv = 55, maxMedv = 65;
    int minKt = 45, maxKt = 55;
    int skMedv = ceil(medvKg / 5);
    int skKt = ceil(ktKg / 5);
    min = skMedv * minMedv + skKt * minKt;
    max = skMedv * maxMedv + skKt * maxKt;
}

void kaina(double &min, double &max, double valKaina, int minT, int maxT)
{
    min = (double) minT / 60 * valKaina;
    max = (double) maxT / 60 * valKaina;
}
