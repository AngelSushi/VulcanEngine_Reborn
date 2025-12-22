#pragma once
#include <CoreAPI/Types.h>

template<typename T>
struct TIsIntegral {
    enum { Value = false };
};

// All types that can be write with an int

template<> struct TIsIntegral<bool> { enum { Value = true }; };
template<> struct TIsIntegral<char> { enum { Value = true }; };
template<> struct TIsIntegral<signed char> { enum { Value = true }; };
template<> struct TIsIntegral<unsigned char> {  enum { Value = true }; };
template<> struct TIsIntegral<char16> { enum { Value = true }; };
template<> struct TIsIntegral<char32> { enum { Value = true }; };
template<> struct TIsIntegral<wchar> { enum { Value = true }; };
template<> struct TIsIntegral<short> { enum { Value = true }; };
template<> struct TIsIntegral<unsigned short> { enum { Value = true }; };
template<> struct TIsIntegral<int> { enum { Value = true }; };
template<> struct TIsIntegral<unsigned int> { enum { Value = true }; };
template<> struct TIsIntegral<long> { enum { Value = true }; };
template<> struct TIsIntegral<unsigned long> { enum { Value = true }; };
template<> struct TIsIntegral<long long> { enum { Value = true }; };
template<> struct TIsIntegral<unsigned long long> { enum { Value = true }; };