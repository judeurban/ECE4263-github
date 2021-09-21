#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include<fstream>
#include "main.h"

// namespaces

using json = nlohmann::json;
using namespace std;

// functions

void PrintGradient(std::string);
void PrintBG(std::string, int, int);
void Print(std::string, int);
void APIcall(void);
void httpGet(std::string);
static size_t WriteCallback(void *, size_t, size_t, void *);
void replacebracketwithspace(void); //why tf do I need this??
void SetWeatherSwitch(void);
float Kelvin2Fahrenheit(float);

// classes/objects
CURL *curl;
CURLcode response;
json json_response;

// variables
std::string readBuffer;
std::string zip_code;
bool isActive = true;

struct WeatherSwitch
{
    const char * types[10] = {"sun", "cloud", "rain", "fog", "clear", "snow", "storm", "tornado"};
    uint8_t current;         //holds the current TRUE value of type
};

struct MainWeather
{
    int humidity;
    int pressure;
    float feels_like;
    float temp;
    float temp_max;
    float temp_min;
};

struct Sys
{
    std::string country;
    time_t sunrise;
    time_t sunset;
};

struct Wind
{
    int deg;
    float speed;
};

struct Coordinates
{
    float lat;
    float lon;
};

class Weather
{
private:

    void SetWeatherSwitch()
    {
        std::string::size_type position;

        // .length() doesn't work on an array of strings
        int array_len = sizeof(this->weatherswitch.types) / sizeof(this->weatherswitch.types[0]);

        // find weather description
        for (int i = 0 ; i <= array_len ; i++)
        {
            position = this->description.find(this->weatherswitch.types[i]);
            if (position == std::string::npos)
            {
                // not found
                continue;
            }
            else 
            {
                // found
                this->weatherswitch.current = i;
                return;
            }
        }
    }

public:
    // independent variables
    bool isMetric;
    bool isDaytime;
    std::string name;
    std::string description;

    int visibility;
    
    // structs
    MainWeather main;
    Sys sys;
    Wind wind;
    Coordinates coordinates;
    WeatherSwitch weatherswitch;

    void UpdateWeather(void)
    {
        json_response = json::parse(readBuffer);

        // strings
        this->name = json_response["name"].get<std::string>();
        this->description = json_response["weather"]["description"].get<std::string>();

        // integers
        this->visibility = json_response["visibility"].get<int>();

        // time
        this->sys.country = json_response["sys"]["country"].get<std::string>();
        this->sys.sunrise = json_response["sys"]["sunrise"].get<int>();
        this->sys.sunset = json_response["sys"]["sunset"].get<int>();

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

        // if(SysTime > Sunrise && SysTime < Sunset) daytime = true;

        if(time(0) > this->sys.sunrise && time(0) < this->sys.sunset)
            this->isDaytime = true;
        else 
            this->isDaytime = false;

        SetWeatherSwitch();
        SetImperialMetric();

        //find country, convert to F or C
        if(this->isMetric)
        {
            //celsius
            this->main.feels_like -= 273.15;
            this->main.temp -= 273.15;
            this->main.temp_max -= 273.15;
            this->main.temp_min -= 273.15;
        }
        else
        {
            //fahrenheit
            this->main.feels_like = Kelvin2Fahrenheit(this->main.feels_like);
            this->main.temp = Kelvin2Fahrenheit(this->main.temp);
            this->main.temp_max = Kelvin2Fahrenheit(this->main.temp_max);
            this->main.temp_min = Kelvin2Fahrenheit(this->main.temp_min);
        }
    }

    void PrintClass(void);
    void ArtPrint();
    void PrintFormatted();
    void SetImperialMetric(void);
};


int main()
{
    system("clear");
    Weather weather;
    time_t check_time = time(0);

    cout << "Enter Zip Code: " ;
    cin >> zip_code; 

    while(isActive)
    {
        if(time(0) >= check_time)
        {
            system("clear");

            // internet stuff
            curl_global_init(CURL_GLOBAL_ALL);
            curl = curl_easy_init();
            
            APIcall();

        if (readBuffer.length() <= 50)
        {
            cout << "404 - city not found" << endl;
            isActive = false;
            break;
        }

            weather.UpdateWeather();
            weather.ArtPrint();
            // weather.PrintClass();
            weather.PrintFormatted();
            
            check_time += REQUEST_PERIOD*60;
        }
    }
    
}

void APIcall()
{
    std::string buffer[200];
    std::string api_key = "3c5c7dcd8ea2d74cfc1a7ee295286488";
    stringstream url;

    url << "api.openweathermap.org/data/2.5/weather?zip=" << zip_code << "&appid=" << api_key;

    try
    {
        httpGet(url.str());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        cout << "Check internet connection or invalid Zip Code" << endl;
    }
}

void httpGet(std::string url)
{
    readBuffer.clear();

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
        // cout << readBuffer << endl;

        curl_easy_cleanup(curl);
    }
    
    curl_global_cleanup();
    replacebracketwithspace();      //my json libarary exploded when a pair of '[]' showed up lol
}

void PrintBG(std::string s, int foreground, int background)
{
    background += 10;
    cout << "\033[0;" << background << ";" << foreground << "m" << s << "\033[0m\n";
}

void Print(std::string s, int foreground)
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

void Weather::ArtPrint()
{
    int COLOR;

    if(this->isDaytime)
    {
        COLOR = YELLOW;
    }
    else
    {
        COLOR = BLUE;
    }

    std::string filename;
    ifstream file;
    std::string text;

    switch (this->weatherswitch.current)
    {
    // case "sun":
    case 0:
        if(!this->isDaytime) return;
        file.open("sunny.txt");
        COLOR = YELLOW;
        break;
    // case "clouds":
    case 1:
        if(this->isDaytime) COLOR = WHITE;
        file.open("clouds.txt");
        break;
    // case "rain":
    case 2:
        file.open("rain.txt");
        COLOR = BLUE;
        break;
    // case "fog":
    case 3:
        break;
    // case "clear":
    case 4:
        if(this->isDaytime)
        {
            COLOR = YELLOW;
            file.open("sunny.txt");
        }
        else
        {
            COLOR = BLUE;
            file.open("moon.txt");
        }
        break;
    // case "snow":
    case 5:
        file.open("snow.txt");
        COLOR = WHITE;
        break;
    // case "storm":
    case 6:
        file.open("thunderstorm.txt");
        COLOR = YELLOW;
        break;
    // case "tornado":
    case 7:
        file.open("tornado.txt");
        COLOR = BLACK;
    default:
        if(file.is_open())
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

void Weather::PrintClass()
{
    // strings
    cout << endl << endl;
    cout << "name: " << this->name << endl;
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

    if(this->isDaytime)
        cout << "time of day: day" << endl;
    else
        cout << "time of day: night" << endl;

    if(this->isMetric)
        cout << "Using Metric units" << endl;
    else
        cout << "Using Imperial units" << endl;

}

void Weather::SetImperialMetric()
{
    if(this->sys.country.find("US") == std::string::npos)       
        isMetric = true;                                        //NOT USA
    else                                                        
        isMetric = false;                                       //USA
}

void Weather::PrintFormatted()
{
    char datetime[20];
    time_t now = time(NULL);
    strftime(datetime, 20, "%Y-%m-%d %H:%M:%S", localtime(&now));

    cout << endl << endl;
    cout << "Current Date/Time: " << datetime << endl;
    cout << "LOCATION: " << this->name << endl;
    cout << "DESCRIPTION: " << this->description << endl;
    cout << "PRESSURE: " << this->main.pressure <<  " mb" << endl;

    cout << "FEELS LIKE: " << this->main.feels_like << "º F" << endl;
    cout << "TEMPERATURE: " << this->main.temp << "º F" << endl;
    cout << "HIGH TEMPERATURE: " << this->main.temp_max << "º" << endl;
    cout << "LOW TEMPERATURE: " << this->main.temp_min << "º" << endl;
}
