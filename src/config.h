#pragma once

#include <iostream>

#ifdef _DEBUG
#define LOG(x) std::cout << x << std::endl
#elif defined(_DEBUG)
#define LOG(x)
#endif

#define ASSERT(x) if(!(x)) __debugbreak();

#define c_Display_X 80
#define c_Display_Y 80