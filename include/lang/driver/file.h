#pragma once

#include <istream>
#include <string>
#include <vector>
#include <streambuf>

namespace openloco {
namespace lang {

    class file_streambuffer;
    class scanner;

#pragma mark - file
    /**
     * Represents an input file for the parsing process. It keeps track of
     * lines for better error reporting.
     *
     * @details The purpose of the class is to write missing flex behaviour.
     * Flex lacks of support of getting the current line it's reading from.
     */
    class file
    {
    public:

        /** \addtogroup File operations */
        /** @{ */

        /**
         * Read file into buffer
         * @param filename The filename of the file to open
         */
        void open(std::string& filename);

        /**
         * Read istream into buffer
         * @param in The inputstream to be read
         */
        void open(std::istream& in);

        /** Empty buffer */
        void reset();

        /** @} */

        /** \addtogroup Access */
        /** @{ */

        /**
         * @param number
         * @return
         */
        std::string get_line(unsigned long number);

        /** @} */

        friend file_streambuffer;
        friend scanner;
    private:
        std::vector<std::string> _lines;
    };

#pragma mark - file_streambuffer
    /**
     * Represents an streambuf for file in order to use a file as istream object.
     */
    class file_streambuffer : public std::streambuf
    {
    public:
        explicit file_streambuffer(file& infile) : _infile(infile), _current_line(0)
        {
        }

    private:
        int_type underflow() override;


    private:
        file &_infile;
        long _current_line;
    };
}}
