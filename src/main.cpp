#include <iostream>
#include <string>

#include "scanner.h"
#include "build_manager.h"
#include "test_manager.h"
#include "analyzer.h"
#include "reporter.h"

int main(int argc, char* argv[]) {

    std::cout << "=================================\n";
    std::cout << "        BuildGuard v0.1\n";
    std::cout << "   C++ Build & CI Health Tool\n";
    std::cout << "=================================\n";

    if (argc < 2) {

        std::cout << "\nUsage: buildguard <command> [project-path]\n";

        std::cout << "\nCommands:\n";
        std::cout << "  scan       Scan project structure\n";
        std::cout << "  build      Build the project\n";
        std::cout << "  test       Run tests\n";
        std::cout << "  analyze    Analyze build errors\n";
        std::cout << "  report     Generate JSON report\n";

        return 1;
    }

    std::string command = argv[1];

    std::string projectPath = ".";

    if (argc >= 3) {
        projectPath = argv[2];
    }


    // =========================
    // SCAN
    // =========================

    if (command == "scan") {

        scanProject(projectPath);
    }


    // =========================
    // BUILD
    // =========================

    else if (command == "build") {

        buildProject(projectPath);
    }


    // =========================
    // TEST
    // =========================

    else if (command == "test") {

        runTests(projectPath);
    }


    // =========================
    // ANALYZE
    // =========================

    else if (command == "analyze") {

        analyzeBuild(projectPath);
    }


    // =========================
    // REPORT
    // =========================

else if (command == "report") {

    generateReport(projectPath);

    }


    // =========================
    // UNKNOWN COMMAND
    // =========================

    else {

        std::cout << "\nUnknown command: "
                  << command
                  << "\n";

        return 1;
    }

    return 0;
}
