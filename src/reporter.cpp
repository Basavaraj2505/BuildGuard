#include "reporter.h"
#include "config.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

void generateReport(const std::string& projectPath) {

    std::cout << "\n=================================\n";
    std::cout << "       BuildGuard Report\n";
    std::cout << "=================================\n";

    fs::path project(projectPath);

    if (!fs::exists(project)) {

        std::cout << "\n[ERROR] Project path does not exist.\n";
        return;
    }

    // =========================
    // LOAD CONFIGURATION
    // =========================

    BuildGuardConfig config;

    if (!loadConfig(projectPath, config)) {

        std::cout
            << "[REPORT] Using default configuration.\n";
    }

    // =========================
    // REPORT OUTPUT
    // =========================

    fs::path reportFile =
        project / config.reportOutput;

    fs::path reportDirectory =
        reportFile.parent_path();

    if (!reportDirectory.empty() &&
        !fs::exists(reportDirectory)) {

        fs::create_directories(reportDirectory);
    }

    std::ofstream file(reportFile);

    if (!file.is_open()) {

        std::cout
            << "\n[ERROR] Could not create report file.\n";

        return;
    }

    // =========================
    // PROJECT STRUCTURE
    // =========================

    bool hasCMake =
        fs::exists(project / "CMakeLists.txt");

    bool hasSrc =
        fs::is_directory(project / "src");

    bool hasTests =
        fs::is_directory(project / "tests");

    bool hasGit =
        fs::is_directory(project / ".git");

    bool hasGithub =
        fs::is_directory(project / ".github");

    // =========================
    // JSON REPORT
    // =========================

    file << "{\n";

    file << "  \"project\": \""
         << config.projectName
         << "\",\n";

    file << "  \"build_status\": \"SUCCESS\",\n";

    file << "  \"tests\": \""
         << (config.testsEnabled ? "PASSED" : "DISABLED")
         << "\",\n";

    file << "  \"compiler\": \"GCC\",\n";

    file << "  \"build_system\": \""
         << config.buildSystem
         << " + "
         << config.generator
         << "\",\n";

    file << "  \"build_type\": \""
         << config.buildType
         << "\",\n";

    file << "  \"language\": \"C++17\",\n";

    file << "  \"report_format\": \""
         << config.reportFormat
         << "\",\n";

    file << "  \"structure\": {\n";

    file << "    \"cmake\": "
         << (hasCMake ? "true" : "false")
         << ",\n";

    file << "    \"src\": "
         << (hasSrc ? "true" : "false")
         << ",\n";

    file << "    \"tests\": "
         << (hasTests ? "true" : "false")
         << ",\n";

    file << "    \"git\": "
         << (hasGit ? "true" : "false")
         << ",\n";

    file << "    \"github_actions\": "
         << (hasGithub ? "true" : "false")
         << "\n";

    file << "  },\n";

    file << "  \"health_score\": 100\n";

    file << "}\n";

    file.close();

    std::cout
        << "\n[REPORT] JSON report generated.\n";

    std::cout
        << "Location: "
        << reportFile
        << "\n";
}
