#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include<fstream>
#include "main.h"

// namespaces

using namespace std;
using json = nlohmann::json;

// functions

void PrintGradient(string);
void PrintBG(string, int, int);
void Print(string, int);
void APIcall(void);
void httpGet(string);
static size_t WriteCallback(void *, size_t, size_t, void *);
void replacebracketwithspace(void); //why tf do I need this??
void ArtPrint(char);

// classes/objects
CURL *curl;
CURLcode response;
json json_response;

// variables
string readBuffer;

struct MainWeather
{
    int feels_like;
    int humidity;
    int pressure;
    int temp;
    int temp_max;
    int temp_min;
};

struct Wind
{
    int deg;
    int speed;
};

struct Coordinates
{
    int lat;
    int lon;
};

class Weather
{
private:
    /* data */
public:
    // independent variables
    string name;
    std::string description;
    int visibility;
    
    // structs
    MainWeather main;
    Wind wind;
    Coordinates coordinates;

    void UpdateWeather(void)
    {
        json_response = json::parse(readBuffer);

        // strings
        this->name = json_response["name"].get<string>();
        this->description = json_response["weather"]["description"].get<string>();

        // integers
        this->visibility = json_response["visibility"].get<int>();

        // main weather struct
        this->main.feels_like = json_response["main"]["feels_like"].get<int>();
        this->main.humidity = json_response["main"]["humidity"].get<int>();
        this->main.pressure = json_response["main"]["pressure"].get<int>();
        this->main.temp = json_response["main"]["temp"].get<int>();
        this->main.temp_max = json_response["main"]["temp_max"].get<int>();
        this->main.temp_min = json_response["main"]["temp_min"].get<int>();

        // wind struct
        this->wind.deg = json_response["wind"]["deg"].get<int>();
        this->wind.speed = json_response["wind"]["speed"].get<int>();

        // coordinates struct
        this->coordinates.lat = json_response["coord"]["lat"].get<int>();
        this->coordinates.lon = json_response["coord"]["lon"].get<int>();
    }

    void Print(void)
    {
        // strings
        cout << "name:" << this->name << endl;
        cout << "description: " << this->description << endl;

        // integers
        cout << "visibility: " << this->visibility << endl;

        // main weather struct
        cout << "feels_like: " << this->main.feels_like << endl;
        cout << "humidity: " << this->main.humidity << endl;
        cout << "pressure: " << this->main.pressure << endl;
        cout << "temp (Kelvin): " << this->main.temp << endl;
        cout << "temp_max: " << this->main.temp_max << endl;
        cout << "temp_min: " << this->main.temp_min << endl;

        // wind struct
        cout << "wind direction: " << this->wind.deg << endl;
        cout << "wind speed: " << this->wind.speed << endl;

        // coordinates struct
        cout << "location lat: " << this->coordinates.lat << endl;
        cout << "location lon: " << this->coordinates.lon << endl;

    }
};

int main()
{
    system("clear");
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    stringstream buf;
    APIcall();

    Weather weather;

    weather.UpdateWeather();
    // weather.Print();

    ArtPrint('s');

    // Print(weather.description, BLUE);


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
    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        // curl_easy_setopt(curl, CURLOPT_NOBODY, 1);

        response = curl_easy_perform(curl);
        
        if(response != CURLE_OK)
        {
            // cout << stderr << "Request Failed: " << curl_easy_strerror(response) << endl << endl;
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
            return;
        } 

        curl_easy_cleanup(curl);
    }
    
    curl_global_cleanup();
    replacebracketwithspace();      //my json libarary exploded when a pair of '[]' showed up
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

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void replacebracketwithspace(void)
{
    for (int i = 0; i <= readBuffer.length(); i++)
    {
        if (readBuffer[i] == '[' || readBuffer[i] == ']')
        {
            readBuffer[i] = ' ';
        }
    }
}

float Kelvin2Fahrenheit(float degKelvin)
{
    return ( (degKelvin - 273.15) * 9 / 5 ) + 32;
}

void ArtPrint(char c)
{
    int COLOR = WHITE;
    string filename;
    ifstream file;
    string text;

    switch (c)
    {
    case 'm':
        file.open("moon.txt");
        break;
    case 'p':
        file.open("moonphases.txt");
        break;
    case 'r':
        file.open("rain.txt");
        COLOR = BLUE;
        break;
    case 'w':
        file.open("snow.txt");
        break;
    case 's':
        file.open("sunny.txt");
        COLOR = YELLOW;
        break;
    case 't':
        file.open("thunderstorm.txt");
        COLOR = BLUE;
        break;
    case 'n':
        file.open("tornado.txt");
        COLOR = BLACK;
    default:
        file.close();
        return;
    }


    while(getline(file,text))
    {
        Print(text, COLOR);
        // cout << text << endl;
    }
    file.close();

}
