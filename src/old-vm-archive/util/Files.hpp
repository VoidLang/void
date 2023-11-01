#include "../Common.hpp"

namespace Void {
    /**
     * Represents a file manager utility.
     */
    namespace Files {
        /**
         * The separator of the different file parts used by the operating system.
         */
        const char SEPARATOR =
#ifdef _WIN32
            '\\';
#else
            '/';
#endif _WIN32

        /**
         * Check if the givn path is a directory.
         * @param path file path
         * @return true if the file is a directory
         */
        bool isDirectory(String path);

        /**
         * Check if the given path exists.
         * @param path file path
         * @return true if the file exists
         */
        bool exists(String path);

        /**
         * Recursively walk through the given directory and get all files paths within it.
         * @param directory target file
         * @param result found inner files
         */
        void walk(String directory, List<Path>& result);

        /**
         * Read the given file line by line.
         * @param file file path
         * @return file content lines
         */
        List<String> readLines(String file);

        /**
         * Read the content of the file.
         * @param file file path
         * @return file content
         */
        String readAll(String file);

        /**
         * Read the content of the file as utf-8.
         * @param file file path
         * @return utf-8 file content
         */
        UString readUTF(String file);

        /**
         * Combine the given directory with a file.
         * @param directory target directory
         * @param file target file
         * @return combined directory and file
         */
        String combine(String directory, String file);
    }
}