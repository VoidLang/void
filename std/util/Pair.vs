package "util"

/**
 * Represents a holder of two values.
 * This is useful to store two values under the same handle.
 * @since 1.0
 */
public struct Pair<K, V>(
    /**
     * The key element of the pair.
     */
    K key, 

    /**
     * The value element of the pair.
     */
    V value
)
