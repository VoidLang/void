#include "Lists.hpp"

namespace Void {
    /**
     * Create a sub-list from a begin and end index
     */
    List<String> Lists::subList(List<String> list, ulong begin) {
        return List<String>(list.begin() + begin, list.begin() + begin);
    }

    /**
     * Create a list with the given varargs passed.
     */
    List<String> Lists::asList(uint size, ...) {
        // declare the list of the dynamic arguments
        List<String> result;

        // begin the processing of the varargs
        va_list list;
        va_start(list, size);

        // handle vararg parameters
        for (uint i = 0; i < size; i++)
            result.push_back(String(va_arg(list, char*)));

        // end varargs processing
        va_end(list);
        return result;
    }
}
