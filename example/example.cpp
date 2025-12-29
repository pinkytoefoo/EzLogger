#include <memory>
#include <string>
#include <iostream>

#include "EzLogger/EzLogger.h"

#ifdef __unix__
int main()
{
    ezlog::info("yay");

    return 0;
}
#endif

#ifdef _WIN32
int main()
{
    std::shared_ptr<EzLogger::EzLogger> Logger = std::make_shared<EzLogger::EzLogger>(EzLogger::EZ_TRACE, "EXAMPLE");

    Logger->SetPattern("%t: ");
    Logger->Info("This is an info test %s", Logger->GetType().c_str());
    // std::cout << "seeing";
}
#endif
