#include "Modifier.hpp"

namespace Void {
    /**
     * Get the bitmask of the given modifier.
     * @param modifier certain access modifier
     * @return the bitmask of the modifier
     */
    int maskModifier(String modifier) {
        // loop through the registered modifiers
        for (ulong i = 0; i < MODIFIER_COUNT; i++) {
            // check if the modifier name matches the given name
            if (MODIFIER_KEYS[i] == modifier)
                return MODIFIER_VALUES[i];
        }
        return 0;
    }

    /**
     * Get the bitmask of the given modifiers.
     * @param modifiers access modifiers list
     * @return the bitmask of the modifiers
     */
    int maskModifiers(List<String> modifiers) {
        int flag = 0;
        for (String modifier : modifiers)
            flag |= maskModifier(modifier);
        return flag;
    }

    /**
     * Parse the modifiers bitmask to list.
     * @param modifiers access modifiers bitmask
     * @return the names of the modifiers
     */
    List<String> parseModifiers(int modifiers) {
        List<String> result;
        // check each modifier if it is in the bitmask
        for (ulong i = 0; i < MODIFIER_COUNT; i++) {
            // check the current modifier
            if ((modifiers & MODIFIER_VALUES[i]) > 0)
                // get the name of the modifier value
                result.push_back(MODIFIER_KEYS[i]);
        }
        return result;
    }

    /**
     * Determine if the modifier bitmask has the given modifier included.
     * @param modifiers access modifiers bitmask
     * @param modifier test modifier
     * @return true if the bitmask has the given modifier
     */
    bool hasModifier(int modifiers, Modifier modifier) {
        // get the flag of the modifier
        int flag = static_cast<UnderlyingType<Modifier>::type>(modifier);
        // test if the methods modifiers mask has the flag
        return (modifiers & flag) > 0;
    }
}