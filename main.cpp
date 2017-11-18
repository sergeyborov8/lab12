#include <iostream>
#include <future>
#include <thread>
#include <curl/curl.h>

int main(int argc, char *argv[]) {

    CURL *curl = curl_easy_init();

    std::string url;

    if (argc < 2) {
        std::cout << "enter: ";
        std::getline(std::cin, url);
    } else {
        url = argv[1];
    }

    if (curl) {

        curl_easy_setopt(curl, CURLOPT_URL, Url.c_str());
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT_MS, 3000);

        std::promise<CURLcode> promise;

        auto response = promise.get_future();

        std::thread request([curl, &promise]() {
            promise.set_value(curl_easy_perform(curl));
        });

        request.detach();

        long answer;

        auto res = response.get();

        if (res == CURLE_OK) {
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &answer);
            std::cout << answer << std::endl;
        }

        curl_easy_cleanup(curl);
    }
    return 0;
}
