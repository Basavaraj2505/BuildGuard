#include "config.h"

#include <filesystem>
#include <iostream>

#include <yaml-cpp/yaml.h>

namespace fs = std::filesystem;

bool loadConfig(
    const std::string& projectPath,
    BuildGuardConfig& config
) {

    fs::path configFile =
        fs::path(projectPath) / "buildguard.yml";

    // Configuration file is optional.
    // If it doesn't exist, use default values.
    if (!fs::exists(configFile)) {

        std::cout
            << "[CONFIG] No buildguard.yml found. "
            << "Using default configuration.\n";

        return true;
    }

    try {

        YAML::Node root =
            YAML::LoadFile(configFile.string());

        if (root["project"] &&
            root["project"]["name"]) {

            config.projectName =
                root["project"]["name"].as<std::string>();
        }

        if (root["build"]) {

            if (root["build"]["system"]) {

                config.buildSystem =
                    root["build"]["system"].as<std::string>();
            }

            if (root["build"]["generator"]) {

                config.generator =
                    root["build"]["generator"].as<std::string>();
            }

            if (root["build"]["build_type"]) {

                config.buildType =
                    root["build"]["build_type"].as<std::string>();
            }
        }

        if (root["test"] &&
            root["test"]["enabled"]) {

            config.testsEnabled =
                root["test"]["enabled"].as<bool>();
        }

        if (root["report"]) {

            if (root["report"]["format"]) {

                config.reportFormat =
                    root["report"]["format"].as<std::string>();
            }

            if (root["report"]["output"]) {

                config.reportOutput =
                    root["report"]["output"].as<std::string>();
            }
        }

        std::cout
            << "[CONFIG] Loaded buildguard.yml\n";

        return true;

    }
    catch (const YAML::Exception& error) {

        std::cout
            << "[CONFIG ERROR] "
            << error.what()
            << "\n";

        return false;
    }
}
