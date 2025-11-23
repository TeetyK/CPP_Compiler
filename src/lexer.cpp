#include "lexer.h"
std::string IdentifierStr;
double NumVal;

int gettok(){
    static int LastChar = ' ';
    // skip while space
    while(isspace(LastChar)){
        LastChar = getchar();
    }
    // identifiers : [a-zA-Z][a-zA-Z0-9]*
    if(isalpha(LastChar)){
        IdentifierStr = LastChar;
        while(isalnum(LastChar = getchar())){
            IdentifierStr +=LastChar;
        }
        if(IdentifierStr=="def"){return tok_def;}
        if(IdentifierStr=="extern"){return tok_extern;}
        if(IdentifierStr=="Hello"){return tok_hello;}
        return tok_identifier;
    }
    if(isdigit(LastChar) || LastChar == '.'){ // Number : [0-9.]+
        std::string NumStr;
        do{
            NumStr+=LastChar;
            LastChar = getchar();
        }while(isdigit(LastChar) || LastChar=='.');
        NumVal = strtod(NumStr.c_str(),0);
        return tok_number;
    }

    if(LastChar == '#'){
        do{
            LastChar = getchar();
        }
        while(LastChar != EOF && LastChar !='\n' && LastChar !='\r');
        if ( LastChar != EOF){
            return gettok();
        }
    }
    if(LastChar == EOF){
        return tok_eof;
    }
    int ThisChar = LastChar;
    LastChar = getchar();
    return ThisChar;
}