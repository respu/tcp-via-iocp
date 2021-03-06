#pragma once

#if defined(_DEBUG)

#include <iostream>

#define LOG_DEBUG(message) std::cout << "Debug: " << message << std::endl
#define LOG_ERROR(message) std::cout << "Error: " << message << std::endl

#else

#define LOG_DEBUG(message)
#define LOG_ERROR(message)

#endif