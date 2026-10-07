#ifndef ANALYZER_H
#define ANALYZER_H

#include <string>

enum class ErrorType {
    NONE,
    SYMBOL_ERROR,
    INCLUDE_ERROR,
    LINKER_ERROR,
    SYNTAX_ERROR,
    UNKNOWN_ERROR
};

struct BuildError {
    ErrorType type;
    std::string message;
};

BuildError analyzeBuild(const std::string& projectPath);

BuildError classifyError(const std::string& line);

std::string errorTypeToString(ErrorType type);

#endif
