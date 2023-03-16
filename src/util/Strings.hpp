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
         * Split the string to parts using a delimiter.
         * @param source target string
         * @param seperator character to split at
         */
        List<String> split(String& source, char separator);
    }
}
