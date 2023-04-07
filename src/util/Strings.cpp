#include "Strings.hpp"
#include <codecvt>

#pragma warning(disable : 4996)

namespace Void {
    /**
     * Join all the elements from a list using a separator.
     * @param list elements source
     * @param separator separator between elements
     */
    String Strings::join(List<String>& list, String separator) {
        // declare the final string result
        String value = "";
        // concat the elements of the list
        for (ulong i = 0; i < list.size(); i++) {
            // append the list element
            value += list[i];
            // append the separator if there are more elements remaining
            if (i < list.size() - 1)
                value += separator;
        }
        return value;
    }

    /**
     * Join all the elements from a list using a separator.
     * @param list elements source
     * @param separator separator between elements
     */
    UString Strings::join(List<UString>& list, UString separator) {
        // declare the final string result
        UString value = U"";
        // concat the elements of the list
        for (ulong i = 0; i < list.size(); i++) {
            // append the list element
            value += list[i];
            // append the separator if there are more elements remaining
            if (i < list.size() - 1)
                value += separator;
        }
        return value;
    }

    /**
     * Split the string to parts using a delimiter.
     * @param source target string
     * @param seperator character to split at
     */
    List<String> Strings::split(String& source, char separator) {
        // declare the split result
        List<String> result;

        // find the first position
        ulong pos = source.find(separator);
        ulong initPos = 0;

        // decompose the statement
        while (pos != String::npos) {
            result.push_back(source.substr(initPos, pos - initPos));
            initPos = pos + 1;

            pos = source.find(separator, initPos);
        }

        // add the last one
        result.push_back(source.substr(initPos, std::min(pos, source.size()) - initPos + 1));

        return result;
    }

    /**
     * Split the string to parts using a delimiter.
     * @param source target string
     * @param seperator character to split at
     */
    List<UString> Strings::split(UString& source, char separator) {
        // declare the split result
        List<UString> result;

        // find the first position
        ulong pos = source.find(separator);
        ulong initPos = 0;

        // decompose the statement
        while (pos != String::npos) {
            result.push_back(source.substr(initPos, pos - initPos));
            initPos = pos + 1;

            pos = source.find(separator, initPos);
        }

        // add the last one
        result.push_back(source.substr(initPos, std::min(pos, source.size()) - initPos + 1));

        return result;
    }

    /**
     * Convert an utf-32 char to string.
     * @return string representation of the char
     */
    String Strings::fromUTF(char32_t c) {
        // convert to std::string
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        return converter.to_bytes(c);
    }

    /**
     * Convert an utf-32 string to an utf-8 string.
     * @return utf-8 string
     */
    String Strings::fromUTF(UString utf) {
        // create a UTF-8 codecvt facet
        std::wstring_convert<std::codecvt_utf8<char32_t>, char32_t> converter;
        return converter.to_bytes(utf);
    }

    /**
     * Fill a new string with the given string n times.
     * @param count fill count
     * @param string fill source
     * @return filled string content
     */
    String Strings::fill(uint count, String string) {
        String result = "";
        for (uint i = 0; i < count; i++)
            result += string;
        return result;
    }
}
