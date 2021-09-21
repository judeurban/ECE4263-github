#include <iostream>
#include <stdlib.h>
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
std::string readBuffer;

json json_response;

struct weather {
    string name;
    int visibility;
};

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

int main()
{
    system("clear");
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    stringstream buf;
    APIcall();
    json_response = json::parse(readBuffer);
    // cout << json_response.dump(4) << endl;

    // auto weatherobject = json_response.get<weather>();

    // cout << weatherobject.name << endl;

    weather weatherobject 
    {
        json_response["name"].get<string>(),
        json_response["visibility"].get<int>()
    };

    cout << weatherobject.name << endl;

    // cout << json_response.get<weather>() << endl;

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

void httpGet(string url)
{
    cout << "1" << endl;
    if(curl)
    {
        cout << "2" << endl;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        // curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
        cout << "3" << endl;

        response = curl_easy_perform(curl);
        
        cout << "4" << endl;

        if(response != CURLE_OK)
        {
            // cout << stderr << "Request Failed: " << curl_easy_strerror(response) << endl << endl;
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
            return;
        } 
        else
        {
            // fprintf("%s", response);
            // cout << response << endl;
            // cout << readBuffer << endl;
        }
        curl_easy_cleanup(curl);
    }
    
    curl_global_cleanup();
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

