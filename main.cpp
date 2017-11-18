#include <stdio.h>
#include <curl/curl.h>

int main(int argc, char* argv[])
{
    if(argc < 2){
        cout << "Нет параметра" << endl;
        return 0;
    }

    char* name = argv[1];
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, name);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_NOBODY, true);

        res = curl_easy_perform(curl);

        if(res != CURLE_OK){
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }
        else {
            char *url = NULL;
            curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);
            if(url){
                printf("Redirect to: %s\n", url);
            }
            
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            printf("Response code: %ld\n", response_code);
        }

        curl_easy_cleanup(curl);
    }
    return 0;
}
