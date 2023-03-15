#include "Strings.hpp"

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
}