#include <iostream>
#include <iomanip>

using namespace std;

void greitis(double t, double &v1, double &v2, double a1, double a2);

int main()
{
    double v1, v2, a1, a2, t;
    cout << "Iveskite matavimo laika bei abieju traukiniu nuvaziuotus atstumus: " << endl;
    cin >> t >> a1 >> a2;
    greitis (t, v1, v2, a1, a2);
    cout << fixed << setprecision (2) << "Pirmo traukinio greitis: " << v1 << endl;
    cout << fixed << setprecision (2) << "Antro traukinio greitis: " << v2 << endl;
    return 0;
}

void greitis(double t, double &v1, double &v2, double a1, double a2)
{
        v1 = a1 / 1000 / (t / 3600);
        v2 = a2 / 1000 / (t / 3600);
}
