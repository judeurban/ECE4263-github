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

  if(curl)
  {
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.com/");
    response = curl_easy_perform(curl);

    if(response != CURLE_OK)
    {
      fprintf(stderr, "Request failed: %s\n", curl_easy_strerror(response));
      // cout << stderr << "Request Failed: " << curl_easy_strerror(response) << endl << endl;
      return 0;
    } 
    else
    {
    // fprintf("%s", response);
    cout << response << endl;
    }
    curl_easy_cleanup(curl);
  }

  curl_global_cleanup();
  return 0;
}