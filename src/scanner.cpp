#include "scanner.h"

#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;

void scanProject(const std::string& projectPath) {

    fs::path project(projectPath);

    std::cout << "\n=================================\n";
    std::cout << "       BuildGuard Scan\n";
    std::cout << "=================================\n";

    // Check whether the project path exists
    if (!fs::exists(project)) {
        std::cout << "\n[ERROR] Project path does not exist.\n";
        return;
    }

    std::cout << "\nProject: " << fs::absolute(project) << "\n\n";

    // Check important project components
    bool hasCMake = fs::exists(project / "CMakeLists.txt");
    bool hasSrc = fs::is_directory(project / "src");
    bool hasTests = fs::is_directory(project / "tests");
    bool hasGit = fs::is_directory(project / ".git");
    bool hasGithub = fs::is_directory(project / ".github");

    std::cout << (hasCMake ? "[OK]   " : "[MISS] ")
              << "CMakeLists.txt\n";

    std::cout << (hasSrc ? "[OK]   " : "[MISS] ")
              << "src/ directory\n";

    std::cout << (hasTests ? "[OK]   " : "[MISS] ")
              << "tests/ directory\n";

    std::cout << (hasGit ? "[OK]   " : "[MISS] ")
              << ".git/ directory\n";

    std::cout << (hasGithub ? "[OK]   " : "[MISS] ")
              << ".github/ directory\n";

    // Count C++ source files
    int cppFiles = 0;

    for (const auto& entry :
         fs::recursive_directory_iterator(project)) {

        // Only process regular files
        if (!entry.is_regular_file()) {
            continue;
        }

        // Ignore generated build files
        if (entry.path().string().find("/build/") != std::string::npos) {
            continue;
        }

        // Count C++ source files
        if (entry.path().extension() == ".cpp" ||
            entry.path().extension() == ".cc" ||
            entry.path().extension() == ".cxx") {

            cppFiles++;
        }
    }

    std::cout << "\nC++ source files: " << cppFiles << "\n";

    // Determine project status
    if (hasCMake && hasSrc && hasGit) {
        std::cout << "\nStatus: READY\n";
    } else {
        std::cout << "\nStatus: NEEDS ATTENTION\n";
    }
}
