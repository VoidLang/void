#pragma once

#define NOMINMAX

// string manipulation

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
#define object_cast std::any_cast;

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

#define stringToInt std::stoi

// functions

#include <functional>

template <typename T>
using Function = std::function<T>;
// #define Function std::function

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

// integers

typedef unsigned int uint;
typedef size_t ulong;

// windows exceptions

#include <windows.h>
#include <excpt.h>

#define ExceptionInfo _EXCEPTION_POINTERS

// misc

#define setConsoleSync(x) \
    std::ios::sync_with_stdio(x)

#define UnderlyingType std::underlying_type