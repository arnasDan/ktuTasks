#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void beTarpuVienaEilute(string &str, int &pos);
string skaityti();
string lauztiniaiSkliaustai(string str);
string beTarpu(string str);
string tabuliacija(string str);

int main()
{
    setlocale (LC_ALL, "Lithuanian");
    string kodas = skaityti();
    kodas = beTarpu(kodas);
    kodas = lauztiniaiSkliaustai(kodas);
    kodas = tabuliacija(kodas);
    ofstream out("Rez.txt");
    out << kodas;
    return 0;
}

string skaityti()
{
    ifstream in("Duom.txt");
    string str;
    getline(in, str, (char) in.eof());
    return str;
}

string beTarpu(string str)
{
    int pos = 0;
    while (str.find("\n", pos) != string::npos)
    {
        pos = str.find("\n", pos);
        beTarpuVienaEilute(str, pos);
    }
    return str;
}

void beTarpuVienaEilute(string &str, int &pos)
{
    int endpos = str.find_first_not_of(" ", pos+1) - 1;
    str.erase(pos+1, endpos-pos);
    pos++;
}

string lauztiniaiSkliaustai(string str)
{
    int pos = 0, add = 0;
    while (str.find_first_of("{}", pos) != string::npos)
    {
        pos = str.find_first_of("{}", pos);
        if (str[pos+1] != '\n')
        {
            str.insert(pos+1, "\n");
            add++;
        }
        if (str[pos-1] != '\n')
        {
            str.insert(pos, "\n");
            add++;
        }
        pos += add + 1;
        add = 0;
    }
    return str;
}

string tabuliacija(string str)
{
    int pos = 0, x = 0;
    while (str.find("\n", pos) != string::npos)
    {
        pos = str.find("\n", pos);
        if (str[pos+1] == ' ')
        {
            int prepos = pos;
            beTarpuVienaEilute(str, pos);
            pos = prepos;
        }
        if (str[pos+1] == '}')
            x--;
        str.insert(pos+1, 4*x, ' ');
        pos += 4*x;
        if (str[pos+1] == '{')
            x++;
        pos++;
    }
    return str;
}
