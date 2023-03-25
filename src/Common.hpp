#pragma once

#define NOMINMAX

// strings

#include <iostream>
#include <string>
#include <sstream>

typedef std::string String;
typedef std::stringstream StringStream;

#define toString(x) \
    std::to_string(x)

// objects

#include <any>

typedef std::any Object;
#define object_cast std::any_cast

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

// number conversion 

#define stringToInt(x) \
    std::stoi(x)
#define stringToLong(x) \
    std::stoll(x)
#define stringToFloat(x) \
    std::stof(x)
#define stringToDouble(x) \
    std::stod(x)

// functions

#include <functional>

template <typename T>
using Function = std::function<T>;

// files

#include <filesystem>

#define FS std::filesystem

#define fileIsDirectory FS::is_directory
#define fileExists FS::exists

typedef FS::path Path;

#include <fstream>

typedef std::ifstream FileReader;
typedef std::ofstream FileWriter;

typedef FS::directory_iterator DirIterator;
typedef FS::directory_entry DirEntiry;

#define readNextLine std::getline

// numbers

typedef unsigned int uint;
typedef size_t ulong;
typedef unsigned char byte;
typedef __int64 lint;
typedef wchar_t cint;

// windows exceptions

#include <windows.h>
#include <excpt.h>

#define ExceptionInfo _EXCEPTION_POINTERS

// misc

#define setConsoleSync(x) \
    std::ios::sync_with_stdio(x)

#define UnderlyingType std::underlying_type

#define instanceof(obj, T) \
    ((bool) (dynamic_cast<T*>(obj) != nullptr))

// time

#include <ctime>
#include <cstdlib>

#define MILLISECONDS std::chrono::milliseconds
#define NANOSECONDS std::chrono::nanoseconds
#define DURATION_CAST std::chrono::duration_cast
#define SYSTEM_CLOCK std::chrono::system_clock

#define currentTimeMillis() \
    (DURATION_CAST<MILLISECONDS>(SYSTEM_CLOCK::now().time_since_epoch()).count())

#define nanoTime() \
    (DURATION_CAST<NANOSECONDS>(SYSTEM_CLOCK::now().time_since_epoch()).count())