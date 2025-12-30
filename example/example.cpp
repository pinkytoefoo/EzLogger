#include <memory>
#include <string>
#include <chrono>
#include <thread>

#include "ezlog/ezlog.hpp"

int main()
{
    ezlog::logger log{ezlog::level::info};
    using namespace ezlog;
    log.log(color::cyan, "this is cyan regular");
    log.log(color::cyan, "this is cyan intense");

    // using namespace std;
    // auto start = chrono::steady_clock::now();
    // for (int i = 0; i < 1'000'000; ++i)
    //     log.log(ezlog::color::bright_blue, "hello {}", i);
    // auto end = chrono::steady_clock::now();

    // chrono::duration<double> duration = end - start;

    // log.info(std::format("Execution duration: {} seconds", duration.count()));

    return 0;
}
