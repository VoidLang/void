#pragma once

// string manipulation

#include <iostream>
#include <string>

typedef std::string String;

// maps

#include <unordered_map>

template <typename K, typename V>
using Map = std::unordered_map<K, V>;

// lists

template <typename T>
using List = std::vector<T>;

#define contains(list, element) \
    std::find(list.begin(), list.end(), element) != list.end()

// debugging

#define println(x) \
    std::cout << x << '\n'

#define print(x) \
    std::cout << x

#define error(x) \
    { std::cout << x << '\n'; exit(-1); }

#define warn(x) \
    std::cout << "[Warning] " << x << '\n'

// windows exceptions

#include <windows.h>
#include <excpt.h>

#define ExceptionInfo _EXCEPTION_POINTERS

// misc

#define setConsoleSync(x) \
    std::ios::sync_with_stdio(x)
