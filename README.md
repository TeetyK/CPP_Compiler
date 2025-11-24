# CPP_Compiler
## Install
```bash
# vcpkg
git clone https://github.com/microsoft/vcpkg.git
cd vcpkg
.\bootstrap-vcpkg.bat
.\vcpkg integrate install
```
## Build CMake
```bash
# Build-CMake
cmake .. -DCMAKE_TOOLCHAIN_FILE=..\vcpkg\scripts\buildsystems\vcpkg.cmake
cmake --build.
.\program_main
```
## DEBUG
```
debug\program_main.exe
```
# TEST CASE with Catch2
```c++
TEST_CASE("Compiler Core - Basic Arithmetic", "[core][math]") {

    REQUIRE(CalculateSum(1.0, 2.0) == 3.0);

    REQUIRE(CalculateSum(5.5, 4.5) == 10.0);

    REQUIRE(CalculateSum(-10.0, 5.0) == -5.0);
}
```

```bash
===============================================================================
All tests passed (3 assertions in 1 test case)

```
# Display TEST

```bash
>.\Debug\program_main.exe test.ttt --optimize 3
Randomness seeded to: 2304627225
===============================================================================
All tests passed (3 assertions in 1 test case)

--- Project Configuration ---
Tests Passed successfully.
Input File: test.ttt
Optimization Level: O3
Compiler is ready to process test.ttt
TTT> def sum(a b) a+b;
TTT> Parsed a function definition.
TTT> sum(10,10);
TTT> Parsed a top-level expr
Intepret Result: 20
```
# SUPPORT FEATURE
support -> function ,basic operations
not support -> if then else , for in 

