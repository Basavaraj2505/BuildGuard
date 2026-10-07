#ifndef REPORTER_H
#define REPORTER_H

#include <string>
#include "analyzer.h"

void generateReport(
    const std::string& projectPath,
    const BuildError& buildError
);

#endif
