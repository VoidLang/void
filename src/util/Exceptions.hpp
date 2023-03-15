#pragma once

#include "../Common.hpp"

namespace Void {
    /**
     * Represents a Winddows-level exception handler.
     */
    namespace Exceptions {
        /**
         * Get the name of the exception using exception code.
         */
        String getName(unsigned int exception);

        /**
         * Handle a windows-level exception.
         */
        int handle(unsigned int exception, ExceptionInfo* pointers);
    }
}
