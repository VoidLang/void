#pragma once

#include "../Common.hpp"

namespace Void {
    /**
     * Represents a list helper tool.
     */
    namespace Lists {
        /**
         * Create a sub-list from a begin and end index
         */
        List<String> subList(List<String> list, ulong begin);

        /**
         * Create a list with the given varargs passed.
         */
        List<String> asList(uint size, ...);
    }
}
