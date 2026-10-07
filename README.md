# 🛡️ BuildGuard

## C++ Build & CI Health Analyzer

[![C++17](https://img.shields.io/badge/C%2B%2B-17-blue.svg)](https://isocpp.org/)
[![CMake](https://img.shields.io/badge/Build-CMake-red.svg)](https://cmake.org/)
[![Ninja](https://img.shields.io/badge/Generator-Ninja-green.svg)](https://ninja-build.org/)
[![CI](https://img.shields.io/badge/CI-GitHub%20Actions-blue.svg)](https://github.com/features/actions)
[![Tests](https://img.shields.io/badge/Tests-CTest-orange.svg)](https://cmake.org/cmake/help/latest/module/CTest.html)

BuildGuard is a **C++ command-line developer tool** that automates project building, testing, project structure validation, build error analysis, and JSON health reporting.

It combines **C++, CMake, Ninja, YAML, Bash, Git, CTest, and GitHub Actions** into a practical developer workflow for detecting build issues and validating project health.

---

## 🚀 Why BuildGuard?

Build failures often require developers to manually inspect compiler output, run tests, check project structure, and verify CI configuration.

BuildGuard brings these tasks together into a single CLI workflow.

```text
Build
  ↓
Test
  ↓
Scan
  ↓
Analyze
  ↓
Generate Report
  ↓
CI Validation
```

Instead of manually checking multiple tools, developers can use BuildGuard to get a consistent view of the project's build and CI health.

---

## ✨ Features

### 🔨 Build Automation

- CMake-based C++ project configuration
- Ninja build generation
- Configurable build type
- Build time measurement
- Automated compilation

### 🧪 Testing

- CTest integration
- Unit tests
- Integration tests
- YAML-controlled test execution
- Automatic test execution in CI

### 🔍 Project Analysis

- Project structure scanning
- CMake configuration detection
- Source directory validation
- Test directory validation
- Git repository detection
- GitHub Actions configuration detection

### 🚨 Build Error Analysis

BuildGuard analyzes compiler output and classifies common build failures into categories:

- `INCLUDE_ERROR`
- `LINKER_ERROR`
- `SYMBOL_ERROR`
- `SYNTAX_ERROR`
- `UNKNOWN_ERROR`

Example:

```text
[ERROR CLASSIFICATION]
Type: INCLUDE_ERROR
Message: fatal error: example.h: No such file or directory
```

### 📊 JSON Reporting

BuildGuard generates a machine-readable JSON report containing:

- Build status
- Error classification
- Build system
- Generator
- Build type
- Project structure
- Git configuration
- GitHub Actions configuration
- Health score

### ⚙️ Configuration

Build behavior can be controlled using a YAML configuration file instead of hard-coding project settings.

### 🔄 CI Automation

BuildGuard provides:

- Bash-based local CI
- GitHub Actions CI
- Automated build validation
- Automated testing
- Project scanning
- JSON report generation

---

# 🏗️ Architecture

```text
                         ┌─────────────────────┐
                         │   BuildGuard CLI     │
                         │      main.cpp       │
                         └──────────┬──────────┘
                                    │
             ┌──────────────────────┼──────────────────────┐
             │                      │                      │
             ▼                      ▼                      ▼
      ┌─────────────┐       ┌─────────────┐       ┌─────────────┐
      │   Scanner   │       │    Build    │       │    Test     │
      │ scanner.cpp │       │   Manager   │       │   Manager    │
      └─────────────┘       └──────┬──────┘       └──────┬──────┘
                                    │                      │
                                    ▼                      ▼
                             ┌─────────────┐        ┌─────────────┐
                             │ CMake/Ninja │        │    CTest    │
                             └──────┬──────┘        └─────────────┘
                                    │
                                    ▼
                             ┌─────────────┐
                             │   Analyzer  │
                             │ analyzer.cpp│
                             └──────┬──────┘
                                    │
                                    ▼
                             ┌─────────────┐
                             │   Reporter  │
                             │ reporter.cpp│
                             └──────┬──────┘
                                    │
                                    ▼
                         ┌─────────────────────┐
                         │   JSON Build Report │
                         │ buildguard_report   │
                         └─────────────────────┘

                    Configuration
                         │
                         ▼
                  buildguard.yml
```

---

# 📁 Project Structure

```text
BuildGuard/
│
├── src/
│   ├── main.cpp
│   ├── scanner.cpp
│   ├── scanner.h
│   ├── build_manager.cpp
│   ├── build_manager.h
│   ├── test_manager.cpp
│   ├── test_manager.h
│   ├── analyzer.cpp
│   ├── analyzer.h
│   ├── reporter.cpp
│   ├── reporter.h
│   ├── config.cpp
│   └── config.h
│
├── tests/
│   └── test_buildguard.cpp
│
├── scripts/
│   ├── build.sh
│   └── ci.sh
│
├── .github/
│   └── workflows/
│       └── ci.yml
│
├── buildguard.yml
├── CMakeLists.txt
├── README.md
└── .gitignore
```

---

# 🛠️ Technologies

| Category | Technology |
|----------|------------|
| Language | C++17 |
| Build System | CMake |
| Build Generator | Ninja |
| Testing | CTest |
| Configuration | YAML |
| Reporting | JSON |
| Automation | Bash |
| Version Control | Git |
| CI | GitHub Actions |
| Environment | Linux / WSL |

---

# 📋 Requirements

Before building BuildGuard, make sure the following are installed:

- C++17 compatible compiler
- CMake 3.20+
- Ninja
- Git
- Bash
- yaml-cpp
- CTest

BuildGuard was developed and tested using **Ubuntu on WSL**.

---

# ⚙️ Configuration

BuildGuard uses `buildguard.yml` to control build, testing, and reporting behavior.

### Example

```yaml
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
```

### Configuration Options

| Section | Option | Description |
|---------|--------|-------------|
| `project` | `name` | Project name |
| `build` | `system` | Build system |
| `build` | `generator` | Build generator |
| `build` | `build_type` | CMake build type |
| `test` | `enabled` | Enable or disable tests |
| `report` | `format` | Report format |
| `report` | `output` | Report output path |

---

# 🔨 Building the Project

### 1. Configure

```bash
cmake -S . -B build -G Ninja
```

### 2. Build

```bash
cmake --build build
```

Successful output:

```text
=================================
        BUILD SUCCESS
=================================
```

---

# 💻 CLI Usage

BuildGuard provides several commands.

## 1. Scan

Scan the project structure:

```bash
./build/buildguard scan .
```

The scanner checks for important project components such as:

- `CMakeLists.txt`
- `src/`
- `tests/`
- `.git/`
- `.github/`
- C++ source files

---

## 2. Build

Build the project using the YAML configuration:

```bash
./build/buildguard build .
```

Example:

```text
[CONFIG]
Build system: cmake
Generator: Ninja
Build type: Release

[BUILD] Configuring project...
[BUILD] Compiling project...

=================================
        BUILD SUCCESS
=================================
Build time: 3.175 seconds
```

---

## 3. Test

Run the project's tests:

```bash
./build/buildguard test .
```

BuildGuard uses CTest to execute the configured tests.

Example:

```text
=================================
       BuildGuard Tests
=================================

[TEST] Testing is enabled.
[TEST] Running CTest...

100% tests passed, 0 tests failed out of 2

=================================
        TESTS PASSED
=================================
```

### Disable Testing

Tests can be disabled through YAML:

```yaml
test:
  enabled: false
```

BuildGuard then skips test execution:

```text
[TEST] Testing is disabled in buildguard.yml.
[TEST] Skipping test execution.
```

---

## 4. Analyze

Analyze the build output:

```bash
./build/buildguard analyze .
```

The analyzer detects and classifies common compiler/build errors.

---

## 5. Generate Report

Generate a JSON build health report:

```bash
./build/buildguard report .
```

The report is generated at:

```text
reports/buildguard_report.json
```

---

# 🚨 Error Classification

BuildGuard currently supports the following error categories:

| Error Type | Description |
|------------|-------------|
| `INCLUDE_ERROR` | Missing header or include file |
| `LINKER_ERROR` | Linker or undefined reference failure |
| `SYMBOL_ERROR` | Undeclared or missing symbol |
| `SYNTAX_ERROR` | Common syntax-related compiler error |
| `UNKNOWN_ERROR` | Error that could not be classified |

### Example

Input:

```text
fatal error: scanner_missing.h: No such file or directory
```

BuildGuard reports:

```text
[ERROR CLASSIFICATION]
Type: INCLUDE_ERROR
Message: fatal error: scanner_missing.h: No such file or directory
```

This makes build failures easier to understand than simply returning a generic compilation failure.

---

# 📊 JSON Build Report

A successful build produces a report similar to:

```json
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
```

The report provides a machine-readable representation of project health that can be consumed by other tools or CI workflows.

---

# 🧪 Testing

BuildGuard currently contains:

### Integration Test

```text
BuildGuardScanTest
```

Validates the project scanning functionality through the actual BuildGuard executable.

### Unit Tests

```text
BuildGuardUnitTests
```

The unit test suite validates:

- Include error classification
- Linker error classification
- Symbol error classification
- Syntax error classification
- Normal build output
- YAML configuration loading

Run all tests with:

```bash
ctest --test-dir build --output-on-failure
```

Expected result:

```text
100% tests passed, 0 tests failed out of 2
```

---

# 🔄 Local CI Pipeline

BuildGuard provides a Bash-based local CI workflow.

Run:

```bash
./scripts/ci.sh
```

The pipeline performs:

```text
┌───────────────────────┐
│ 1. Build Project      │
└───────────┬───────────┘
            ↓
┌───────────────────────┐
│ 2. Run Tests          │
└───────────┬───────────┘
            ↓
┌───────────────────────┐
│ 3. Scan Project       │
└───────────┬───────────┘
            ↓
┌───────────────────────┐
│ 4. Generate Report    │
└───────────┬───────────┘
            ↓
       CI PASSED
```

Successful execution ends with:

```text
=================================
       LOCAL CI PASSED
=================================
```

---

# ☁️ GitHub Actions CI

BuildGuard uses GitHub Actions for continuous integration.

Every push or pull request targeting `main` triggers the CI workflow.

### CI Pipeline

```text
Checkout Repository
        ↓
Install Dependencies
        ↓
Configure CMake
        ↓
Build Project
        ↓
Run CTest
        ↓
Run BuildGuard Scan
        ↓
Generate JSON Report
        ↓
Display Report
```

### CI Validation

The pipeline verifies that:

- The project configures successfully
- The C++ project compiles
- Unit tests pass
- Integration tests pass
- BuildGuard scanning works
- JSON report generation works

---

# 🔁 Development Workflow

A typical development workflow looks like this:

```text
        Modify Code
             ↓
      Run Local CI
             ↓
     ./scripts/ci.sh
             ↓
     Build + Test + Scan
             ↓
       JSON Report
             ↓
        git commit
             ↓
         git push
             ↓
     GitHub Actions CI
             ↓
       CI Validation
```

This provides a repeatable development and validation process.

---

# 🧠 Software Engineering Concepts

BuildGuard demonstrates practical knowledge of:

- Command-line application development
- Modular C++ design
- C++17 filesystem APIs
- Build automation
- Configuration-driven development
- CMake build management
- Ninja build generation
- Automated testing
- Unit testing
- Integration testing
- Compiler error handling
- Build diagnostics
- JSON reporting
- Bash scripting
- Git workflow
- Continuous Integration
- Linux/WSL development
- Developer tooling

---

# 🎯 Why This Project?

BuildGuard was designed as a practical developer-tooling project rather than a simple CRUD or demonstration application.

The project focuses on areas commonly encountered in software development environments:

- Build systems
- Developer tooling
- Automated testing
- CI pipelines
- Build diagnostics
- Configuration management
- Linux development
- Git workflows

---

# 🔮 Future Improvements

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
- More advanced build diagnostics

---

# 👨‍💻 Author

**Basavaraj G**

Computer Science Engineering

### BuildGuard

> C++ Build & CI Health Analyzer
>
> A developer-focused tool for automated builds, testing, diagnostics, reporting, and CI validation.
