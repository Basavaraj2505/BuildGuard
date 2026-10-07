#ifndef BUILDGUARD_TEST_MANAGER_H
#define BUILDGUARD_TEST_MANAGER_H

#include <string>

#include "config.h"

bool runTests(
    const std::string& projectPath,
    const BuildGuardConfig& config
);

#endif
