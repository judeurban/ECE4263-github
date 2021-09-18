#include <iostream>
#include "main.h"
#include <string.h>
#include <sstream>
#include <curl/curl.h> //your directory may be different

using namespace std;    // std::cout, std::cin

void PrintGradient(string);
void PrintBG(string, int, int);
void Print(string, int);
void APIcall(void);

string rcvd_buffer;

int main()
{
    stringstream buf;    
    // Print("hello world", BLUE);
    // PrintBG("   Hello World     ", BLACK, BLUE);
    buf << "Text" << endl;
    APIcall();
}

void APIcall()
{
    string buffer[200];
    string api_key = "3c5c7dcd8ea2d74cfc1a7ee295286488";
    string zip_code = "74055";
    stringstream url;

    url << "api.openweathermap.org/data/2.5/weather?zip=" << zip_code << "&appid=" << api_key;

    // api.openweathermap.org/data/2.5/weather?zip={zip code},{country code}&appid={API key}
    // string url[100] = "api.openweathermap.org/data/2.5/weather?zip=&appid=";
    // url.insert(ZIPCODE_COL, zip_code);
    // url.insert(KEY_COL, api_key);

    cout << "api.openweathermap.org/data/2.5/weather?zip=74055&appid=3c5c7dcd8ea2d74cfc1a7ee295286488" << endl;
    cout << url.str() << endl;

    // url <<

// insert at zipcode 58
// insert at key 70

}

void PrintBG(string s, int foreground, int background)
{
    background += 10;
    cout << "\033[0;" << background << ";" << foreground << "m" << s << "\033[0m\n";
}

void Print(string s, int foreground)
{
    cout << "\033[0;" << foreground << "m" << s << "\033[0m\n";
}
