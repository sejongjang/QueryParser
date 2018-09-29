#include "Scanner.h"
#include "tokenType.h"
#include "Token.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <vector>
//#define SCAN
//#define IDREAD
//#define SREAD

using namespace std;

void Scanner::idReader(ifstream& inFile, char last){
    stringstream ss;
    ss << last;
    char curr;
    while (isalnum(inFile.peek())){
        inFile.get(curr);
        ss << curr;
    }
    string value = ss.str();
    if (value == "Schemes") tokenList.push_back(Token(SCHEMES, value, line));
    else if (value == "Queries") tokenList.push_back(Token(QUERIES, value, line));
    else if (value == "Facts") tokenList.push_back(Token(FACTS, value, line));
    else if (value == "Rules") tokenList.push_back(Token(RULES, value, line));
    else tokenList.push_back(Token(ID, value, line));
    total++;
}

void Scanner::stringReader(ifstream& inFile){
    stringstream ss;
    ss << '\'';
    char curr;
    while (inFile.peek() != '\''){
        inFile.get(curr);
        if (curr == EOF || curr == '\n'){
            error = true;
            return;
        } else ss << curr;
    }
    inFile.get(curr);
    ss << curr;
    string value = ss.str();
    tokenList.push_back(Token(STRING, value, line));
    total++;
}

void Scanner::scan(string fileName){
    line = 1;
    error = false;
    ifstream inFile;
    inFile.open(fileName);
    char curr;
    while (inFile.get(curr) && !error){
        switch (curr){
            case ' ': break;
            case '\t': break;
            case '\n': line++;
                break;
            case '#': inFile.ignore(256, '\n');
                line++;
                break;
            case ',': tokenList.push_back(Token(COMMA, ",", line));
                total++;
                break;
            case '.': tokenList.push_back(Token(PERIOD, ".", line));
                total++;
                break;
            case '?': tokenList.push_back(Token(Q_MARK, "?", line));
                total++;
                break;
            case '(': tokenList.push_back(Token(LEFT_PAREN, "(", line));
                total++;
                break;
            case ')': tokenList.push_back(Token(RIGHT_PAREN, ")", line));
                total++;
                break;
            case ':': if (inFile.peek() == '-') {
                tokenList.push_back(Token(COLON_DASH, ":-", line));
                inFile.ignore(1,'-');
                total++;
            } else {
                tokenList.push_back(Token(COLON, ":", line));
                total++;
            }
                break;
            case '\'': stringReader(inFile);
                break;
            default: if (isalpha(curr)) idReader(inFile, curr);
            else error = true;
        }
    }
    if (!error){
        total++;
        tokenList.push_back(Token(END, "", line));
    }
}

void Scanner::printTokens(string fileName){
    ofstream outFile;
    outFile.open(fileName);
    for (unsigned int i = 0; i < tokenList.size(); i++) {
        outFile << tokenList[i].toString();
    }
    if (error) outFile << "Input Error on line " << line << endl;
    else outFile << "Total Tokens = " << total << endl;
}
