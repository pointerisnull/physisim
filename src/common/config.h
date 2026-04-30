#ifndef CONFIG_H
#define CONFIG_H

#define MAX_PATH 256
#define MAX_PROMPT 1024
/*KEYWORD -> SYMBOL -> static constANT -> LITERAL -> IDENTIFIER*/
#define KEYWORD_COUNT 32
#define SYMBOL_COUNT 32
#define CONSTANT_COUNT 1024
#define LITERAL_COUNT 128
#define IDENTIFIER_COUNT 1024

#define KEYWORD_T     0
#define SYMBOL_T      1
#define IDENTIFIER_T  2
#define CONSTANT_T    3
#define LITERAL_T     4
#define VALUE_T       5
#define DTYPE_T       6

static const char *KEY_INIT     = "INIT";
static const char *KEY_EVENT    = "EVENTS";
static const char *KEY_APPLY    = "APPLY";
static const char *KEY_PTCL     = "PARTICLE";
static const char *KEY_FORCE    = "FORCE";
static const char *KEY_MASS     = "MASS";
static const char *KEY_VEL      = "VELOCITY";
static const char *KEY_POS      = "POS";
static const char *KEY_MAG      = "MAG";
static const char *KEY_DENS     = "DENSITY";
static const char *KEY_ELAS     = "ELASTICITY";
static const char *KEY_RAD      = "RADIUS";
static const char *KEY_WIDTH    = "WIDTH";
static const char *KEY_HEIGHT   = "HEIGHT";

static const char *SYM_NL       = "\n";
static const char *SYM_AT       = "@";          



/*
static const char *SYM_NEWLINE = "\n";

//static const char *SYM_NEWLINE = "\n"
static const char *SYM_COMMA   = ",";
static const char *SYM_PLUS    = "+";
static const char *SYM_MINUS   = "-";
static const char *SYM_STAR    = "*";
static const char *SYM_FSLASH  = "/";
static const char *SYM_BSLASH  = "\\";
static const char *SYM_EQUALS  = "=";
static const char *SYM_MODULO  = "%";
static const char *SYM_NOT     = "!";
static const char *SYM_ADDR    = "&";
static const char *SYM_PIPE    = "|";
static const char *SYM_COMMENT = "#";
static const char *SYM_STRLIT  = "\"";
static const char *SYM_LESS    = "<";
static const char *SYM_GREATER = ">";
static const char *SYM_LPAREN  = "(";
static const char *SYM_RPAREN  = ")";
static const char *SYM_LBRACK  = "[";
static const char *SYM_RBRACK  = "[";
static const char *SYM_EQUIV   = "==";
static const char *SYM_GEQUIV  = ">=";
static const char *SYM_LEQUIV  = "<=";
static const char *SYM_PP      = "++";
static const char *SYM_MM      = "--";
static const char *SYM_PEQUALS = "+=";
static const char *SYM_MEQUALS = "-=";

static const char *KEYWORD_NULL    = "NULL";
static const char *KEYWORD_VOID    = "VOID";
static const char *KEYWORD_BEGIN   = "BEGIN";
static const char *KEYWORD_RETURN  = "RETURN";
static const char *KEYWORD_IMPORT  = "IMPORT";
static const char *KEYWORD_IF      = "IF";
static const char *KEYWORD_ELSE    = "ELSE";
static const char *KEYWORD_THEN    = "THEN";
static const char *KEYWORD_FOR     = "FOR";
static const char *KEYWORD_NEXT    = "NEXT"; //end of for loop
static const char *KEYWORD_WHILE   = "WHILE";
static const char *KEYWORD_LOOP    = "LOOP";//WEND in basic, end of while
static const char *KEYWORD_PRINT   = "PRINT";
static const char *KEYWORD_INPUT   = "INPUT";
static const char *KEYWORD_i8      = "BIT8";
static const char *KEYWORD_i16     = "BIT16";
static const char *KEYWORD_i32     = "BIT32";
static const char *KEYWORD_i64     = "BIT64";
*/

#endif
