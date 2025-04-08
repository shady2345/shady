#define _CRT_SECURE_NO_WARNINGS  
#include <iostream>  
#include <cctype>  
#include <cstring>  
using namespace std;
int charClass; char
lexeme[100]; char
nextChar; int lexLen; int
nextToken;
string input = "M=(x * 5) / (y * 100)"; int pos = 0;
#define LETTER 1  
#define DIGIT 2  
#define UNKNOWN 99  
#define IDENT 0  
#define INT_LIT 11  
#define ASSIGN_OP 22  
#define ADD_OP 33  
#define SUB_OP 44  
#define MULT_OP 55  
#define DIV_OP 66  
#define LEFT_PAREN 77  
#define RIGHT_PAREN 88  
#define EOF_TOKEN -1  
void addChar(); void
getChar(); void
getNonBlank(); int lex(); int
lookup(char ch);
int main() {
    input +=
        " ";
    pos = 0;
    getChar();
    do {
        lex();
    } while (nextToken != EOF_TOKEN);
    return 0;
}  int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        LEFT_PAREN;
        addChar();
        break;
        nextToken =
            RIGHT_PAREN;
        addChar();
        break;
        nextToken =
    case ')':
    case '+':
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
        addChar();
    case '*':
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
        addChar();
    case '=':
        nextToken = ASSIGN_OP;




    break;     default:         addChar();
                      nextToken = EOF_TOKEN;         break;
    }
    return nextToken;
}  void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;         lexeme[lexLen]
            = '\0';
    }
    else {
        cout << "Error - lexeme is too long" << endl;
    }
}  void getChar() {
    if (pos < input.length()) {
        nextChar = input[pos++];         if
            (isalpha(nextChar))             charClass = LETTER;
        else if (isdigit(nextChar))             charClass =
            DIGIT;         else
            charClass = UNKNOWN;
    }
    else {
        charClass = EOF_TOKEN;         nextChar = ' ';
    }
}
void getNonBlank() {
    while (isspace(nextChar) && charClass != EOF_TOKEN)         getChar();
}  int lex() {
    lexLen =
        0;     getNonBlank();

    switch (charClass) {
        case
        LETTER:         addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;         break;
        case DIGIT:         addChar();
            getChar();
            while (charClass == DIGIT) {
                addChar();             getChar();
            }
            nextToken = INT_LIT;         break;
        case UNKNOWN:
            lookup(nextChar);         getChar();
        break;     case EOF_TOKEN:
            nextToken = EOF_TOKEN;
            strcpy(lexeme, "EOF");         break;
    }
    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}
