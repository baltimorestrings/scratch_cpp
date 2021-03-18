#include <iostream>
#include <curl/curl.h>
#include <vector>
#include <string>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

void die(const char* msg)  {
    std::cout << msg;
    exit(1);
}

int main(int argc, char **argv) {
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string baseUrl = "https://moog.vzbuilders.com/graze/v1/getSituationDetails?sitn_id=";
    const char* gUser = std::getenv("GRAZE_USER");
    const char* gPass = std::getenv("GRAZE_PASS");
    // Check arguments and env-vars
    if (argc != 2) {
        die("Please supply a situation ID.\n");
    }
    try { 
        std::stoi(argv[1]); 
    } catch (std::exception) {
        die("Please provide an integer argument.\n");
    }
    if (!gUser || !gPass) {
        die("env vars not found.\n");
    }
    
    baseUrl += argv[1];
    

    curl  = curl_easy_init();
    if (curl) {
        std::cout << baseUrl << std::endl;
        curl_easy_setopt(curl, CURLOPT_URL, baseUrl.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long) CURLAUTH_BASIC);
        curl_easy_setopt(curl, CURLOPT_USERNAME, gUser);
        curl_easy_setopt(curl, CURLOPT_PASSWORD, gPass);
        res  = curl_easy_perform(curl);
        std::cout << readBuffer << std::endl;
        curl_easy_cleanup(curl);
    }
    return 0;
}


