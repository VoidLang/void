#include "Storage.hpp"

namespace Void {
    /**
     * Ensure the capacity of the storage.
     * @param unit sub-storage type
     * @param capacity ensured sub-storage capacity
     */
    void Storage::ensure(StorageUnit unit, int capacity) {
        switch (unit) {
            case StorageUnit::BYTE:
                bytes.ensure(capacity);
                break;
            case StorageUnit::SHORT:
                shorts.ensure(capacity);
                break;
            case StorageUnit::INT:
                ints.ensure(capacity);
                break;
            case StorageUnit::FLOAT:
                floats.ensure(capacity);
                break;
            case StorageUnit::DOUBLE:
                doubles.ensure(capacity);
                break;
            case StorageUnit::LONG:
                longs.ensure(capacity);
                break;
            case StorageUnit::BOOLEAN:
                doubles.ensure(capacity);
                break;
            case StorageUnit::INSTANCE:
                instances.ensure(capacity);
                break;
        }
    }
}