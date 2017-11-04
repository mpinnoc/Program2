#include "lexer.h"
#include <cctype>

using namespace std;
string lexeme;
char ch;

TokenType getToken(istream* br, string& lexeme)
{
    while(!br->eof())
    {
        ch = br->get();

        /*if( ch == '\n' )
        {
            extern int lineNumber;
            ++lineNumber;
        }*/
        if(ch=='/')
        {
            lexeme += ch;
            ch=br->get();
            if (ch=='/')
            {
                return TokenType::T_DONE;
            }
            if(isalpha(ch)||ch != '/')
                br->putback(ch);
            return TokenType::T_SLASH;
        }
        if(ch == '(')
        {
            lexeme +=ch;
            return TokenType::T_LPAREN;
        }
        if(ch == ')')
        {
            lexeme +=ch;
            return TokenType::T_RPAREN;
        }
        if(ch == '-')
        {
            lexeme +=ch;
            return TokenType::T_MINUS;
        }
        if(ch == '+')
        {
            lexeme +=ch;
            return TokenType::T_PLUS;
        }
        if (ch == '*')
        {
            lexeme +=ch;
            return TokenType::T_STAR;
        }
        if(ch == ';')
        {
            lexeme +=ch;
            return TokenType::T_SC;
        }
        //String Constant
        if(ch == '"')
        {
            lexeme +=ch;
            ch = br->get();
            while(ch != '"')
            {
                lexeme +=ch;
                ch = br->get();
                if(ch == '\n')
                {
                    lexeme +=ch;
                    //ch = br->get();
                    return TokenType::T_ERROR;
                }
            }
            lexeme +=ch;
            return TokenType::T_SCONST;
        }
        //Int Constant
        if(isdigit(ch))
        {
            lexeme += ch;
            ch = br->get();
            if(ch == '.')
            {
                lexeme ="";
                lexeme += ch;
                ch = br->get();
                return TokenType::T_ERROR;
            }
            while(isdigit(ch))
            {
                lexeme += ch;
                ch = br->get();
            }
            //lexeme += ch; //// adds the plus and colon
            if(!isdigit(ch))
                br->putback(ch);
            return TokenType::T_ICONST;
        }
        //Identifers
        if(isalpha(ch))
        {
            lexeme += ch;
            ch = br->get();
            while(isalnum(ch))
            {
                lexeme += ch;
                ch = br->get();
            }
            if(lexeme == "int")
            {
                return TokenType::T_INT;
            }
            if(lexeme == "string")
            {
                return TokenType::T_STRING;
            }
            if(lexeme == "set")
            {
                return TokenType::T_SET;
            }
            if(lexeme == "print")
            {
                return TokenType::T_PRINT;
            }
            if(lexeme == "println")
            {
                return TokenType::T_PRINTLN;
            }
            if(isspace(' '))
            {
                return TokenType::T_ID;
            }
        }
    }
    if(br->eof())
    {
        return TokenType::T_DONE;
    }
    
    return TokenType();
}





