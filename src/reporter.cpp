#include "reporter.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

void generateReport(
    const std::string& projectPath,
    const BuildError& buildError,
    const BuildGuardConfig& config
) {
    std::cout << "\n=================================\n";
    std::cout << "       BuildGuard Report\n";
    std::cout << "=================================\n";

    fs::path project(projectPath);

    if (!fs::exists(project)) {
        std::cout << "\n[ERROR] Project path does not exist.\n";
        return;
    }

    // Create the reports directory if it does not exist.
    fs::path reportDirectory = project / "reports";

    if (!fs::exists(reportDirectory)) {
        fs::create_directories(reportDirectory);
    }

    // Use the output path from buildguard.yml.
    fs::path reportFile = project / config.reportOutput;

    // Create parent directories if needed.
    if (reportFile.has_parent_path()) {
        fs::create_directories(reportFile.parent_path());
    }

    std::ofstream file(reportFile);

    if (!file.is_open()) {
        std::cout << "\n[ERROR] Could not create report file.\n";
        return;
    }

    bool hasCMake = fs::exists(project / "CMakeLists.txt");
    bool hasSrc = fs::is_directory(project / "src");
    bool hasTests = fs::is_directory(project / "tests");
    bool hasGit = fs::is_directory(project / ".git");
    bool hasGithub = fs::is_directory(project / ".github");

    bool buildSuccess = buildError.type == ErrorType::NONE;

    int healthScore = buildSuccess ? 100 : 0;

    file << "{\n";

    file << "  \"project\": \"" << config.projectName << "\",\n";

    file << "  \"build_status\": \""
         << (buildSuccess ? "SUCCESS" : "FAILED")
         << "\",\n";

    file << "  \"error_type\": \""
         << errorTypeToString(buildError.type)
         << "\",\n";

    file << "  \"error_message\": \""
         << buildError.message
         << "\",\n";

    file << "  \"build_system\": \""
         << config.buildSystem
         << "\",\n";

    file << "  \"generator\": \""
         << config.generator
         << "\",\n";

    file << "  \"build_type\": \""
         << config.buildType
         << "\",\n";

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

    file << "  \"health_score\": "
         << healthScore
         << "\n";

    file << "}\n";

    file.close();

    std::cout << "\n[REPORT] JSON report generated.\n";
    std::cout << "Location: " << reportFile << "\n";
}
