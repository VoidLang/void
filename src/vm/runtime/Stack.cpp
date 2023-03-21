#include "Stack.hpp"
#include "../../util/Strings.hpp"

namespace Void {
    class Executable;

    /**
     * Initialize the stack.
     * @param parent parent stack of this stack
     * @param executable stack creator executable
     * @param name stack name
     */
    Stack::Stack(Stack* parent, Executable* executable, String name) 
        : parent(parent), executable(executable), offset(parent == nullptr ? 0 : parent->offset + 1), name(name)
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

    /**
     * Get the string representation of the stack.
     * @return stack debug information
     */
    String Stack::debug() {
        return "[" + toString(offset) + "] " + name;
    }
}
