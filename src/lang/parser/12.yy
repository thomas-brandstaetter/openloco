#line 1 "12.yy"
    // -----------------------------------------------------------------------
    // B.1.2 Constants
    // -----------------------------------------------------------------------
constant
    : numeric_literal
    | character_string
    | time_literal
    | bit_string_literal
    | boolean_literal
    ;

    // -----------------------------------------------------------------------
    // B.1.2.1 Numeric literals
    // -----------------------------------------------------------------------
numeric_literal
    : integer_literal   { $$.value = $1.value; }
    | real_literal      { $$.value = $1.value; }
    ;

integer_literal
    : integer_type_name integer_literal_value   { $$.value = $2.value; }
    | integer_literal_value                     { $$.value = $1.value; }
    ;

integer_literal_value
    : signed_integer    { $$ = $1; }
    | INTEGER           { $$.value = $1; }
    | BINARY_INTEGER    { $$.value = $1; }
    | OCTAL_INTEGER     { $$.value = $1; }
    | HEX_INTEGER       { $$.value = $1; }
    ;

signed_integer
    : PLUS INTEGER      { $$.value = $2; }
    | MINUS INTEGER     { $2 = -($2); $$.value = $2; }
    ;

real_literal
    : MANTISSA exponent { $$.value = std::pow($1, $2.value); }
    | FIXED_POINT exponent { $$.value = std::pow($1, $2.value); }
    | real_type_name NUM MANTISSA exponent { $$.value = std::pow($3, $4.value); }
    | real_type_name NUM FIXED_POINT exponent { $$.value = std::pow($3, $4.value); }
    ;

exponent
    : E PLUS INTEGER    { $$.value = $3; }
    | E MINUS INTEGER   { $3 = -($3);  $$.value = $3; }
    | E INTEGER         { $$.value = $2; }
    |
    ;

bit_string_literal
    : bit_string_type_name NUM bit_string_literal_value { $$.value = $3.value; }
    ;

bit_string_literal_value
    : INTEGER           { $$.value = $1; }
    | BINARY_INTEGER    { $$.value = $1; }
    | OCTAL_INTEGER     { $$.value = $1; }
    | HEX_INTEGER       { $$.value = $1; }
    ;


boolean_literal
    : BOOL NUM boolean_literal_value    { $$.value = $3.value; }
    | boolean_literal_value             { $$.value = $1.value; }
    ;

boolean_literal_value
    : "0"               { $$.value = false; }
    | "1"               { $$.value = true; }
    | TRUE              { $$.value = true; }
    | FALSE             { $$.value = false; }
	;

    // -----------------------------------------------------------------------
    // B.1.2.2 Character strings
    // -----------------------------------------------------------------------
character_string
    : SINGLE_BYTE_CHARACTER_STRING { $$.value = $1; }
    | DOUBLE_BYTE_CHARACTER_STRING { $$.value = $1; }
    ;

    // -----------------------------------------------------------------------
    // B.1.2.3 Time literals
    // -----------------------------------------------------------------------

time_literal
    : duration          { }
    | time_of_day       { }
    | date              { }
    | date_and_time     { }
    ;

    // -----------------------------------------------------------------------
    // B.1.2.3.1 Duration
    // -----------------------------------------------------------------------

    // TODO time_type_name
duration
    : "T" NUM MINUS interval    { $4 = -$4; $$ = $4; }
    | "TIME" NUM MINUS interval { $4 = -$4; $$ = $4; }
    | "T" NUM interval          { $$ = $3; }
    | "TIME" NUM interval       { $$ = $3; }
    ;

interval
    : days              { $$ = driver.dc.days_in_ms($1); }
    | hours             { $$ = driver.dc.hours_in_ms($1); }
    | minutes           { $$ = driver.dc.minutes_in_ms($1); }
    | seconds           { $$ = driver.dc.seconds_in_ms($1); }
    | milliseconds      { $$ = $1; }
    ;

days
    : FIXED_POINT "d"           { $$ = driver.dc.days_in_ms($1); }
    | INTEGER "d" "_" hours     {
        $$ = driver.dc.days_in_ms($1);
        $$ += driver.dc.hours_in_ms($4);
    }
    | INTEGER "d" hours         {
        $$ = driver.dc.days_in_ms($1);
        $$ += driver.dc.hours_in_ms($3);
    }
    ;

hours
    : FIXED_POINT "h"           { $$ = driver.dc.hours_in_ms($1); }
    | INTEGER "h" "_" minutes   {
        $$  = driver.dc.hours_in_ms($1);;
        $$ += driver.dc.minutes_in_ms($4);;
    }
    | INTEGER "h" minutes {
        $$  = driver.dc.hours_in_ms($1);;
        $$ += driver.dc.minutes_in_ms($3);;
    }
    ;

minutes
    : FIXED_POINT "m"           { $$ = driver.dc.minutes_in_ms($1); }
    | INTEGER "m" seconds       {
        $$ += driver.dc.minutes_in_ms($1);
        $$ += driver.dc.seconds_in_ms($3);
    }
    | INTEGER "m" "_" seconds   {
        $$ += driver.dc.minutes_in_ms($1);
        $$ += driver.dc.seconds_in_ms($4);
    }
    ;

seconds
    : FIXED_POINT "s"           { $$ = driver.dc.seconds_in_ms($1); }
    | INTEGER "s" milliseconds  { $$ += driver.dc.seconds_in_ms($1); $$ += $3; }
    | INTEGER "s" "_" milliseconds { $$ += driver.dc.seconds_in_ms($1); $$ += $4; }
    ;

milliseconds
    : FIXED_POINT "ms"          { $$ = $1; }
    ;

    // -----------------------------------------------------------------------
    // B.1.2.3.2 Time of day and date
    // -----------------------------------------------------------------------
time_of_day
    : TIME_OF_DAY NUM daytime   { $$ = $3; }
    | TOD NUM daytime           { $$ = $3; }
    ;

daytime: day_hour COLON day_minute COLON day_second {
        $$.hour = $1;
        $$.minute = $3;
        $$.second = $5;
    }
    ;

day_hour: INTEGER       { $$ = $1; };
day_minute: INTEGER     { $$ = $1; };
day_second: FIXED_POINT { $$ = $1; };

date
    : DATE NUM date_literal
    | D NUM date_literal
    ;

date_literal: year MINUS month MINUS day {
        $$.year = $1;
        $$.month = $3;
        $$.day = $5;
    }
    ;

year: INTEGER           { $$ = $1; };
month: INTEGER          { $$ = $1; };
day: INTEGER            { $$ = $1; };

date_and_time
    : DATE_AND_TIME NUM date_literal MINUS daytime {
        $$.date = $3;
        $$.time = $5;
    }
    | DT NUM date_literal MINUS daytime {
        $$.date = $3;
        $$.time = $5;
    }
    ;
