# DataStructure-FileExplorer
## Description
2023 summer data-structure team project
FileExplorer Team6

## How to build
### Linux
mkdir build && cd build  
cmake ..  
make

### Window
mkdir build && cd build  
cmake -G "Unix Makefiles" ..    
make

## How to use
Usage: FileExplorer [--help] [--version] [-dir] [-mkdir VAR] [-rm VAR] [-touch VAR] [-cp VAR...] [-mv VAR...] [-sort VAR...] [-ss VAR...] [-path VAR]

Optional arguments:
  -h, --help   	shows help message and exits  
  -v, --version	prints version information and exits  
  -dir         	print current location  
  -mkdir       	USAGE : -mkdir [FOLDERNAME to create]  
  -rm          	USAGE : -rm [WHAT to remove]  
  -touch       	USAGE : -touch [FILENAME to create]  
  -cp          	USAGE : -cp [WHAT to copy] [WHERE to copy] [nargs: 2]  
  -mv          	USAGE : -mv [WHAT to move] [WHERE to move] [nargs: 2]  
  -sort        	USAGE : -sort [q for quick, m for merge, h for heap] [n for name, s for size, t for time] [nargs: 2]  
  -ss          	USAGE : -ss [dfs or bfs] [kmp or strstr] [what to search] [nargs: 3]  
  -path        	where to search (only for '-ss')  
