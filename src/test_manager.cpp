#include "test_manager.h"

#include <cstdlib>
#include <iostream>

bool runTests(
    const std::string& projectPath,
    const BuildGuardConfig& config
) {
    std::cout << "\n=================================\n";
    std::cout << "       BuildGuard Tests\n";
    std::cout << "=================================\n";

    std::cout << "\nProject: " << projectPath << "\n";

    // Check whether testing is enabled in buildguard.yml.
    if (!config.testsEnabled) {
        std::cout << "\n[TEST] Testing is disabled in buildguard.yml.\n";
        std::cout << "[TEST] Skipping test execution.\n";
        return true;
    }

    std::cout << "\n[TEST] Testing is enabled.\n";
    std::cout << "[TEST] Running CTest...\n\n";

    std::string testCommand =
        "ctest --test-dir \"" +
        projectPath +
        "/build\" --output-on-failure";

    int testResult = std::system(testCommand.c_str());

    if (testResult != 0) {
        std::cout << "\n=================================\n";
        std::cout << "        TESTS FAILED\n";
        std::cout << "=================================\n";

        return false;
    }

    std::cout << "\n=================================\n";
    std::cout << "        TESTS PASSED\n";
    std::cout << "=================================\n";

    return true;
}
