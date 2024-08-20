#pragma once

#ifndef __FILESYSTEM__
#include <filesystem>
#endif

#ifndef __IOSTREAM__
#include <iostream>
#endif

#ifndef __SYS_STAT_H__
#include <sys/stat.h>
#endif

#ifndef KMP
#define KMP 0
#endif

#ifndef STRSTR
#define STRSTR 1
#endif

#ifdef _WIN32
    #ifdef FE_EXPORTS
        #define FE_API __declspec(dllexport)
    #else
        #define FE_API __declspec(dllimport)
    #endif
#else
    #define FE_API
#endif

namespace file_engine{
    namespace fs = std::filesystem;
    using namespace fs;
    using namespace std;

    class FileAPI
    {
        public:
            struct FileInfo {
                    string name;
                    string path;
                    uintmax_t size;
                    bool is_directory;
                    time_t modified_time;
#ifdef _WIN32
                    struct _stat64i32 st;
#else
                    struct stat st;
#endif
                    };
            void printAInfo(FileInfo *info_array);
            void printInfo(FileInfo *info_array, int size);
            FileInfo *getInfo(path filepath);
            int printSortedArr(char method, char standard);
            void searchFile(const path &p, const string &target, int method, int algorithm);
            FileAPI();
            ~FileAPI();

        private:
            int getSize(path path);
            int printSearchedInDir(path const &dirpath, string pattern, int method);
            FileInfo *getInfoArray();
                 
    };
    ;

}


