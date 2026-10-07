#include <cassert>
#include <iostream>
#include <string>

#include "analyzer.h"
#include "config.h"

void testIncludeError() {
    BuildError result =
        classifyError("fatal error: scanner_missing.h: No such file or directory");

    assert(result.type == ErrorType::INCLUDE_ERROR);

    std::cout << "[PASS] Include error classification\n";
}

void testLinkerError() {
    BuildError result =
        classifyError("undefined reference to `main'");

    assert(result.type == ErrorType::LINKER_ERROR);

    std::cout << "[PASS] Linker error classification\n";
}

void testSymbolError() {
    BuildError result =
        classifyError("error: variable was not declared in this scope");

    assert(result.type == ErrorType::SYMBOL_ERROR);

    std::cout << "[PASS] Symbol error classification\n";
}

void testSyntaxError() {
    BuildError result =
        classifyError("error: expected ';' before '}' token");

    assert(result.type == ErrorType::SYNTAX_ERROR);

    std::cout << "[PASS] Syntax error classification\n";
}

void testNoError() {
    BuildError result =
        classifyError("Build completed successfully.");

    assert(result.type == ErrorType::NONE);

    std::cout << "[PASS] Normal build output classification\n";
}

void testYamlConfiguration(const std::string& projectPath) {
    BuildGuardConfig config;

    bool loaded =
        loadConfig(projectPath, config);

    assert(loaded);
    assert(config.projectName == "BuildGuard");
    assert(config.buildSystem == "cmake");
    assert(config.generator == "Ninja");
    assert(config.buildType == "Release");
    assert(config.testsEnabled == true);
    assert(config.reportFormat == "json");
    assert(config.reportOutput == "reports/buildguard_report.json");

    std::cout << "[PASS] YAML configuration loading\n";
}

int main(int argc, char* argv[]) {
    std::cout << "\n=================================\n";
    std::cout << "    BuildGuard Unit Tests\n";
    std::cout << "=================================\n\n";

    if (argc < 2) {
        std::cerr << "[ERROR] Project path argument is required.\n";
        return 1;
    }

    std::string projectPath = argv[1];

    testIncludeError();
    testLinkerError();
    testSymbolError();
    testSyntaxError();
    testNoError();
    testYamlConfiguration(projectPath);

    std::cout << "\n=================================\n";
    std::cout << "    ALL UNIT TESTS PASSED\n";
    std::cout << "=================================\n";

    return 0;
}
