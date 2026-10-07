# BuildGuard

## C++ Build & CI Health Analyzer

BuildGuard is a command-line developer tool for automating C++ project builds, testing, project structure validation, build error analysis, and JSON health reporting.

The project demonstrates practical software engineering concepts including C++, CMake, Ninja, YAML configuration, Bash automation, Git, CTest, and GitHub Actions CI.

---

## Features

- C++ project structure scanning
- CMake-based build automation
- Ninja build support
- YAML-based project configuration
- Configurable build type
- CTest integration
- YAML-controlled test execution
- Compiler/build error classification
- JSON build health reports
- Git repository detection
- GitHub Actions CI
- Bash-based local CI automation
- Build time measurement

---

## Architecture

```text
                         BuildGuard CLI
                              |
             +----------------+----------------+
             |                |                |
            Scan             Build            Test
             |                |                |
          Scanner       Configuration        CTest
                           Loader
                              |
                       buildguard.yml
                              |
                        CMake + Ninja
                              |
                     Build / Compilation
                              |
                       Error Analyzer
                              |
                    JSON Report Generator
                              |
                  buildguard_report.json




Requirements
- C++17 compatible compiler
- CMake 3.20+
- Ninja
- Git
- Bash
- yaml-cpp
- CTest
BuildGuard was developed and tested using Ubuntu on WSL.
Configuration
BuildGuard uses buildguard.yml to control the build, testing, and reporting behavior.
Example configuration:
project:
  name: BuildGuard

build:
  system: cmake
  generator: Ninja
  build_type: Release

test:
  enabled: true

report:
  format: json
  output: reports/buildguard_report.json

The configuration allows the application to control:
- Build system
- Build generator
- Build type
- Test execution
- Report format
- Report output location
Build
Configure the project using CMake and Ninja:
cmake -S . -B build -G Ninja

Build the project:
cmake --build build

CLI Usage
1. Scan a Project
./build/buildguard scan .

Scans the project structure and checks for important development files and directories.
2. Build a Project
./build/buildguard build .

BuildGuard loads the configuration from buildguard.yml and performs the configured CMake/Ninja build.
Example output:
[CONFIG]
Build system: cmake
Generator: Ninja
Build type: Release

[BUILD] Configuring project...
[BUILD] Compiling project...

=================================
        BUILD SUCCESS
=================================

3. Run Tests
./build/buildguard test .

BuildGuard uses CTest to execute the project's tests.
Testing can be enabled or disabled through buildguard.yml:
test:
  enabled: true

When testing is disabled:
test:
  enabled: false

BuildGuard skips test execution.
4. Analyze a Build
./build/buildguard analyze .

BuildGuard runs the build process and analyzes the compiler/build output to identify common build errors.
5. Generate a JSON Report
./build/buildguard report .

The command analyzes the build and generates a JSON health report.
Default output:
reports/buildguard_report.json

Error Classification
BuildGuard currently identifies common compiler and build errors including:
INCLUDE_ERROR
LINKER_ERROR
SYMBOL_ERROR
SYNTAX_ERROR
UNKNOWN_ERROR

Example:
[ERROR CLASSIFICATION]
Type: INCLUDE_ERROR
Message: fatal error: example.h: No such file or directory

This allows build failures to be categorized instead of simply reporting that compilation failed.
JSON Build Report
A successful build generates a report similar to:
{
  "project": "BuildGuard",
  "build_status": "SUCCESS",
  "error_type": "NONE",
  "error_message": "",
  "build_system": "cmake",
  "generator": "Ninja",
  "build_type": "Release",
  "report_format": "json",
  "structure": {
    "cmake": true,
    "src": true,
    "tests": true,
    "git": true,
    "github_actions": true
  },
  "health_score": 100
}

The report provides information about:
- Build status
- Error classification
- Build system
- Generator
- Build type
- Project structure
- Git integration
- GitHub Actions configuration
- Overall health score
Local CI Pipeline
BuildGuard provides a Bash-based local CI pipeline.
Run:
./scripts/ci.sh

The pipeline performs four stages:
1. Build
      ↓
2. Run Tests
      ↓
3. Scan Project
      ↓
4. Generate JSON Report

Successful execution ends with:
=================================
       LOCAL CI PASSED
=================================

GitHub Actions CI
BuildGuard includes a GitHub Actions workflow that automatically validates the project.
The CI pipeline:
1. Checks out the repository
2. Installs project dependencies
3. Configures CMake
4. Builds the C++ project
5. Runs CTest
6. Runs BuildGuard project scanning
7. Generates a JSON build report
8. Displays the generated report


The workflow runs automatically for pushes and pull requests targeting the main branch.
Development Workflow

A typical development workflow is:

Modify Source Code
       ↓
Run Local CI
       ↓
./scripts/ci.sh
       ↓
Build
       ↓
Tests
       ↓
Project Scan
       ↓
JSON Report
       ↓
git commit
       ↓
git push
       ↓
GitHub Actions
       ↓
CI Validation

Technologies Used
Category	Technology
Language	C++17
Build System	CMake
Build Generator	Ninja
Testing	CTest
Configuration	YAML
Reporting	JSON
Automation	Bash
Version Control	Git
CI	GitHub Actions
Development Environment	Linux / WSL


Key Software Engineering Concepts Demonstrated
- Command-line application development
- Modular C++ design
- C++17 filesystem APIs
- Build automation
- Configuration-driven development
- CMake build management
- Automated testing
- Compiler error handling
- Build diagnostics
- JSON reporting
- Bash scripting
- Git workflow
- Continuous Integration
- Linux/WSL development
- Developer tooling


Future Improvements
Potential future improvements include:
- More detailed health-score calculation
- Additional compiler error patterns
- Robust JSON escaping
- Structured JSON serialization
- Support for additional build systems
- Parallel test execution
- More detailed Git diagnostics
- Additional unit tests
- Cross-platform Windows/Linux support
- Improved CLI argument handling

Author
Basavaraj G
