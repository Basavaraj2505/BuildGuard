#ifndef BUILDGUARD_BUILD_MANAGER_H
#define BUILDGUARD_BUILD_MANAGER_H

#include <string>
#include "config.h"

bool buildProject(
    const std::string& projectPath,
    const BuildGuardConfig& config
);

#endif
