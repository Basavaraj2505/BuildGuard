cmake_minimum_required(VERSION 3.20)

project(BuildGuard
    VERSION 0.1.0
    DESCRIPTION "C++ Build and CI Health Analyzer"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(buildguard
    src/main.cpp
    src/scanner.cpp
    src/build_manager.cpp
    src/test_manager.cpp
    src/analyzer.cpp
src/reporter.cpp

)
enable_testing()

add_test(
    NAME BuildGuardScanTest
    COMMAND buildguard scan ${CMAKE_SOURCE_DIR}
)
