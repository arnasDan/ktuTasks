#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std;

struct zod
{
    string zodis;
    bool rastas;
};

void skaitytiKryziazodi(string Eilutes[], int &dydis);
void skaitytiZodzius(struct zod Zodz[], int &zodSk);
void spresti(struct zod Zodz[], string Eilutes[], int dydis, int zodSk, string EilRez[]);
bool ieskotiHorizontaliai(string Eilutes[], string zodis, int pos, int eilute, string EilRez[]);
bool ieskotiVertikaliai(string Eilutes[], string zodis, int pos, int eilute, string EilRez[], int dydis);
bool ieskotiIstrizai(string Eilutes[], string zodis, int pos, int eilute, string EilRez[], int dydis);
void isvesti(string EilRez[], int dydis);

int main()
{
    zod Zodz[1000];
    setlocale(LC_ALL, "Lithuanian");
    string Eilutes[1000];
    int dydis, zodSk;
    skaitytiKryziazodi(Eilutes, dydis);
    string EilRez[1000];
    for (int i = 0; i < dydis; i++)
    {
        EilRez[i] = string (dydis, '+');;
    }
    skaitytiZodzius(Zodz, zodSk);
    spresti(Zodz, Eilutes, dydis, zodSk, EilRez);
    isvesti(EilRez, dydis);
    return 0;
}

void skaitytiKryziazodi(string Eilutes[], int &dydis)
{
    ifstream in("Kryziazodis.txt");
    in >> dydis;
    in.ignore(256, '\n');
    for (int i = 0; i < dydis; i++)
    {
        getline(in, Eilutes[i], '\n');
        Eilutes[i].erase(remove(Eilutes[i].begin(), Eilutes[i].end(), ' '), Eilutes[i].end()); //debug cout << Eilutes[i] << endl;
    }
}

void skaitytiZodzius(struct zod Zodz[], int &zodSk)
{
    ifstream in("Zodziai.txt");
    in >> zodSk;
    for (int i = 0; i < zodSk; i++)
    {
        in >> Zodz[i].zodis;
        Zodz[i].rastas = false;
    }
}

void spresti(struct zod Zodz[], string Eilutes[], int dydis, int zodSk, string EilRez[])
{
    for (int i = 0; i < dydis; i++)
    {
        for (int j = 0; j < zodSk; j++)
        {
            int pos = 0;
            while (Eilutes[i].find(Zodz[j].zodis[0], pos) != string::npos && !Zodz[j].rastas)
            {
                pos = Eilutes[i].find(Zodz[j].zodis[0], pos); //debug cout << Eilutes[i] << " " << Zodz[j].zodis[0] << " " << pos << endl;
                Zodz[j].rastas = ieskotiHorizontaliai(Eilutes, Zodz[j].zodis, pos, i, EilRez);
                if (Zodz[j].rastas)
                    break;
                Zodz[j].rastas = ieskotiVertikaliai(Eilutes, Zodz[j].zodis, pos, i, EilRez, dydis);
                if (Zodz[j].rastas)
                    break;
                Zodz[j].rastas = ieskotiIstrizai(Eilutes, Zodz[j].zodis, pos, i, EilRez, dydis);
                pos++;
            }
        }
    }
}

bool ieskotiHorizontaliai(string Eilutes[], string zodis, int pos, int eilute, string EilRez[])
{
    if (Eilutes[eilute].find(zodis, pos - 1) == string::npos)
    {
        string patkr = "";
        int i = 0;
        while(i < zodis.length() && pos-i >= 0)
        {
            patkr += Eilutes[eilute][pos-i];
            i++;
        }
        if (patkr == zodis)
        {
            EilRez[eilute].replace(pos - ((int) zodis.length() - 1), pos + 1, Eilutes[eilute], pos - ((int) zodis.length() - 1), pos + 1);
            return true;
        }
        else
            return false;
    }
    else
    {
        EilRez[eilute].replace(pos, zodis.length(), zodis);
        return true;
    }
}

bool ieskotiVertikaliai(string Eilutes[], string zodis, int pos, int eilute, string EilRez[], int dydis)
{
    string patkr;
    if (eilute + ((int) zodis.length() - 1) <= dydis)
    {
        patkr = "";
        int i = eilute;
        for (int i = eilute; i < zodis.length(); i++)
        {
            patkr += Eilutes[i][pos];
        }
        if (patkr == zodis)
        {
            for (int i = eilute; i < zodis.length(); i++)
            {
                EilRez[i][pos] = Eilutes[i][pos];
            }
            return true;
        }
    }
    if (eilute - ((int) zodis.length() - 1) >= 0)
    {
        patkr = "";
        for (int i = 0; i < zodis.length(); i++)
        {
            patkr += Eilutes[eilute-i][pos];
        }
        if (patkr == zodis)
        {
            for (int i = 0; i < zodis.length(); i++)
            {
                EilRez[eilute-i][pos] = Eilutes[eilute-i][pos];
            }
            return true;
        }
    }
    return false;
}

bool ieskotiIstrizai(string Eilutes[], string zodis, int pos, int eilute, string EilRez[], int dydis)
{
    string patkr;
    if (eilute + ((int) zodis.length() - 1) <= dydis && pos + ((int) zodis.length() - 1) <= dydis) //SE
    {
        patkr = "";
        for (int i = 0; i < zodis.length(); i++)
        {
            patkr += Eilutes[eilute+i][pos+i];
        }
        if (patkr == zodis)
        {
            for (int i = 0; i < zodis.length(); i++)
            {
                EilRez[eilute+i][pos+i] = Eilutes[eilute+i][pos+i];
            }
            return true;
        }
    }
    if (eilute + ((int) zodis.length() - 1) <= dydis && pos - ((int) zodis.length() - 1) >= 0) //SW
    {
        patkr = "";
        for (int i = 0; i < zodis.length(); i++)
        {
            patkr += Eilutes[eilute+i][pos-i];
        }
        if (patkr == zodis)
        {
            for (int i = 0; i < zodis.length(); i++)
            {
                EilRez[eilute+i][pos-i] = Eilutes[eilute+i][pos-i];
            }
            return true;
        }
    }
    if (eilute - ((int) zodis.length() - 1) >= 0 && pos + ((int) zodis.length() - 1) <= dydis) //NE
    {
        patkr = "";
        for (int i = 0; i < zodis.length(); i++)
        {
            patkr += Eilutes[eilute-i][pos+i];
        }
        if (patkr == zodis)
        {
            for (int i = 0; i < zodis.length(); i++)
            {
                EilRez[eilute-i][pos+i] = Eilutes[eilute-i][pos+i];
            }
            return true;
        }
    }
    if (eilute - ((int) zodis.length() - 1) >= 0 && pos - ((int) zodis.length() - 1) >= 0) //NW
    {
        patkr = "";
        for (int i = 0; i < zodis.length(); i++)
        {
            patkr += Eilutes[eilute-i][pos-i];
        }
        if (patkr == zodis)
        {
            for (int i = 0; i < zodis.length(); i++)
            {
                EilRez[eilute-i][pos-i] = Eilutes[eilute-i][pos-i];
            }
            return true;
        }
    }
    return false;
}

void isvesti(string EilRez[], int dydis)
{
    ofstream out("Rezultatai.txt");
    for(int i = 0; i < dydis; i++)
    {
        int pos = 0;
        while(EilRez[i].find_first_not_of(" \n", pos) != string::npos)
        {
            pos = EilRez[i].find_first_not_of(" \n", pos);
            EilRez[i].insert(pos + 1, " ");
            pos += 2;
        }
        out << EilRez[i] << endl;
    }
}
