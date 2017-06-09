%{

/* Declarations section */
#define DEBUG 0
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include "contracts.hpp"
#include "parser.tab.hpp"
void showToken(std::string name);
void printErr();
void printEscapeErr(std::string name);
char* handleAsciiChar();
char buf[100];
char *s;

%}


%x LN_COMM
%x BK_COMM
%option yylineno
%option noyywrap

digit   		([0-9])
letter  		([a-zA-Z])
whitespace		([\t\n ])
E               ([Ee][+-]?{digit}+)
asciiTrailer    ({digit}{digit}{digit}{digit})


%%

\/\/             { BEGIN LN_COMM; s = buf; }
<LN_COMM>\n      { 
                  *s = 0;
                  BEGIN 0;
                  printf("%d %s %s\n", yylineno-1, "LN_COMMENT", buf);
                }
<LN_COMM>.    { *s++ = *yytext; }

\/\*            { BEGIN BK_COMM; s = buf; *s++ = '/'; *s++='*';}
<BK_COMM>\*\/      { 
                  *s++='*';
                  *s++ = '/';
                  *s = 0;
                  BEGIN 0;
                  printf("%d %s %s\n", yylineno, "BK_COMMENT", buf);
                }

<BK_COMM>"EOF"    { printf("Error unclosed block comment\n"); exit(0);}
<BK_COMM>.    { *s++ = *yytext; }




{whitespace}				;
"void"                         {
                                    showToken("VOID");
                                    yylval.type = _VOID;
                                    return VOID;
                               }
"int"                          {
                                    showToken("INT");
                                    yylval.type = _INT;
                                    return INT;
                               }

"byte"                         {
                                    showToken("BYTE");
                                    yylval.type = _BYTE;
                                    return BYTE;
                               }
"b"                            {showToken("B"); return B;}

"bool"                         {
                                    showToken("BOOL");
                                    yylval.type = _BOOL;
                                    return BOOL;
                               }

"and"                          {showToken("AND"); return AND;}
"or"                           {showToken("OR"); return OR;}
"not"                          {showToken("NOT");        return NOT;} 
"true"                         {
                                    showToken("TRUE");
                                    yylval.boolVal = _TRUE;
                                    yylval.type = _BOOL;
                                    return TRUE;
                               }

"false"                        {
                                    showToken("FALSE");
                                    yylval.boolVal = _FALSE;
                                    yylval.type = _BOOL;
                                    return FALSE;
                               }

"return"                       {showToken("RETURN");   return RETURN;}
"if"                           {showToken("IF");   return IF;}
"else"                     { showToken("ELSE");       return ELSE;}    
"while"                    {  showToken("WHILE");     return WHILE;}
"switch"                   {   showToken("SWITCH");     return SWITCH;}
"case"                     { showToken("CASE");     return CASE;}
"break"                    {  showToken("BREAK");     return BREAK;}
\:                         { showToken("COLON");     return COLON;}
\;                         {    showToken("SC");     return SC;}
\,                         {    showToken("COMMA");     return COMMA;}
\(                         {    showToken("LPAREN");     return LPAREN;}
\)                         {    showToken("RPAREN");     return RPAREN;}
\{                         {    showToken("LBRACE");     return LBRACE;}
\}                         {    showToken("RBRACE");     return RBRACE;}
\=                         {    showToken("ASSIGN");     return ASSIGN;}
\=\=                       {    showToken("RELOP");     return  RELOP;}  
\!\=                       {    showToken("RELOP");     return  RELOP;}
\<                         {    showToken("RELOP");     return  RELOP;}
\>                         {    showToken("RELOP");     return  RELOP;}
\<\=                       {    showToken("RELOP");     return  RELOP;}
[>][=]                     {    showToken("RELOP");     return  RELOP;}
[+]                        {    showToken("BINOP");     return   BINOP;}
[-]                        {    showToken("BINOP");     return  BINOP;}
[*]                        {    showToken("BINOP");     return  BINOP;}
[/]                        {    showToken("BINOP");     return  BINOP;}
null                       {    showToken("NULL");      return NULL;}
"0"                        {
                                showToken("NUM");
                                yylval.numVal = atoi(yytext);
                                yylval.type = _INT;
                                return NUM;
                           }

[1-9][0-9]*                {
                                showToken("NUM");
                                yylval.numVal = atoi(yytext);
                                yylval.type = _INT;
                                cout << yylval.type << ", " << yylval.numVal << endl;
                                return NUM;
                           }

[a-zA-Z][a-zA-Z0-9]*       {
                                showToken("ID");
                                yylval.varName =  yylval.stringVal = yytext;
                                yylval.type = _STRING;
                                return ID;
                           }

\"([^\n\r\"\\]|\\[rnt"\\])+\"  {
                                    showToken("STRING");
                                    yylval.stringVal = yytext;
                                    yylval.type = _STRING;
                                    return STRING;
                               }

<<EOF>>		{showToken("EOF"); exit(1);}
.		            printErr();

%%

void showToken(std::string name)
{
    #if DEBUG > 0
        cout << yylineno << " " << name << " " << yytext << endl;
    #endif
}

void printEscapeErr(std::string name)
{
    cout << "Error " << name << " " << yytext+1 << endl;
    exit(0);
}

void printErr(){
    printf("Error %s\n", yytext);
    exit(0);
}

char* handleAsciiChar(){

    char prefix = '#';
    int num = (int)strtol(yytext+2, NULL, 16);
    char * buffer = (char *) malloc(strlen(yytext));

    sprintf(buffer,"%c",prefix);
    sprintf(buffer + strlen(buffer),"%d",num);
    sprintf(buffer + strlen(buffer),"%c",prefix);

    return buffer;
}
