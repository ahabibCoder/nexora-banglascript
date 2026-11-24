%{
#include <iostream>
#include <cstdlib>
#include <cstring>
#include "parser/Driver.hpp"
#include "parser.tab.hpp"

#if defined(_WIN32) && !defined(strdup)
#define strdup _strdup
#endif

static int64_t parse_bengali_or_ascii_int(const char* text) {
    int64_t val = 0;
    for (size_t i = 0; text[i] != '\0';) {
        if (text[i] >= '0' && text[i] <= '9') {
            val = val * 10 + (text[i] - '0');
            i++;
        } else if ((unsigned char)text[i] == 0xE0 && (unsigned char)text[i+1] == 0xA7 &&
                   (unsigned char)text[i+2] >= 0xA6 && (unsigned char)text[i+2] <= 0xAF) {
            val = val * 10 + ((unsigned char)text[i+2] - 0xA6);
            i += 3;
        } else {
            i++;
        }
    }
    return val;
}

#define YY_USER_ACTION \
    yylloc->first_line = yylloc->last_line = yylineno; \
    yylloc->first_column = yycolumn; \
    yylloc->last_column = yycolumn + (int)yyleng - 1; \
    yycolumn += (int)yyleng;

static char* unescape_string(const char* text, int len) {
    char* result = (char*)malloc(len);
    int j = 0;
    // Skip opening and closing quotes
    for (int i = 1; i < len - 1; ++i) {
        if (text[i] == '\\' && i + 1 < len - 1) {
            i++;
            switch (text[i]) {
                case 'n':  result[j++] = '\n'; break;
                case 't':  result[j++] = '\t'; break;
                case 'r':  result[j++] = '\r'; break;
                case '\\': result[j++] = '\\'; break;
                case '\"': result[j++] = '\"'; break;
                default:   result[j++] = text[i]; break;
            }
        } else {
            result[j++] = text[i];
        }
    }
    result[j] = '\0';
    return result;
}
%}

%option reentrant
%option bison-bridge
%option bison-locations
%option noyywrap
%option yylineno

/* Whitespace & Newlines */
WS          [ \t\r]+
NEWLINE     \n

/* Digits & Numbers */
BENGALI_DIGIT (\xE0\xA7[\xA6-\xAF])
ASCII_DIGIT [0-9]
DIGIT       ({ASCII_DIGIT}|{BENGALI_DIGIT})
INT         {DIGIT}+
FLOAT       {DIGIT}+"."{DIGIT}+

/* Bengali & ASCII Identifiers */
BENGALI_CHAR [\xE0-\xEF][\x80-\xBF]{2}
ID_START    [a-zA-Z_]|{BENGALI_CHAR}
ID_PART     [a-zA-Z0-9_]|{BENGALI_CHAR}
IDENTIFIER  {ID_START}{ID_PART}*

/* Strings */
STRING      \"([^\"\\\n]|\\.)*\"

%%

{WS}        { /* ignore whitespace */ }
{NEWLINE}   { yycolumn = 1; }

"//".*      { /* single-line comment */ }
"/*"([^*]|\*+[^*/])*\*+"/" {
    /* multi-line comment: update line and column */
    for (int i = 0; i < yyleng; ++i) {
        if (yytext[i] == '\n') {
            yycolumn = 1;
        }
    }
}

"sonkha"|"সংখ্যা"       { return TOKEN_TYPE_SONKHA; }
"dosomik"|"দশমিক"     { return TOKEN_TYPE_DOSOMIK; }
"bakya"|"বাক্য"         { return TOKEN_TYPE_BAKYA; }
"sotti"|"সত্যি"         { return TOKEN_TYPE_SOTTI; }
"shunno"|"শূন্য"        { return TOKEN_TYPE_SHUNNO; }

"jodi"|"যদি"           { return TOKEN_JODI; }
"nahole"|"নাহলে"       { return TOKEN_NAHOLE; }
"jotokhon"|"যতক্ষণ"     { return TOKEN_JOTOKHON; }
"bondho"|"বন্ধ"         { return TOKEN_BONDHO; }
"chaliyejao"|"চালিয়েযাও" { return TOKEN_CHALIYEJAO; }
"kaj"|"কাজ"           { return TOKEN_KAJ; }
"ferot"|"ফেরত"         { return TOKEN_FEROT; }
"dekhao"|"দেখাও"       { return TOKEN_DEKHAO; }
"nao"|"নাও"           { return TOKEN_NAO; }
"true"|"সত্য"          { return TOKEN_TRUE; }
"false"|"মিথ্যা"       { return TOKEN_FALSE; }

"=="        { return TOKEN_EQ; }
"!="        { return TOKEN_NEQ; }
"<="        { return TOKEN_LE; }
">="        { return TOKEN_GE; }
"<"         { return TOKEN_LT; }
">"         { return TOKEN_GT; }
"&&"|"ebong" { return TOKEN_AND; }
"||"|"othoba" { return TOKEN_OR; }
"!"|"na"    { return TOKEN_NOT; }

"+"         { return TOKEN_PLUS; }
"-"         { return TOKEN_MINUS; }
"*"         { return TOKEN_STAR; }
"/"         { return TOKEN_SLASH; }
"%"         { return TOKEN_PERCENT; }
"="         { return TOKEN_ASSIGN; }

"("         { return TOKEN_LPAREN; }
")"         { return TOKEN_RPAREN; }
"{"         { return TOKEN_LBRACE; }
"}"         { return TOKEN_RBRACE; }
","         { return TOKEN_COMMA; }
";"         { return TOKEN_SEMICOLON; }

{FLOAT}     {
    yylval->float_val = std::atof(yytext);
    return TOKEN_FLOAT_LITERAL;
}

{INT}       {
    yylval->int_val = parse_bengali_or_ascii_int(yytext);
    return TOKEN_INT_LITERAL;
}

{STRING}    {
    yylval->str_val = unescape_string(yytext, yyleng);
    return TOKEN_STRING_LITERAL;
}

{IDENTIFIER} {
    yylval->str_val = strdup(yytext);
    return TOKEN_IDENTIFIER;
}

.           {
    // Invalid token reporting
    /* ignore or report */
}

%%
