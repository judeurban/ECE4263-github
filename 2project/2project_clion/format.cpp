#include<iostream>
#include<fstream>
#include<cstdlib>
#include<iomanip>
#include <time.h>

using namespace std;

char weatherType;                   // description in main.h

int main()
{
    // string description = "hot and sunny";
    string description = "few clouds";

    std::string::size_type pos = description.find("sun");

    

    if (pos == std::string::npos)
    {
        cout << "did not find the string..." << endl;
    }
    else 
    {
    cout << "position is: " << pos << endl;
    }

    pos = description.find("cloud");
    cout << "position is: " << pos << endl;

    cout << "weathertype is: " << weatherType << endl;



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