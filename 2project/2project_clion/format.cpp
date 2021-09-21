#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include <time.h>

using namespace std;

int main()
{
    
    time_t curtime = time(0);

    cout << curtime << endl;

    return 0;
}