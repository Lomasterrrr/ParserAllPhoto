#include <iostream>
#include <string>
#include "curl/curl.h"
#include <ctime>
#include <bits/stdc++.h> 
using namespace std;
static const char AlphaNumeric[] = "0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";
int MyLen = sizeof(AlphaNumeric) - 1;
char RandomStr() {
    return AlphaNumeric[rand() % MyLen];
}
string Generate(int l) {
    string result;
    int m;
    m = 0;
    while (m < l) {
        result = result + RandomStr();      
        m = m + 1;
    }
    return result;
}
size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}
void GrabPhotoStandart(string format, string site){
    int i = 0;
    srand(time(0));
    while (!false) {
        auto begin = std::chrono::steady_clock::now();
        string resultGen;
        resultGen = Generate(5);
        CURL *curl;
        FILE *fp;
        CURLcode res;
        string link;
        link = "https://" + site + "/" + resultGen + format;
        char arr[link.length() + 1]; 
	    strcpy(arr, link.c_str()); 
        string outFile;
        outFile = resultGen + format;
        char *url;
        url = arr;
        string outfilename[FILENAME_MAX] = {outFile};
        curl = curl_easy_init();
        const char *c = outFile.c_str();
        if (curl) {
            fp = fopen(c,"wb");
            curl_easy_setopt(curl, CURLOPT_URL, url);
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
            res = curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            fclose(fp);
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        cout << "  " << link << " | " << elapsed_ms.count() << " ms" << endl;
        i++;
    }
}
void MainMenu(){
    system("clear");
    string what;
    string what1;
    cout << "\n  ParseAllPhoto\n";
    cout << "  --------------------------------------------------\n";
    cout << "  Enter site (example: i.imgur.com): ";
    cin >> what;
    cout << "  Enter format (example: .png): ";
    cin >> what1;
    cout << "  --------------------------------------------------\n";
    GrabPhotoStandart(what1,what);
}   
int main () {
    MainMenu();
    return 0;
}