#pragma once

#ifndef __STRING__
#include <string>
#endif

#ifndef __FILESYSTEM__
#include <filesystem>
#endif


#ifndef KMP
#define KMP 0
#endif

#ifndef STRSTR
#define STRSTR 1
#endif

#include <queue>

#ifdef _WIN32
    #ifdef FE_EXPORTS
        #define FE_API __declspec(dllexport)
    #else
        #define FE_API __declspec(dllimport)
    #endif
#else
    #define FE_API
#endif

namespace search_engine{

    using namespace std;
    namespace fs = filesystem;
    using namespace fs;

    class SearchAPI {

        public:
            int key;
            string pattern;

            SearchAPI();
            ~SearchAPI();

            int strstr(char text[], char pattern[]);
            bool kmp(char text[], char pattern[]);

            //string type 오버로딩
            int strstr(string text, string pattern);
            bool kmp(string text, string pattern);

            // 하위 폴더 전체 검색
            void dfs(const path& p, const string& target, int method);
            void bfs(const path& p, const string& target, int method);

        private:
            queue<path> que;// 큐는 항상 유지
            
            void drecursive_k(const path& p, const string& target);
            void drecursive_s(const path& p, const string& target);

    };
}


