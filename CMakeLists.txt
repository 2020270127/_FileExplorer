cmake_minimum_required(VERSION 3.0.0)
project(fe VERSION 1.0.0)

include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "")

if(MINGW OR WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static -static-libgcc -static-libstdc++ -static-libgfortran")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,--allow-multiple-definition")
endif()

add_library(
    fe_library SHARED
    Algorithm/fileinfo.cpp
    Algorithm/search.cpp
)

if(WIN32)
    target_compile_definitions(fe_library PRIVATE FE_EXPORTS)
endif()

add_executable(
    fe fe.cpp
)
target_link_libraries(fe fe_library)

add_executable(
    fe_test test.cpp
)
target_link_libraries(fe_test fe_library)

add_compile_options(-Wall)

add_custom_target(clean-all
    COMMAND ${CMAKE_COMMAND} -E rm -rf CMakeFiles CMakeCache.txt *.cmake fe fe_test fe_library
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning all generated files"
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
