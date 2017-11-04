//===================================================================
// Name        : Program 2
// Author      : Michelle Pinnock
// Version
// Description : Program 2 Part 1 Assignment
//===================================================================
#include "lexer.h"
#include <fstream>
#include <string.h>
#include <sstream>
#include <map>

using namespace std;
TokenType getToken(istream* br, string& lexeme);
TokenType tok;
map<TokenType, int> tokens;
map<TokenType, string> type;
map<string, int> ID;
int toknum;
string str="";

int main(int argc, char * argv[])
{
    ifstream myFile;
    stringstream iss;
    string lexeme;
    bool vflag = false;
    bool sflag = false;
    bool iflag = false;
    
    
    if(argc >2 && strncmp(argv[1],"-",1)!=0)
    {
        cerr << "TOO MANY FILES" << endl;
        return 0;
    }
    for(int i=1; i <argc; i++)
    {
        if(strcmp(argv[i], "-v") ==0)
        {
            vflag =true;
            continue;
        }
        if(strcmp(argv[i], "-s") ==0)
        {
            sflag =true;
            continue;
        }
        if(strcmp(argv[i], "-i") ==0)
        {
            iflag =true;
            continue;
        }
        if (strncmp(argv[i], "-",1) == 0 && strncmp(argv[i], "-v",2)!=0 && strncmp(argv[i], "-s",3)!=0 && strncmp(argv[i], "-i",4)!=0)
        {
            cerr << argv[i]<<" "<<"UNRECOGNIZED FLAG" << endl;
            return 0;
        }
        
        myFile.open(argv[i]);
        if(myFile.is_open())
        {
            
            while((tok= getToken(&myFile, lexeme))!= T_DONE && tok!=T_ERROR)
            {
                tokens[tok]++;
                
                if(tok==T_INT)
                {
                    type[tok]= "Int";
                }
                else if(tok==T_SET)
                {
                    type[tok]= "Set";
                }
                else if(tok==T_STRING)
                {
                    type[tok]= "String";
                }
                else if(tok==T_PRINT)
                {
                    type[tok]= "print";
                }
                else if(tok==T_PRINTLN)
                {
                    type[tok]= "println";
                }
                else if(tok==T_SCONST)
                {
                    type[tok]= "String Constant";
                }
                else if(tok==T_ICONST)
                {
                    type[tok]= "Int Constant";
                }
                else if(tok==T_ID)
                {
                    type[tok]= "Identifier";
                }
                else if(tok==T_LPAREN)
                {
                    type[tok]= "Left Parenthesis";
                }
                else if(tok==T_RPAREN)
                {
                    type[tok]= "Right Parenthesis";
                }
                else if(tok==T_STAR)
                {
                    type[tok]= "Star";
                }
                else if(tok==T_MINUS)
                {
                    type[tok]= "Minus";
                }
                else if(tok==T_SLASH)
                {
                    type[tok]= "Slash";
                }
                else if(tok==T_SC)
                {
                    type[tok]= "Semi Colon";
                }
                else if(tok==T_PLUS)
                {
                    type[tok]= "Plus";
                }
                
                if((vflag==true)&&(iflag==false)&&(sflag==false))
                {
                    if(tok==T_INT)
                    {
                        cout << "T_INT"<< endl;
                    }
                    else if(tok==T_SET)
                    {
                        cout << "T_SET"<< endl;
                    }
                    else if(tok==T_STRING)
                    {
                        cout << "T_STRING"<< endl;
                    }
                    else if(tok==T_PRINT)
                    {
                        cout << "T_PRINT"<< endl;
                    }
                    else if(tok==T_PRINTLN)
                    {
                        cout << "T_PRINTLN"<< endl;
                    }
                    else if(tok==T_SCONST)
                    {
                        cout << "T_SCONST(" << lexeme << ")"<< endl;
                    }
                    else if(tok==T_ICONST)
                    {
                        cout << "T_ICONST(" << lexeme << ")"<< endl;
                        
                    }
                    else if(tok==T_ID)
                    {
                        cout << "T_ID(" << lexeme << ")"<< endl;
                        
                    }
                    else if(tok==T_LPAREN)
                    {
                        cout << "T_LPAREN" << endl;
                    }
                    else if(tok==T_RPAREN)
                    {
                        cout << "T_RPAREN" << endl;
                    }
                    else if(tok==T_STAR)
                    {
                        cout << "T_STAR" << endl;
                    }
                    else if(tok==T_MINUS)
                    {
                        cout << "T_MINUS" << endl;
                    }
                    else if(tok==T_SLASH)
                    {
                        cout << "T_SLASH" << endl;
                    }
                    else if(tok==T_SC)
                    {
                        cout << "T_SC" << endl;
                    }
                    else if(tok==T_PLUS)
                    {
                        cout << "T_PLUS" << endl;
                    }
                }
                if(tok==T_ID)
                {
                    ID[lexeme]++;
                }
                if(tok==T_SCONST)
                {
                    str = lexeme;
                }
                lexeme.clear();
                
            }
            
            if(tok != T_ERROR)
            {
                map<TokenType, int>::iterator it;
                for (it = tokens.begin(); it != tokens.end(); it++)
                {
                    toknum += it->second;
                }
                
                cout << "Token count: " << toknum <<endl;
                if(tokens.empty())
                {
                    cout << "Identifier count: " << 0 << endl;
                }
                for (it = tokens.begin(); it != tokens.end(); it++)
                {
                    if(type[it->first] == "Identifier")
                        cout << "Identifier count: " << it->second << endl;
                    if(type[it->first] == "String Constant")
                        cout << "String count: " << it->second << endl;
                }
                
                if(tokens.find(T_SCONST)==tokens.end())
                    cout << "String count: " << 0 << endl;
                
                if((iflag==true)&&(vflag==false)&&(sflag==false))
                {
                    string output = "";
                    string comma = ", ";
                    for(auto it: ID)
                    {
                        string current = it.first;
                        output += current + comma;
                    }
                    output = output.substr(0, output.length()-2);
                    cout << output << endl;
                }
                if((sflag==true)&&(iflag==false)&&(vflag==false))
                {
                    if(str.length()>0)
                        cout << str << endl;
                }
                if((sflag==true)&&(iflag==true)&&(vflag==false))
                {
                    if(str.length()>0)
                        cout << str << endl;
                    
                    string output = "";
                    string comma = ", ";
                    for(auto it: ID)
                    {
                        string current = it.first;
                        output += current + comma;
                    }
                    output = output.substr(0, output.length()-2);
                    cout << output << endl;
                }
            }
            if(tok == T_ERROR)
            {
                cout << "Lexical error" <<  " T_ERROR(" << lexeme <<")" << endl;
            }
            
            
            myFile.close();
            
        }
        else
            cerr << argv[i]<< " FILE NOT FOUND" << endl;
        return 0;
        
    }
}
