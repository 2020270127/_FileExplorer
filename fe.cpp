#include "include/argparse.hpp"
#include "Algorithm/fileinfo.hpp"
#include "Algorithm/search.hpp"

#ifndef __STDLIB_H__
#include <stdlib.h>
#endif

#ifndef __FSTREAM__
#include <fstream>
#endif

#ifndef __FILESYSTEM__
#include <filesystem>
#endif

namespace fs = std::filesystem;

using namespace search_engine;
using namespace file_engine;
using namespace std;
using namespace fs;


int main(int argc, char *argv[]) {
    argparse::ArgumentParser parser("FileExplorer");
    
    search_engine::SearchAPI SearchAPIInstance;
    file_engine::FileAPI FileAPIInstance;

    // Args list
    parser.add_argument("-dir").default_value("./").help("print current location").nargs(0);
    parser.add_argument("-mkdir").help("USAGE : -mkdir [FOLDERNAME to create]"); //폴더 생성
    parser.add_argument("-rm").help("USAGE : -rm [WHAT to remove]"); //파일 혹은 폴더 삭제 
    parser.add_argument("-touch").help("USAGE : -touch [FILENAME to create]"); //파일 생성
    parser.add_argument("-cp").help("USAGE : -cp [WHAT to copy] [WHERE to copy]").nargs(2); //파일 혹은 폴더 복사
    parser.add_argument("-mv").help("USAGE : -mv [WHAT to move] [WHERE to move]").nargs(2); //이동
    parser.add_argument("-sort").help("USAGE : -sort [q for quick, m for merge, h for heap] [n for name, s for size, t for time]").nargs(2); //정렬
    parser.add_argument("-ss").help("USAGE : -ss [dfs or bfs] [kmp or strstr] [what to search]").nargs(3);
    parser.add_argument("-path").help("where to search (only for '-ss')").nargs(1); //검색

    if (argc == 1) {
        cout << parser;
        exit(0);
    }
    try {
        parser.parse_args(argc, argv);
    } catch (const runtime_error &err) {
        cerr << err.what() << endl;
        cerr << parser;
    }
    
    if (parser.is_used("-dir")) { //현재 경로 출력
        cout << current_path() << endl;
    }

    else if (parser.is_used("-rm")) {  //파일 삭제기능, 강제 삭제 디폴트
    string path_to_remove = parser.get<string>("-rm");
        
    try {
        if (exists(path_to_remove)) {
            remove_all(path_to_remove);
        } else {
            cerr << "Path not found: " << path_to_remove << endl;
        }
    } catch (const exception& ex) {
        cerr << "Error removing path: " << path_to_remove << ", error: " << ex.what() << endl;
    }
}
    
    else if (parser.is_used("-mkdir")) { // 폴더 생성
    string path_to_create = parser.get<string>("-mkdir");
    try {
        if (create_directory(path_to_create)) {
            cout << "Directory created: " << path_to_create << endl;
        } else {
            cerr << "Directory already exists: " << path_to_create << endl;
        }
    } catch (const exception& ex) {
        cerr << "Error creating directory: " << path_to_create << ", error: " << ex.what() << endl;
      }

    }
    else if (parser.is_used("-touch")) { //파일 생성
    string file_path = parser.get<string>("-touch");
    try {
        ofstream file(file_path);
        if (file.is_open()) {
            file.close();
            cout << "File created: " << file_path << endl;
        } else {
            cerr << "Error creating file: " << file_path << endl;
        }
    } catch (const exception& ex) {
        cerr << "Error creating file: " << file_path << ", error: " << ex.what() << endl;
        }
    }

    else if (parser.is_used("-cp")) {   



    string file_name = parser.get<vector<string>>("-cp")[0];
    
    string destination_path = parser.get<vector<string>>("-cp")[1];

    path source = current_path();
    path destination(destination_path);

    if (!exists(source / file_name)) // 소스 경로에 파일이나 폴더가 존재하지 않는 경우
    {
        cout << "Cannot copy file or folder: " << source / file_name << " (not found)" << endl;
        return 1;
    }

    try
    {
        if (is_directory(source / file_name)) // 폴더를 복사하는 경우
        {
            create_directories(destination / file_name);
            for (const auto& file : recursive_directory_iterator(source / file_name))
            {
                path current(file.path());
                path target(destination / file_name / current.lexically_relative(source / file_name));
                if (is_directory(current)) // 하위 폴더를 만들어줌
                {
                    create_directory(target);
                }
                else // 파일을 복사함
                {
                    copy_file(current, target, copy_options::overwrite_existing);
                }
            }
        }
        else // 파일을 복사하는 경우
        {
            copy_file(source / file_name, destination / file_name, copy_options::overwrite_existing);
        }

        cout << "File or folder copied successfully" << endl;
        return 0;
    }
    catch (const exception& ex)
    {
        cerr << "Error: " << ex.what() << endl;
        return 1;
    }
}

    else if (parser.is_used("-mv")) {


    string file_name = parser.get<vector<string>>("-mv")[0];
    string destination_path = parser.get<vector<string>>("-mv")[1];

    path current_path = fs::current_path();
    path source_file = current_path / file_name;
    path destination_file = current_path / destination_path / file_name;

    try {
        rename(source_file, destination_file);
        cout << "File moved successfully!" << endl;
    }
    catch (const filesystem_error& e) {
        cerr << e.what() << endl;
    }
}   

    else if (parser.is_used("-sort")) {
        auto sortArgs = parser.get<vector<string>>("-sort");
        char method = sortArgs[0][0]; // q(qucick), m(merge), h(heap)
        char algorithm = sortArgs[1][0]; //n(name), s(size), t(modified_time)
      
        if((method != 'q' && method != 'm' && method != 'h') || (algorithm != 'n'&& algorithm != 's'&& algorithm != 't'))
            cout<<"wrong argument"<<endl;
        else if(FileAPIInstance.printSortedArr(method,algorithm) == -1){
            cout<<"wrong argument"<<endl;
        }
        //sort
    }
    
    else if (parser.is_used("-ss")) {
        auto sortArgs = parser.get<vector<string>>("-ss");
        auto Path = parser.get<vector<string>>("-path");

        int method = (sortArgs[0] == "DFS") || (sortArgs[0] == "dfs") ? 0 : (sortArgs[0] == "BFS") || (sortArgs[0] == "bfs") ? 1 : -1;
        int algorithm = (sortArgs[1] == "KMP") || (sortArgs[1] == "kmp") ? 0 : (sortArgs[1] == "STRSTR") || (sortArgs[1] == "strstr") ? 1 : -1;

        string pattern = sortArgs[2];
        string path = Path.empty() ? current_path().string() : Path[0];

        if(method != -1 && algorithm != -1) 
            FileAPIInstance.searchFile(path, pattern, method, algorithm);
        else    
            cout<<"wrong argument"<<endl;
    }

    exit(0);
}
