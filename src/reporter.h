#ifndef BUILDGUARD_REPORTER_H
#define BUILDGUARD_REPORTER_H

#include <string>

#include "analyzer.h"
#include "config.h"

void generateReport(
    const std::string& projectPath,
    const BuildError& buildError,
    const BuildGuardConfig& config
);

#endif
