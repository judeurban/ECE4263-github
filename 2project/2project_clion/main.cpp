#include <iostream>
#include <string.h>
#include <sstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include "main.h"

using namespace std;    // std::cout, std::cin
using json = nlohmann::json;

void PrintGradient(string);
void PrintBG(string, int, int);
void Print(string, int);
void APIcall(void);
void httpGet(string);

std::string rcvd_buffer;
CURL *curl;
CURLcode response;


int main()
{
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    stringstream buf;
    APIcall();
}

void APIcall()
{
    string buffer[200];
    string api_key = "3c5c7dcd8ea2d74cfc1a7ee295286488";
    string zip_code = "74055";
    stringstream url;

    url << "api.openweathermap.org/data/2.5/weather?zip=" << zip_code << "&appid=" << api_key;

    httpGet(url.str());

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

void httpGet(string url)
{

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        response = curl_easy_perform(curl);

        if(response != CURLE_OK)
        {
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
            // cout << stderr << "Request Failed: " << curl_easy_strerror(response) << endl << endl;
            return;
        } 
        else
        {
            // fprintf("%s", response);
            cout << response << endl;
        }
        curl_easy_cleanup(curl);
    }
    
    curl_global_cleanup();
}
