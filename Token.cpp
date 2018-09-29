#include <string>
#include <iostream>
#include <sstream>
#include "Token.h"

using namespace std;

string Token::toString(){
    stringstream ss;
    string tt;
    switch (type) {
        case COMMA: tt = "COMMA"; break;
        case PERIOD: tt = "PERIOD"; break;
        case Q_MARK: tt = "Q_MARK"; break;
        case LEFT_PAREN: tt = "LEFT_PAREN"; break;
        case RIGHT_PAREN: tt = "RIGHT_PAREN"; break;
        case COLON: tt = "COLON"; break;
        case COLON_DASH: tt = "COLON_DASH"; break;
        case SCHEMES: tt = "SCHEMES"; break;
        case FACTS: tt = "FACTS"; break;
        case RULES: tt = "RULES"; break;
        case QUERIES: tt = "QUERIES"; break;
        case ID: tt = "ID"; break;
        case STRING: tt = "STRING"; break;
        case END: tt = "EOF"; break;
    }
    ss << "(" << tt << ",\"" << value << "\"," << line << ")" << endl;
    return ss.str();
}

