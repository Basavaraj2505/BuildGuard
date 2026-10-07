#include "analyzer.h"

#include <cstdio>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

BuildError classifyError(const std::string& line) {

    // Missing header / include file
    if (line.find("No such file or directory") != std::string::npos) {
        return {
            ErrorType::INCLUDE_ERROR,
            line
        };
    }

    // Linker errors
    if (line.find("undefined reference") != std::string::npos) {
        return {
            ErrorType::LINKER_ERROR,
            line
        };
    }

    // Symbol errors
    if (line.find("was not declared") != std::string::npos ||
        line.find("undeclared") != std::string::npos) {
        return {
            ErrorType::SYMBOL_ERROR,
            line
        };
    }

    // Syntax errors
    if (line.find("expected") != std::string::npos ||
        line.find("syntax error") != std::string::npos) {
        return {
            ErrorType::SYNTAX_ERROR,
            line
        };
    }

    // Generic compiler error
    if (line.find("error:") != std::string::npos ||
        line.find("fatal error:") != std::string::npos) {
        return {
            ErrorType::UNKNOWN_ERROR,
            line
        };
    }

    return {
        ErrorType::NONE,
        ""
    };
}


std::string errorTypeToString(ErrorType type) {

    switch (type) {

        case ErrorType::NONE:
            return "NONE";

        case ErrorType::SYMBOL_ERROR:
            return "SYMBOL_ERROR";

        case ErrorType::INCLUDE_ERROR:
            return "INCLUDE_ERROR";

        case ErrorType::LINKER_ERROR:
            return "LINKER_ERROR";

        case ErrorType::SYNTAX_ERROR:
            return "SYNTAX_ERROR";

        case ErrorType::UNKNOWN_ERROR:
            return "UNKNOWN_ERROR";
    }

    return "UNKNOWN_ERROR";
}


BuildError analyzeBuild(const std::string& projectPath) {

    std::cout << "\n=================================\n";
    std::cout << "       BuildGuard Analysis\n";
    std::cout << "=================================\n";

    std::cout << "\nProject: " << projectPath << "\n";

    fs::path buildDirectory =
        fs::path(projectPath) / "build";

    if (!fs::exists(buildDirectory)) {

        std::cout << "\n[ERROR] Build directory does not exist.\n";
        std::cout << "Run CMake configuration first.\n";

        return {
            ErrorType::UNKNOWN_ERROR,
            "Build directory does not exist."
        };
    }

    std::cout << "\n[ANALYZE] Running CMake build...\n\n";

    std::string command =
        "cmake --build \"" +
        buildDirectory.string() +
        "\" 2>&1";

    FILE* pipe = popen(command.c_str(), "r");

    if (!pipe) {

        std::cout << "\n[ERROR] Could not start build process.\n";

        return {
            ErrorType::UNKNOWN_ERROR,
            "Could not start build process."
        };
    }

    char buffer[512];

    bool buildFailed = false;

    BuildError detectedError{
        ErrorType::NONE,
        ""
    };

    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {

        std::string line(buffer);

        std::cout << line;

        BuildError currentError =
            classifyError(line);

        if (currentError.type != ErrorType::NONE) {

            buildFailed = true;

            if (detectedError.type == ErrorType::NONE) {
                detectedError = currentError;
            }
        }
    }

    int result = pclose(pipe);

    std::cout << "\n=================================\n";

    if (result == 0 && !buildFailed) {

        std::cout << "          BUILD SUCCESS\n";
        std::cout << "=================================\n";

        std::cout << "\nNo build errors detected.\n";

        return {
            ErrorType::NONE,
            ""
        };
    }

    std::cout << "          BUILD FAILED\n";
    std::cout << "=================================\n";

    if (detectedError.type != ErrorType::NONE) {

        std::cout << "\n[ERROR CLASSIFICATION]\n";

        std::cout << "Type: "
                  << errorTypeToString(detectedError.type)
                  << "\n";

        std::cout << "Message: "
                  << detectedError.message;

        return detectedError;
    }

    std::cout << "\n[ERROR CLASSIFICATION]\n";
    std::cout << "Type: UNKNOWN_ERROR\n";
    std::cout << "Could not classify the build error.\n";

    return {
        ErrorType::UNKNOWN_ERROR,
        "Could not classify the build error."
    };
}
