#pragma once

#include "../../Common.hpp"
#include "Instance.hpp"

namespace Void {
    class Instance;

    /**
     * Represents a registry of the sub-storage types.
     */
    enum class StorageUnit {
        INT,
        FLOAT,
        DOUBLE,
        LONG,
        BOOLEAN,
        INSTANCE
    };

    /**
     * Represents a dynamic-array-based storage that holds element at given indexes.
     */
    template <typename T>
    class SubStorage {
    private:
        /**
         * The array of the held sub-storage elements.
         */
        T* data;

    public:
        /**
         * The capacity of the array.
         */
        uint capacity;

        /**
         * Initialize the sub-storage with an initial capacity.
         * @param capacity initial sub-storage capacity
         */
        SubStorage(uint capacity)
            : data(new T[capacity]), capacity(capacity)
        { }

        /**
         * Initialize the sub-storage without any data.
         */
        SubStorage() : SubStorage(0)
        { }

        /**
         * Set a value of the sub-storage at the given index
         * @param index sub-storage index
         * @param value sub-storage index value
         */
        void set(uint index, T value) {
            // resize the array if it is not big enough for the index
            ensure(index + 1);
            // set the element at the given index
            data[index] = value;
        }

        /**
         * Get the value of the given index.
         * @param index sub-storage index
         * @return sub-storage index value
         */
        T get(uint index) {
            // check if the index is inside the capacity bounds
            if (index < capacity)
                return data[index];
            // handle invalid index
            else
                return {};
        }

        /**
         * Ensure the capacity of the sub-storage. Resize the array to be able
         * to hold newCapacity amount of elements.
         * @param newCapacity number of elements that the array must be able to holds
         */
        void ensure(uint newCapacity) {
            // return if the new capacity is less than the previous one
            if (newCapacity <= capacity)
                return;
            // create a new data of the given size
            T* newData = new T[newCapacity];
            // copy the previous elements to the new array
            memcpy(newData, data, capacity * sizeof(T));
            // update the capacity of the storage
            capacity = newCapacity;
            // delete the previous array
            delete[] data;
            // update the array
            data = newData;
        }
    };

    /**
     * Represents a dynamic-size variable storage, that holds different types of values at their corresponding variable indices.
     */
    class Storage {
    public:
        /**
         * The byte value holder sub-storage.
         */
        SubStorage<byte> bytes;

        /**
         * The byte reference value holder sub-storage.
         */
        SubStorage<Reference<byte>*> byteRefs;

        /**
         * The short value holder sub-storage.
         */
        SubStorage<short> shorts;

        /**
         * The short reference value holder sub-storage.
         */
        SubStorage<Reference<short>*> shortRefs;

        /**
         * The int value holder sub-storage.
         */
        SubStorage<int> ints;

        /**
         * The int reference value holder sub-storage.
         */
        SubStorage<Reference<int>*> intRefs;

        /**
         * The long value holder sub-storage.
         */
        SubStorage<lint> longs;

        /**
         * The long reference value holder sub-storage.
         */
        SubStorage<Reference<lint>*> longRefs;

        /**
         * The float value holder sub-storage.
         */
        SubStorage<float> floats;

        /**
         * The float reference value holder sub-storage.
         */
        SubStorage<Reference<float>*> floatRefs;

        /**
         * The double value holder sub-storage.
         */
        SubStorage<double> doubles;

        /**
         * The double reference value holder sub-storage.
         */
        SubStorage<Reference<double>*> doubleRefs;

        /**
         * The boolean value holder sub-storage.
         */
        SubStorage<bool> booleans;

        /**
         * The boolean reference value holder sub-storage.
         */
        SubStorage<Reference<bool>*> booleanRefs;

        /**
         * The instance reference value holder sub-storage.
         */
        SubStorage<Reference<Instance*>*> instances;

        /**
         * Ensure the capacity of the storage.
         * @param unit sub-storage type
         * @param capacity ensured sub-storage capacity
         */
        void ensure(StorageUnit unit, int capacity);
    };
}