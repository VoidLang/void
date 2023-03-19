#pragma once

namespace Void {
    /**
     * Represents a smart pointer which allows us to keep track of the data inside, as well as the inner pointer.
     */
    template <typename T>
    class Reference {
    public:
        /**
         * The held data of the pointer.
         */
        T data;

        /**
         * Determine if the pointer exists.
         */
        bool exists = true;

        /**
         * Determine if the data should be deleted instantly after going out of scope.
         */
        bool weak = false;

        /**
         * Determine if the data should be kept in memory even if it is no longer used.
         */
        bool strong = false;

        /**
         * Initialize the pointer with a default value and reference flags.
         * @param data initial pointer data
         * @param weak should data be delete data instantly after goind out of scope
         * @param strong should data be kept in memory even if it is no longer used 
         */
        Reference(T data, bool weak, bool strong)
            : data(data), weak(weak), strong(strong)
        { }

        /**
         * Initialize the pointer with a default value.
         * @param data initial pointer data
         */
        Reference(T data) 
            : data(data)
        { }

        /**
         * Initialize a pointer without any data given.
         */
        Reference() 
            : exists(false)
        { }

        /**
         * Delete the data and mark it as deleted.
         */
        void purge() {
            delete data;
            exists = false;
        }

        /**
         * Update the value of the reference.
         * @param newData new data of the pointer
         * @param deletePrev should the previous data be deleted
         */
        void set(T newData, bool deletePrev) {
            if (deletePrev)
                purge();
            data = newData;
            exists = true;
        }

        /**
         * Check if the held data is instance of the given type.
         * @return true if T instanceof data
         */
        template <typename T>
        bool isInstance() {
            return dynamic_cast<T*>(data) != nullptr;
        }
    };
}