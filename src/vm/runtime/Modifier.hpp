#pragma once

#include "../../Common.hpp"

#undef INTERFACE

namespace Void {
    /**
     * The registry of the void access modifiers.
     */
    enum class Modifier {
        PUBLIC       = 0x00000001,
        PRIVATE      = 0x00000002,
        PROTECTED    = 0x00000004,
        STATIC       = 0x00000008,
        FINAL        = 0x00000010,
        SYNCHRONIZED = 0x00000020,
        VOLATILE     = 0x00000040,
        TRANSIENT    = 0x00000080,
        NATIVE       = 0x00000100,
        UNSAFE       = 0x00000200,
        ABSTRACT     = 0x00000400,
        INTERFACE    = 0x00000800,
        ANNOTATION   = 0x00001000,
        ENUM         = 0x00002000,
        STRUCT       = 0x00004000,
        WEAK         = 0x00008000,
        TUPLE_STRUCT = 0x00008000,
        WEAK         = 0x00010000,
        STRONG       = 0x00020000,
        DEFAULT      = 0x00040000,
        ASYNC        = 0x00080000
    };

    /**
     * The count of the registered modifiers.
     */
    static const int MODIFIER_COUNT = 19;

    /**
     * The registry of the modifier names.
     */
    static const char* MODIFIER_KEYS[MODIFIER_COUNT] = {
        "public", "private", "protected", "static", "final",  "synchronized",
        "volatile", "transient", "native", "unsafe", "abstract", "interface",
        "annotation",  "enum",   "struct",   "weak",   "strong",   "default",
        "async"
    };

    /**
     * The registry of the modifier values.
     */
    static const int MODIFIER_VALUES[MODIFIER_COUNT] = {
        0x00000001, 0x00000002, 0x00000004, 0x00000008, 0x00000010, 0x00000020,
        0x00000040, 0x00000080, 0x00000100, 0x00000200, 0x00000400, 0x00000800,
        0x00001000, 0x00002000, 0x00004000, 0x00008000, 0x00010000, 0x00020000,
        0x00040000
    };

    /**
     * Get the bitmask of the given modifier.
     * @param modifier certain access modifier
     * @return the bitmask of the modifier
     */
    int maskModifier(String modifier);

    /**
     * Get the bitmask of the given modifiers.
     * @param modifiers access modifiers list
     * @return the bitmask of the modifiers
     */
    int maskModifiers(List<String> modifiers);

    /**
     * Parse the modifiers bitmask to list.
     * @param modifiers access modifiers bitmask
     * @return the names of the modifiers
     */
    List<String> parseModifiers(int modifiers);

    /**
     * Determine if the modifier bitmask has the given modifier included.
     * @param modifiers access modifiers bitmask
     * @param modifier test modifier
     * @return true if the bitmask has the given modifier
     */
    bool hasModifier(int modifiers, Modifier modifier);
}