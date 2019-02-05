=====================
openloco - code style
=====================

C++ Version
-----------

Code should target C++17.

Header Files
------------

In general every `.cc` file should have an associated `.h` file.
There are some exceptions, such as unittests and small `.cc` files containing just a `main()` function.

Self-contained Headers
``````````````````````

Header files should be self-contained (compile on their own) and end in `.h`.

The Include Guard
`````````````````

All header files should contain the following include guard:

.. code:: c++

    #pragma once


Names and Order of Includes
```````````````````````````

1. foo/bar.h.
2. A blank line
3. C system files.
4. C++ system files.
5. A blank line
6. Other libraries' .h files.
7. openloco project's .h files.

Any adjacent blank lines should be collapsed.
This is an example the the file `src/foo/bar.cc`:

.. code:: c++

    #include "foo/bar.h"

.. code:: c++

    #include <sys/types.h>
    #include <unistd.h>
    #include <vector>

.. code:: c++

    #include "base/basictypes.h"
    #include "base/commandlineflags.h"
    #include "foo/server/bar.h"


Namespaces
----------

The layout of section namespaces `src/foo/bar/object.h` should have following form:

.. code c++

    namespace foo {
    namespace bar {
        class Object
        {
        };
    }}


Classes and Structs
-------------------

Name of classes and structs
```````````````````````````

The name of classes and structs should be written in `CamelCase` in files called `camel_case.(cc|h)`.
The only exceptions are IEC types like `bit_string_literal`


:Authors:
    Thomas Brandstätter (brandstifter)

:Version: 0.1 of 2019/01/24:
