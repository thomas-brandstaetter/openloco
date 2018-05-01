%{
    #include <iostream>
    #include <algorithm>

    #include <driver/driver.h>
    #include <scanner/scanner.h>
    #include <ast/ast.h>
    #include <parser.hh>
    #include <location.hh>
    #include <util/debug.h>

    #define YY_USER_ACTION loc.columns(yyleng);

    //extern FILE * yyin;

    #undef  YY_DECL
    #define YY_DECL openloco::lang::parser::symbol_type openloco::lang::scanner::yylex(openloco::lang::driver &driver)

    #define yyterminate() return openloco::lang::parser::make_END(loc);

    volatile bool sbcs_empty = true;
    volatile bool dbcs_empty = true;
%}

%option debug
%option c++
%option yyclass="openloco::lang::scanner"
%option noyywrap


LETTER          [a-zA-Z]
DIGIT           [0-9]
OCTAL_DIGIT     [0-7]
HEX_DIGIT       [0-9A-F]


BIT             [0-1]
INTEGER			{DIGIT}(_?{DIGIT})*
BINARY_INTEGER  "2#"{BIT}[_?{BIT}]*
OCTAL_INTEGER   "8#"{OCTAL_DIGIT}[_?{OCTAL_DIGIT}]*
HEX_INTEGER     "16#"{HEX_DIGIT}[_?{HEX_DIGIT}]*


COMMON_CHARACTER_REPRESENTATION         [A-Za-z0-9]|$[lL]|$[nN]|$[pP]|$[rR]|$[tT]
SINGLE_BYTE_CHARACTER_REPRESENTATION    {COMMON_CHARACTER_REPRESENTATION}|$'|\"|${HEX_DIGIT}{HEX_DIGIT}
DOUBLE_BYTE_CHARACTER_REPRESENTATION    {COMMON_CHARACTER_REPRESENTATION}|$\"|'|${HEX_DIGIT}{HEX_DIGIT}{HEX_DIGIT}{HEX_DIGIT}

MANTISSA        [+-]{INTEGER}\.{INTEGER}
FIXED_POINT     {INTEGER}\.{INTEGER}


%x COMMENT
%x SB_STRING
%x DB_STRING

%%

%{  /* Code executed each time yylex is called */
    loc.step();
%}

    /** @see [1] 2.1.5 */

"(*"                        { BEGIN(COMMENT); }
<COMMENT>"*)"               { BEGIN(INITIAL); }
<COMMENT>"(*"               { yyerror( "E.1 [2.1.5]: Nested comments", loc ); }
<COMMENT><<EOF>>            { yyerror( "E.1 [?.?.?]: EOF before comment is closed", loc ); }
<COMMENT>\n                 { }
<COMMENT>.                  { }


    /** @see [1] C.2 Keywords */
"ACTION"                    { return parser::make_ACTION(loc); }
"AND"                       { return parser::make_AND(loc); }
"ANY"                       { return parser::make_ANY(loc); }
"ANY_BIT"                   { return parser::make_ANY_BIT(loc); }
"ANY_DATE"                  { return parser::make_ANY_DATE(loc); }
"ANY_DERIVED"               { return parser::make_ANY_DERIVED(loc); }
"ANY_ELEMENTARY"            { return parser::make_ANY_ELEMENTARY(loc); }
"ANY_INT"                   { return parser::make_ANY_INT(loc); }
"ANY_MAGNITUDE"             { return parser::make_ANY_MAGNITUDE(loc); }
"ANY_NUM"                   { return parser::make_ANY_NUM(loc); }
"ANY_REAL"                  { return parser::make_ANY_REAL(loc); }
"ANY_STRING"                { return parser::make_ANY_STRING(loc); }
"ARRAY"                     { return parser::make_ARRAY(loc); }
"AT"                        { return parser::make_AT(loc); }
"BOOL"                      { return parser::make_BOOL(loc); }
"BY"                        { return parser::make_BY(loc); }
"BYTE"                      { return parser::make_BYTE(loc); }
"CASE"                      { return parser::make_CASE(loc); }
"CONFIGURATION"             { return parser::make_CONFIGURATION(loc); }
"CONSTANT"                  { return parser::make_CONSTANT(loc); }
"D"                         { return parser::make_D(loc); }
"DATE"                      { return parser::make_DATE(loc); }
"DATE_AND_TIME"             { return parser::make_DATE_AND_TIME(loc); }
"DINT"                      { return parser::make_DINT(loc); }
"DO"                        { return parser::make_DO(loc); }
"DT"                        { return parser::make_DT(loc); }
"DWORD"                     { return parser::make_DWORD(loc); }
"E"                         { return parser::make_E(loc); }
"ELSE"                      { return parser::make_ELSE(loc); }
"ELSIF"                     { return parser::make_ELSIF(loc); }
"EN"                        { return parser::make_EN(loc); }
"END_ACTION"                { return parser::make_END_ACTION(loc); }
"END_CASE"                  { return parser::make_END_CASE(loc); }
"END_CONFIGURATION"         { return parser::make_END_CONFIGURATION(loc); }
"END_FOR"                   { return parser::make_END_FOR(loc); }
"END_FUNCTION"              { return parser::make_END_FUNCTION(loc); }
"END_FUNCTION_BLOCK"        { return parser::make_END_FUNCTION_BLOCK(loc); }
"END_IF"                    { return parser::make_END_IF(loc); }
"END_PROGRAM"               { return parser::make_END_PROGRAM(loc); }
"END_REPEAT"                { return parser::make_END_REPEAT(loc); }
"END_RESOURCE"              { return parser::make_END_RESOURCE(loc); }
"END_STEP"                  { return parser::make_END_STEP(loc); }
"END_STRUCT"                { return parser::make_END_STRUCT(loc); }
"END_TRANSITION"            { return parser::make_END_TRANSITION(loc); }
"END_TYPE"                  { return parser::make_END_TYPE(loc); }
"END_VAR"                   { return parser::make_END_VAR(loc); }
"END_WHILE"                 { return parser::make_END_WHILE(loc); }
"ENO"                       { return parser::make_ENO(loc); }
"EXIT"                      { return parser::make_EXIT(loc); }
"FALSE"                     { return parser::make_FALSE(loc); }
"FOR"                       { return parser::make_FOR(loc); }
"FROM"                      { return parser::make_FROM(loc); }
"FUNCTION"                  { return parser::make_FUNCTION(loc); }
"FUNCTION_BLOCK"            { return parser::make_FUNCTION_BLOCK(loc); }
"F_EDGE"                    { return parser::make_F_EDGE(loc); }
"IF"                        { return parser::make_IF(loc); }
"INITIAL_STEP"              { return parser::make_INITIAL_STEP(loc); }
"INT"                       { return parser::make_INT(loc); }
"INTERVAL"                  { return parser::make_INTERVAL(loc); }
"LINT"                      { return parser::make_LINT(loc); }
"LREAL"                     { return parser::make_LREAL(loc); }
"LWORD"                     { return parser::make_LWORD(loc); }
"MOD"                       { return parser::make_MOD(loc); }
"NON_RETAIN"                { return parser::make_NON_RETAIN(loc); }
"NOT"                       { return parser::make_NOT(loc); }
"OF"                        { return parser::make_OF(loc); }
"ON"                        { return parser::make_ON(loc); }
"OR"                        { return parser::make_OR(loc); }
"PRIORITY"                  { return parser::make_PRIORITY(loc); }
"PROGRAM"                   { return parser::make_PROGRAM(loc); }
"READ_ONLY"                 { return parser::make_READ_ONLY(loc); }
"READ_WRITE"                { return parser::make_READ_WRITE(loc); }
"REAL"                      { return parser::make_REAL(loc); }
"REPEAT"                    { return parser::make_REPEAT(loc); }
"RESOURCE"                  { return parser::make_RESOURCE(loc); }
"RETAIN"                    { return parser::make_RETAIN(loc); }
"RETURN"                    { return parser::make_RETURN(loc); }
"R_EDGE"                    { return parser::make_R_EDGE(loc); }
"SINGLE"                    { return parser::make_SINGLE(loc); }
"SINT"                      { return parser::make_SINT(loc); }
"STEP"                      { return parser::make_STEP(loc); }
"STRING"                    { return parser::make_STRING(loc); }
"STRUCT"                    { return parser::make_STRUCT(loc); }
"TASK"                      { return parser::make_TASK(loc); }
"THEN"                      { return parser::make_THEN(loc); }
"TIME"                      { return parser::make_TIME(loc); }
"TIME_OF_DAY"               { return parser::make_TIME_OF_DAY(loc); }
"TO"                        { return parser::make_TO(loc); }
"TOD"                       { return parser::make_TOD(loc); }
"TRANSITION"                { return parser::make_TRANSITION(loc); }
"TRUE"                      { return parser::make_TRUE(loc); }
"TYPE"                      { return parser::make_TYPE(loc); }
"UDINT"                     { return parser::make_UDINT(loc); }
"UINT"                      { return parser::make_UINT(loc); }
"ULINT"                     { return parser::make_ULINT(loc); }
"UNTIL"                     { return parser::make_UNTIL(loc); }
"USINT"                     { return parser::make_USINT(loc); }
"VAR"                       { return parser::make_VAR(loc); }
"VAR_ACCESS"                { return parser::make_VAR_ACCESS(loc); }
"VAR_CONFIG"                { return parser::make_VAR_CONFIG(loc); }
"VAR_EXTERNAL"              { return parser::make_VAR_EXTERNAL(loc); }
"VAR_GLOBAL"                { return parser::make_VAR_GLOBAL(loc); }
"VAR_INPUT"                 { return parser::make_VAR_INPUT(loc); }
"VAR_IN_OUT"                { return parser::make_VAR_IN_OUT(loc); }
"VAR_OUTPUT"                { return parser::make_VAR_OUTPUT(loc); }
"VAR_TEMP"                  { return parser::make_VAR_TEMP(loc); }
"WHILE"                     { return parser::make_WHILE(loc); }
"WITH"                      { return parser::make_WITH(loc); }
"WORD"                      { return parser::make_WORD(loc); }
"WSTRING"                   { return parser::make_WSTRING(loc); }
"XOR"                       { return parser::make_XOR(loc); }

"%"                         { return parser::make_PERCENT(loc); }
":"                         { return parser::make_COLON(loc); }
";"                         { return parser::make_SEMICOLON(loc); }
"#"                         { return parser::make_NUM(loc); }
"("                         { return parser::make_LPAR(loc); }
")"                         { return parser::make_RPAR(loc); }
"["                         { return parser::make_LSQUAREB(loc); }
"]"                         { return parser::make_RSQUAREB(loc); }
"."                         { return parser::make_DOT(loc); }
".."                        { return parser::make_DDOT(loc); }
","                         { return parser::make_COMMA(loc); }
":="                        { return parser::make_DEF(loc); }
"+"                         { return parser::make_PLUS(loc); }
"-"                         { return parser::make_MINUS(loc); }
"*"                         { return parser::make_STAR(loc); }
"**"                        { return parser::make_SSTAR(loc); }
"=>"                        { return parser::make_MOVE_TO(loc); }

    /* B.1 Common elements */
    /* B.1.1 Letters, digits and identifiers */

({LETTER})(({LETTER}|{DIGIT}|_))+   {
        std::string value(yytext, static_cast<size_t>(yyleng));
        return parser::make_IDENTIFIER(value, loc);
    }

    /* B.1.2 Constants */
    /* B.1.2.1 Numeric literals */

{DIGIT}(_?{DIGIT})*         {

        /* INTEGER */
        std::string str_value(yytext, static_cast<size_t>(yyleng));
        cleanup_number(0, str_value);
        long value = strtol( str_value.c_str(), NULL, 10);

        return parser::make_INTEGER(value, loc);
    }

"2#"{BIT}(_?{BIT})*         {

        std::string str_value(yytext, yyleng);
        cleanup_number(2, str_value);
        long value = strtol( str_value.c_str(), NULL, 2);

        return parser::make_BINARY_INTEGER(value, loc);
    }

"8#"{OCTAL_DIGIT}(_?{OCTAL_DIGIT})* {

        std::string str_value(yytext, yyleng);
        cleanup_number(2, str_value);
        long value = strtol( str_value.c_str(), NULL, 8);

        return parser::make_OCTAL_INTEGER(value, loc);
    }

"16#"{HEX_DIGIT}(_?{HEX_DIGIT})*    {

        std::string str_value(yytext, yyleng);
        cleanup_number(3, str_value);
        long value = strtol( str_value.c_str(), NULL, 16);

        return parser::make_HEX_INTEGER(value, loc);
    }

{FIXED_POINT} {

        std::string str_value(yytext, yyleng);
        cleanup_number(0, str_value);
        double value = strtod( str_value.c_str(), NULL);

        return parser::make_FIXED_POINT(value, loc);
    }

'  { BEGIN(SB_STRING); }

<SB_STRING>{SINGLE_BYTE_CHARACTER_REPRESENTATION}* {

        sbcs_empty = false;
        std::string str_value { yytext };
        return parser::make_SINGLE_BYTE_CHARACTER_STRING(str_value, loc);
    }

<SB_STRING>' {

    BEGIN(0);

    const char *cstr_value = (sbcs_empty) ? "" : yytext;
    std::string str_value { cstr_value };

    sbcs_empty = true;
    return parser::make_SINGLE_BYTE_CHARACTER_STRING(str_value, loc);
}

\" { BEGIN(DB_STRING); }

<DB_STRING>{DOUBLE_BYTE_CHARACTER_REPRESENTATION}* {

        dbcs_empty = false;
        std::string str_value { yytext };
        return parser::make_DOUBLE_BYTE_CHARACTER_STRING(str_value, loc);
    }

<DB_STRING>\" {
    BEGIN(0);

    const char *cstr_value = (dbcs_empty) ? "" : yytext;
    std::string str_value { cstr_value };

    dbcs_empty = true;
    return parser::make_DOUBLE_BYTE_CHARACTER_STRING(str_value, loc);
}



[\t ]                   { loc.step(); }

\n                      {
                            /* EOL */
                            std::cerr << "** _scan_eol: " << _scan_eol << std::endl;
                            loc.lines(yyleng);
                            loc.step();
                            if (_scan_eol)
                                return openloco::lang::parser::make_EOL(loc);
                        }

<<EOF>>                 { return openloco::lang::parser::make_END(loc); }

.                       { return openloco::lang::parser::make_SCANNER_ERROR(loc); }

%%


void
openloco::lang::scanner::set_scan_eol() {
    _scan_eol = true;
}

void
openloco::lang::scanner::unset_scan_eol() {
    _scan_eol = false;
}

void
openloco::lang::scanner::yyerror(const char* message, location loc)
{
    std::cerr
        << "syntax error at: " << loc << "\n"
        << message
        << std::endl;
}

void
openloco::lang::scanner::cleanup_number(const unsigned long erease_end, std::string& str_value) const {

    if (erease_end > 1)
        str_value.erase(0,erease_end);
    str_value.erase(std::remove(str_value.begin(), str_value.end(), '_'), str_value.end());
}

void
openloco::lang::scanner::reset(std::istream* input_file) {
    yyrestart(input_file);
    reset_location();
}

void
openloco::lang::scanner::reset(std::istream& input_file) {
    yyrestart(input_file);
    reset_location();
}

void
openloco::lang::scanner::reset_location() {
    loc.begin.column = 1;
    loc.end.column = 1;
    loc.begin.line = 1;
    loc.end.line = 1;
}