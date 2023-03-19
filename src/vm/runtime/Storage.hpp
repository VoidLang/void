#pragma once

#include "../../Common.hpp"

namespace Void {
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
        /**
         * The array of the held sub-storage elements.
         */
        T* data;

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
        /**
         * Ensure the capacity of the storage.
         * @param unit sub-storage type
         * @param capacity ensured sub-storage capacity
         */
        void ensure(StorageUnit unit, int capacity);
    };
}