============================
openloco - coding guidelines
============================

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

Classes and Structs
-------------------

Name of Classes
---------------

The name should be written in `CamelCase` in a files called `camel_case.(cc|h)`.




:Authors:
    Thomas Brandstätter (brandstifter)

:Version: 0.1 of 2018/08/15:
