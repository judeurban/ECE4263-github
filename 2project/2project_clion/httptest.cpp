#include <stdio.h>
#include <curl/curl.h>
#include <iostream>

using namespace std;

int main()
{
    CURL *curl;
    CURLcode response;
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();

    cout << "hello "<< endl;

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com/");
        response = curl_easy_perform(curl);

        if(response != CURLE_OK)
        {
            fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
            return 0;
        }
//        cout << response << endl;
    }



}