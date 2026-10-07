#ifndef CONFIG_H
#define CONFIG_H

#include <string>

struct BuildGuardConfig {

    std::string projectName = "BuildGuard";

    std::string buildSystem = "cmake";

    std::string generator = "ninja";

    std::string buildType = "Release";

    bool testsEnabled = true;

    std::string reportFormat = "json";

    std::string reportOutput =
        "reports/buildguard_report.json";
};

bool loadConfig(
    const std::string& projectPath,
    BuildGuardConfig& config
);

#endif
