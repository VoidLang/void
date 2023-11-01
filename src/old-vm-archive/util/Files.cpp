#include "Files.hpp"

#include <fstream>
#include <string>
#include <codecvt>

#pragma warning(disable : 4996)

namespace Void {
    /**
     * Check if the givn path is a directory.
     * @param path file path
     * @return true if the file is a directory
     */
    bool Files::isDirectory(String path) {
        return fileIsDirectory(path);
    }

    /**
     * Check if the given path exists.
     * @param path file path
     * @return true if the file exists
     */
    bool Files::exists(String path) {
        return fileExists(path);
    }

    /**
     * Recursively walk through the given directory and get all files paths within it.
     * @param directory target file
     * @param result found inner files
     */
    void Files::walk(String directory, List<Path>& result) {
        // create a new directory iterator and walk through the directory
        for (DirEntiry entry : DirIterator(directory)) {
            // get the path of the current entry
            Path path = entry.path();
            // continue recursive search if the entry is a directory
            if (fileIsDirectory(path))
                Files::walk(path.generic_string(), result);
            // entry is a file, append its path to the result
            else
                result.push_back(path);
        }
    }

    /**
     * Read the given file line by line.
     * @param file file path
     * @return file content lines
     */
    List<String> Files::readLines(String file) {
        // create a new file reader
        FileReader reader;
        reader.open(file);

        // check if the file is not accessible
        if (reader.fail())
            error("Unable to read file: " << file);

        // declare variables for reading
        List<String> lines;
        String line;

        // read the file line by line
        while (readNextLine(reader, line))
            lines.push_back(line);

        // finished file reading
        return lines;
    }

    /**
     * Read the content of the file.
     * @param file file path
     * @return file content
     */
    String Files::readAll(String file) {
        // create a new file reader
        FileReader reader;
        reader.open(file);

        // check if the file is not accessible
        if (reader.fail())
            error("Unable to read file: " << file);

        // declare variables for reading
        String line, content;
        // read the file line by line
        while (readNextLine(reader, line))
            content += line + '\n';

        // finished file reading
        return content;
    }

    /**
     * Read the content of the file as utf-8.
     * @param file file path
     * @return utf-8 file content
     */
    UString Files::readUTF(String file) {
        // create a new file reader
        FileReader reader(file, std::ios_base::binary);
        // check if the file is not accessible
        
        if (!reader)
            error("Unable to read file: " << file);

        // Get the file size
        reader.seekg(0, std::ios_base::end);
        std::streampos fileSize = reader.tellg();
        reader.seekg(0, std::ios_base::beg);

        // Read the file contents into a string
        std::string utf8String(fileSize, '\0');
        reader.read(utf8String.data(), fileSize);

        // Convert the string to a u32string
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        std::u32string utf32String = converter.from_bytes(utf8String);

        return utf32String;
    }

    /**
     * Combine the given directory with a file.
     * @param directory target directory
     * @param file target file
     * @return combined directory and file
     */
    String Files::combine(String directory, String file) {
        Path path = directory;
        path /= file;
        return path.generic_string();
    }
}