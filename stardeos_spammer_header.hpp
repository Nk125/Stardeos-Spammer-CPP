#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <chrono>
#include "httplib.h"
#include <stdexcept>
#include <thread>
#ifdef STSP_LINUX_VER
    #pragma comment(lib, "libssl.so")
    #pragma comment(lib, "libcrypto.so")
#elif STSP_WINDOWS_VER
    #pragma comment(lib, "libssl.lib")
    #pragma comment(lib, "libcrypto.lib")
#else
    #error "No version selected for stardeos comment spammer."

namespace stardeos_nk125 {
    using namespace std;
    class spam {
    public:
        // Failed and successed requests.
        volatile unsigned long long int requests = 0, failed = 0;
        int latest_response_code;
        string latest_response_body;
        // Ratio of success.
        float ratio;
        // Function to init spam.
        void comments(string body, string id, unsigned loops, int stardusts, string uag = "Mozilla/5.0 (Macintosh; U; PPC Mac OS X Mach-O; en-US; rv:1.0.1) Gecko/20021216 Chimera/0.6") {
            if (body.size() >= limit) {
                throw invalid_argument("Server Error: Too large body comment.");
            }
            else if (loops <= 0) {
                throw invalid_argument("Param Error: Too low comment number.");
            }
            using namespace chrono_literals;
            for (unsigned i = 0; i < loops; i++) {
                try {
                    thread t(masscomment, body, id, stardusts, uag);
                    t.detach();
                }
                catch (...) {
                    this_thread::sleep_for(1s);
                    // DON'T DELETE THIS, IF YOU WANT TO HANDLE YOURSELF THE EXCEPTION RETHROW IT:
                    // throw runtime_error("Your description in .what()");
                    // Optionally add std:: behind the runtime_error function.
                }
            }
            this_thread::sleep_for(200ms);
            // Your CPU will be burned if you delete this timeout.
            return;
        }

    private:
        string token;
        short limit = 255;
        // Internal function to handle and send requests.
        void masscomment(string body_comment, string video_id, int stardusts, string user_agent) {
            using namespace httplib;
            string body = "{\"content\":\"" + body_comment + "\",\"stardusts\":" + to_string(stardusts) + ",\"type\":1,\"parent\":\"" + video_id + "\"}";
            Headers hdr = {
                {"User-Agent", user_agent.c_str()},
                {"Referer", "https://stardeos.com/api/v2/comments"},
                {"Authorization", token.c_str()}
            };
            Client request("https://stardeos.com");
            auto res = request.Post("/api/v2/comments", hdr, body.c_str(), body.size(), "application/json");
            if (res && to_string(res->status).substr(0, 1) == "2") {
                ratio = float(float(100 * requests) / failed);
                if (int(ratio) > 100) { ratio = 100; }
                // Checks for 100%+ ratio successes, it's super weird to see 200% of successed requests xD.
                requests++;
            }
            else {
                failed++;
            }
            latest_response_code = res->status;
            lates_response_body = res->body;
            return;
        }
    // Constructor to add token, please include the Bearer specifier.
    spam(string ptoken) {
        token = ptoken;
    }
    };
}
