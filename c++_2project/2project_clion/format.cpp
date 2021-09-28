#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include <time.h>

using namespace std;

char weatherSwitch;                   // description in main.h

int main()
{

    char buff[20];
    time_t now = time(NULL);
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));
    cout << buff << endl;

    return 0;
}


/*
    string description = "few clouds";
    string ;
    std::cin >> look;
    std::string::size_type pos = test.find(look);
    while (pos != std::string::npos)
    {
        // Found!
        std::cout << "found at : " << pos << std::endl;
        pos = test.find(look, pos + 1);
    }
*/