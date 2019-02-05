#pragma once

#include <istream>
#include <string>
#include <vector>
#include <streambuf>

namespace openloco {
namespace lang {

    class FileStreambuffer;

#pragma mark - file
    /**
     * Represents an input file for the parsing process. It keeps track of
     * lines for better error reporting.
     *
     * @details The purpose of the class is to write missing flex behaviour.
     * Flex lacks of support of getting the current line it's reading from.
     */
    class File
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
        const std::string get_line(unsigned long number) const;

        /** @} */

        friend FileStreambuffer;
    private:
        std::vector<std::string> _lines;
    };

#pragma mark - file_streambuffer
    /**
     * Represents an streambuf for file in order to use a file as istream object.
     */
    class FileStreambuffer : public std::streambuf
    {
    public:
        explicit FileStreambuffer(File& infile) : _infile(infile), _current_line(0)
        {
        }

    private:
        int_type underflow() override;


    private:
        File &_infile;
        long _current_line;
    };
}}
