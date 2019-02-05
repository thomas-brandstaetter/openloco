A Specification method for textual languages
============================================

A 1. Syntax
-----------

A syntax is defined by a set of `terminal symbols` to be utilized for program
specification, set of `non-terminal symbols` defined in terms of the terminal
symbols and a set of production rules specifying those definitions.

A 1.1 Terminal symbols
~~~~~~~~~~~~~~~~~~~~~~

Consists of compinations of the characters in the character set defined by
the machine.
For this purpose the terminal textutal symbols of the character string
exclosed by single or double quotes.


A 1.2 Non-terminal symbols
~~~~~~~~~~~~~~~~~~~~~~~~~~

Non-terminal textual symbols shall be represented by strings of lower-case
letters, numbers, and the underline character (_), beginning with a
lower-case letter. For instance, the strings

::

    non-terminal or non_terminal_2

A.1.3 Production rules
~~~~~~~~~~~~~~~~~~~~~~

::

    non_terminal : extended_structure;

    extended_structure
        is "" or NIL
        or terminal_symbol
        or (S) or {S} or [S]
        or S1 | S2
        or S1 S2

