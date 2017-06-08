%{

/* Declarations section */
#include <stdio.h>
#include <string.h>
char *yylval;
void showToken(char *);
void printErr();
void printEscapeErr(char * name);
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
"void"                      showToken("VOID");
"int"                         showToken("INT");
"byte"                        showToken("BYTE");
"b"                           showToken("B");
"bool"                        showToken("BOOL");
"and"                        showToken("AND");
"or"                          showToken("OR");
"not"                         showToken("NOT");
"true"                        showToken("TRUE");
"false"                       showToken("FALSE");
"return"                       showToken("RETURN");
"if"                       showToken("IF");
"else"                       showToken("ELSE");
"while"                       showToken("WHILE");
"switch"                       showToken("SWITCH");
"case"                       showToken("CASE");
"break"                       showToken("BREAK");
\:                           showToken("COLON");
\;                           showToken("SC");
\,                           showToken("COMMA");
\(                          showToken("LPAREN");
\)                          showToken("RPAREN");
\{                          showToken("LBRACE");
\}                          showToken("RBRACE");
\=                           showToken("ASSIGN");
\=\=                          showToken("RELOP");
\!\=                          showToken("RELOP");
\<                          showToken("RELOP");
\>                          showToken("RELOP");
\<\=                          showToken("RELOP");
[>][=]                          showToken("RELOP");
[+]                          showToken("BINOP");
[-]                          showToken("BINOP");
[*]                          showToken("BINOP");
[/]                          showToken("BINOP");

null                        showToken("NULL");
"0"                         showToken("NUM");
[1-9][0-9]*             showToken("NUM");
[a-zA-Z][a-zA-Z0-9]*        showToken("ID");

\"([^\n\r\"\\]|\\[rnt"\\])+\"            showToken("STRING");

<<EOF>>		{showToken("EOF"); exit(1);}
.		            printErr();

%%

void showToken(char * name)
{
        printf("%d %s %s\n", yylineno, name, yytext);
}

void printEscapeErr(char * name){
    printf("Error %s %s\n",name, yytext+1);
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
