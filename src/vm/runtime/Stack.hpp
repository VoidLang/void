#pragma once

#include "../../Common.hpp"
#include "Instance.hpp"
#include "Reference.hpp"

namespace Void {
    class Executable;
    class Instance;
    
    template <typename T>
    class Reference;

    /**
     * Represents a registry of the sub-stack types.
     */
    enum class StackUnit {
        INT,
        FLOAT,
        DOUBLE,
        LONG,
        BOOLEAN,
        INSTANCE
    };
    
    /**
     * Represents a value holder element of the sub-stack.
     */
    template <typename T>
    class StackNode {
    public:
        /**
         * The data of the node.
         */
        T data{};

        /**
         * The next node of the node.
         */
        StackNode<T>* next;

        /**
         * Initialize a new node with an initial value.
         * @param data node data
         */
        StackNode(T data) {
            this->data = data;
            this->next = next;
        }
    };

    /**
     * Represents a link-node-based queue sub-stack, that can queue elements in an order.
     */
    template <typename T>
    class SubStack {
    private:
        /**
         * The first element of the sub-stack.
         */
        StackNode<T>* first = NULL;

        /**
         * The last element of the sub-stack.
         */
        StackNode<T>* last = NULL;

        /**
         * The count of elements in the sun-stack.
         */
        uint count;

    public:
        /**
         * Push a value to the end of the sub-stack.
         * @param new sub-stack element
         */
        void push(T value) {
            // create a new node for the value
            StackNode<T>* newNode = new StackNode<T>(value);

            // check if the sub-stack is empty
            if (last == NULL)
                last = newNode;
            // node has already at least element
            // put the new node before it
            else {
                last->next = newNode;
                last = newNode;
            }
            // check if the first element is not set
            if (first == NULL)
                first = last;
            // increment the element count
            count++;
        }

        /**
         * Pull the first element of the sub-stack.
         * @return oldest sub-stack element
         */
        T pull() {
            // check if the sub-stack has no elements
            StackNode<T>* temp = first;
            if (temp == NULL)
                return {};
            // delete the node of the element
            T value = temp->data;
            StackNode<T>* next = temp->next;
            delete temp;
            // check if no elements left
            if (next == NULL) {
                first = NULL;
                last = NULL;
            }
            // shift the elements to one slot left
            else
                first = next;
            // decrement the element count
            count--;
            return value;
        }

        /**
         * Get a value from the sub-stack
         * @param keepStack should the value be kept on the stack
         * @return oldest sub-stack element
         */
        T pull(bool keepStack) {
            return keepStack ? get() : pull();
        }

        /**
         * Get the first element of the sub-stack without removing it.
         * @return oldest sub-stack element
         */
        T get() {
            // check if the sub-stack is empty
            if (first == NULL)
                return {};
            // return the first value of the sub-stack
            return first->data;
        }

        /**
         * Get the sub-stack element at the given index.
         * @param index sub-stack element index
         * @return sub-stack element at the slot
         */
        T at(uint index) {
            // recursively loop through the elements of the sub-stack
            uint currentIndex = 0;
            StackNode<T>* node = first;
            while (node != NULL) {
                // move to the next node
                if (currentIndex++ < index)
                    node = node->next;
                // index matches, return node data
                else
                    return node->data;
            }
            // element not found
            return {};
        }

        /**
         * Get the size of the sub-stack.
         * @return number of sub-stack elements
         */
        uint size() {
            return count;
        }

        /**
         * Clear the held elements of the sub-stack.
         */
        void clear() {
            // recursively loop through the elements of the sub-stack
            StackNode<T>* node = first;
            while (node != NULL) {
                // get the next node
                StackNode<T>* next = node->next;
                // delete the current node
                delete node;
                // continue checking with the next element
                node = next;
            }
            // reset the sub-stack size
            count = 0;
        }
    };

    /**
     * Represents a dynamic-size stack, that holds different types of objects separately.
     */
    class Stack {
    private:
        /**
         * The parent stack in the stack trace.
         */
        Stack* parent;

    public:
        /**
         * The byte value holder sub-stack.
         */
        SubStack<byte> bytes;

        /**
         * The byte reference value holder sub-stack.
         */
        SubStack<Reference<byte>*> byteRefs;

        /**
         * The char value holder sub-stack.
         */
        SubStack<cint> chars;

        /**
         * The char reference value holder sub-stack.
         */
        SubStack<Reference<cint>*> charRefs;

        /**
         * The short value holder sub-stack.
         */
        SubStack<short> shorts;

        /**
         * The short reference value holder sub-stack.
         */
        SubStack<Reference<short>*> shortRefs;

        /**
         * The int value holder sub-stack.
         */
        SubStack<int> ints;

        /**
         * The int reference value holder sub-stack.
         */
        SubStack<Reference<int>*> intRefs;

        /**
         * The long value holder sub-stack.
         */
        SubStack<lint> longs;

        /**
         * The long reference value holder sub-stack.
         */
        SubStack<Reference<lint>*> longRefs;

        /**
         * The float value holder sub-stack.
         */
        SubStack<float> floats;

        /**
         * The float reference value holder sub-stack.
         */
        SubStack<Reference<float>*> floatRefs;

        /**
         * The double value holder sub-stack.
         */
        SubStack<double> doubles;

        /**
         * The double reference value holder sub-stack.
         */
        SubStack<Reference<double>*> doubleRefs;

        /**
         * The boolean value holder sub-stack.
         */
        SubStack<bool> booleans;

        /**
         * The boolean reference value holder sub-stack.
         */
        SubStack<Reference<bool>*> booleanRefs;

        /**
         * The instance reference value holder sub-stack.
         */
        SubStack<Reference<Instance*>*> instances;

        /**
         * The offset of the current stack that determines
         * how far this stack is from the heap.
         */
        int offset;

        /**
         * The executor of this stack.
         */
        Executable* executable;

        /**
         * The name of the stack.
         */
        String name;

        /**
         * Initialize the stack.
         * @param parent parent stack of this stack
         * @param executable stack creator executable
         * @param name stack name
         */
        Stack(Stack* parent, Executable* executable, String name);

        /**
         * Recursively get the current stack trace.
         * @param result stack trace list
         */
        void stackTrace(List<Stack*>& result);

        /**
         * Get the string representation of the stack.
         * @return stack debug information
         */
        String debug();
    };
}
