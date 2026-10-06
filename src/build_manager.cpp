#include "build_manager.h"

#include <chrono>
#include <cstdlib>
#include <iostream>

bool buildProject(const std::string& projectPath) {

    std::cout << "\n=================================\n";
    std::cout << "       BuildGuard Build\n";
    std::cout << "=================================\n";

    std::cout << "\nProject: " << projectPath << "\n";

    std::cout << "\n[BUILD] Configuring project...\n";

    std::string configureCommand =
        "cmake -S \"" + projectPath +
        "\" -B \"" + projectPath + "/build\" -G Ninja";

    auto start = std::chrono::steady_clock::now();

    int configureResult = std::system(configureCommand.c_str());

    if (configureResult != 0) {
        std::cout << "\n[FAILED] CMake configuration failed.\n";
        return false;
    }

    std::cout << "\n[BUILD] Compiling project...\n";

    std::string buildCommand =
        "cmake --build \"" + projectPath + "/build\"";

    int buildResult = std::system(buildCommand.c_str());

    auto end = std::chrono::steady_clock::now();

    auto duration =
        std::chrono::duration_cast<std::chrono::milliseconds>(
            end - start
        );

    double seconds = duration.count() / 1000.0;

    if (buildResult != 0) {
        std::cout << "\n=================================\n";
        std::cout << "        BUILD FAILED\n";
        std::cout << "=================================\n";
        std::cout << "Build time: " << seconds << " seconds\n";

        return false;
    }

    std::cout << "\n=================================\n";
    std::cout << "        BUILD SUCCESS\n";
    std::cout << "=================================\n";
    std::cout << "Build time: " << seconds << " seconds\n";

    return true;
}
