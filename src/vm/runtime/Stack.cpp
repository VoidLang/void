#include "Stack.hpp"

namespace Void {
    /**
     * Initialize the stack.
     * @param parent parent stack of this stack
     * @param name stack caller name
     */
    Stack::Stack(Stack* parent, String name) 
        : parent(parent), name(name), offset(parent == nullptr ? 0 : parent->offset + 1)
    { }

    /**
     * Recursively get the current stack trace.
     * @param result stack trace list
     */
    void Stack::stackTrace(List<Stack*>& result) {
        // add this stack to the result
        result.push_back(this);
        // make the parent stack add their parents recursively
        if (parent != nullptr)
            parent->stackTrace(result);
    }
}