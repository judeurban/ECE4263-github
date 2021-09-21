#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>

using namespace std;

int main()
{
    string filename;
    ifstream file;
    string text;

    file.open("moonphases.txt");

    while(getline(file,text))
    {
        cout << text << endl;
    }
    file.close();

    return 0;
}