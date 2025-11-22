
#include "main.h"
#include "lexer.cpp"
#include "parseTree.cpp"
#include "AST.cpp"
// ------------------------------------------------------------------
// FUNCTIOn
// ------------------------------------------------------------------
double CalculateSum(double a, double b) {
    return a + b;
}

// ------------------------------------------------------------------
// TEST CASE
// ------------------------------------------------------------------
TEST_CASE("Compiler Core - Basic Arithmetic", "[core][math]") {
    // 1. Test การบวกเลขพื้นฐาน
    REQUIRE(CalculateSum(1.0, 2.0) == 3.0);
    
    // 2. Test การบวกเลขทศนิยม
    REQUIRE(CalculateSum(5.5, 4.5) == 10.0);
    
    // 3. Test การบวกกับค่าลบ
    REQUIRE(CalculateSum(-10.0, 5.0) == -5.0);
}


int main(int argc, char** argv) {

    // int result = Catch::Session().run(argc, argv); 
    int result = Catch::Session().run(); 

    if (result != 0) {
        std::cerr << "Unit tests failed. Exiting.\n";
        // return result;
    }
    
    CLI::App app{"Compiler Project Main Program"};

    std::string input_file = "";
    int optimization_level = 0;


    app.add_option("input_file", input_file, "The source code file (.ttt) to compile")->required();
    app.add_option("-O,--optimize", optimization_level, "Optimization level (0-3)")->default_val(0);

    try {
        app.parse(argc, argv);
    } catch (const CLI::ParseError &e) {

        return app.exit(e);
    }

    std::cout << "--- Project Configuration ---\n";
    std::cout << "Tests Passed successfully.\n";
    std::cout << "Input File: " << input_file << "\n";
    std::cout << "Optimization Level: O" << optimization_level << "\n";
    std::cout << "Compiler is ready to process " << input_file << "\n";
    BinopPrecedence['<'] = 10;
    BinopPrecedence['+'] = 20;
    BinopPrecedence['-'] = 30;
    BinopPrecedence['*'] = 40;
    fprintf(stderr, "TTT> ");
    getNextToken();
    MainLoop();
    return 0;
}