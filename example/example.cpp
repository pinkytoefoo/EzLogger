#include <memory>
#include <string>

#include "ezlog/ezlog.hpp"

int main()
{
    std::unique_ptr<ezlog::logger> logger = std::make_unique<ezlog::logger>(ezlog::level::info);
    logger->trace("logger is calling trace..."); // shouldn't get called
    logger->info("logger is calling info...");
    logger->warn("logger is calling warn...");
    logger->error("logger is calling error...");

    return 0;
}
