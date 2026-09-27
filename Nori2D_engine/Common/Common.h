#pragma once
#include <math.h>

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(_ptr) { if(_ptr){_ptr->Release();} _ptr = nullptr; }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(_ptr) { if(_ptr){ delete (_ptr);} _ptr = nullptr; }
#endif

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(_ptr) { if(_ptr){ delete [] (_ptr);} _ptr = nullptr; }
#endif

// new callbacks based on C++11
#define AX_CALLBACK_0(__selector__, __target__, ...) std::bind(&__selector__, __target__, ##__VA_ARGS__)
#define AX_CALLBACK_1(__selector__, __target__, ...) \
    std::bind(&__selector__, __target__, std::placeholders::_1, ##__VA_ARGS__)
#define AX_CALLBACK_2(__selector__, __target__, ...) \
    std::bind(&__selector__, __target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define AX_CALLBACK_3(__selector__, __target__, ...)                                                          \
    std::bind(&__selector__, __target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, \
              ##__VA_ARGS__)
#define AX_CALLBACK_4(__selector__, __target__, ...)                                                          \
    std::bind(&__selector__, __target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, \
              std::placeholders::_4, ##__VA_ARGS__)

inline 
int LengthSqr(const POINT& a, const POINT& b)
{
	return ((a.x-b.x)*(a.x-b.x)) + ((a.y-b.y)*(a.y-b.y));
}

void OutputDebugString2(const char* format, ...);


#include "Common/DebugString.h"

#include "XFloat2.h"
#include "XMatrix2D.h"
#include "Bit64x64.h"

#include "Collision2D.h"
#include "JsonFile2.h"
#include "Regulator.h"

#include "Scriptor.h"


