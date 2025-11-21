#pragma once
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <utility>
#include <vector>

enum Token {
    tok_eof = -1,
    // command
    tok_def = -2,
    tok_extern = -3,
    // primary
    tok_identifier = -4,
    tok_number = -5,
};

extern std::string IdentifierStr;
extern double NumVal;
int gettok();