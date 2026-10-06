#include "test_manager.h"

#include <cstdlib>
#include <iostream>

bool runTests(const std::string& projectPath) {

    std::cout << "\n=================================\n";
    std::cout << "       BuildGuard Tests\n";
    std::cout << "=================================\n";

    std::cout << "\nProject: " << projectPath << "\n";

    std::cout << "\n[TEST] Running CTest...\n\n";

    std::string testCommand =
        "ctest --test-dir \"" + projectPath + "/build\" --output-on-failure";

    int result = std::system(testCommand.c_str());

    if (result != 0) {

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
