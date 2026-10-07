cmake_minimum_required(VERSION 3.20)

project(BuildGuard
    VERSION 0.1.0
    DESCRIPTION "C++ Build and CI Health Analyzer"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(yaml-cpp REQUIRED)

# =================================
# Main BuildGuard executable
# =================================

add_executable(buildguard
    src/main.cpp
    src/scanner.cpp
    src/build_manager.cpp
    src/test_manager.cpp
    src/analyzer.cpp
    src/reporter.cpp
    src/config.cpp
)

target_include_directories(buildguard
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(buildguard
    PRIVATE
    yaml-cpp::yaml-cpp
)

# =================================
# CTest
# =================================

enable_testing()

# Integration test
add_test(
    NAME BuildGuardScanTest
    COMMAND buildguard scan ${CMAKE_SOURCE_DIR}
)

# =================================
# Unit test executable
# =================================

add_executable(buildguard_tests
    tests/test_buildguard.cpp
    src/analyzer.cpp
    src/config.cpp
)

target_include_directories(buildguard_tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(buildguard_tests
    PRIVATE
    yaml-cpp::yaml-cpp
)

# Unit tests
add_test(
    NAME BuildGuardUnitTests
    COMMAND buildguard_tests ${CMAKE_SOURCE_DIR}
)
