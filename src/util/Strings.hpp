#include "../Common.hpp"

namespace Void {
    /**
     * Represents a string manipulation tool.
     */
    namespace Strings {
        /**
         * Join all the elements from a list using a separator.
         * @param list elements source
         * @param separator separator between elements
         */
        String join(List<String>& list, String separator);

        /**
         * Join all the elements from a list using a separator.
         * @param list elements source
         * @param separator separator between elements
         */
        UString join(List<UString>& list, UString separator);

        /**
         * Split the string to parts using a delimiter.
         * @param source target string
         * @param seperator character to split at
         */
        List<String> split(String& source, char separator);

        /**
         * Split the string to parts using a delimiter.
         * @param source target string
         * @param seperator character to split at
         */
        List<UString> split(UString& source, char separator);

        /**
         * Convert an utf-32 char to string.
         * @return string representation of the char
         */
        String fromUTF(char32_t c);

        /**
         * Convert an utf-32 string to an utf-8 string.
         * @return utf-8 string
         */
        String fromUTF(UString utf);
    }
}
