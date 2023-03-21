#pragma once

#include "../../Common.hpp"

namespace Void {
    class Executable;

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
    class Node {
        /**
         * The data of the node.
         */
        T data{};

        /**
         * The next node of the node.
         */
        Node<T>* next;

        /**
         * Initialize a new node with an initial value.
         * @param data node data
         */
        Node(T data) {
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
        Node<T>* first = NULL;

        /**
         * The last element of the sub-stack.
         */
        Node<T>* last = NULL;

        /**
         * The count of elements in the sun-stack.
         */
        int count;

    public:
        /**
         * Push a value to the end of the sub-stack.
         * @param new sub-stack element
         */
        void push(T value) {
            // create a new node for the value
            Node<T>* newNode = new Node<T>(value);

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
            Node<T>* temp = first;
            if (temp == NULL)
                return {};
            // delete the node of the element
            T value = temp->data;
            Node<T>* next = temp->next;
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
         * Get the size of the sub-stack.
         * @return number of sub-stack elements
         */
        int size() {
            return count;
        }

        /**
         * Clear the held elements of the sub-stack.
         */
        void clear() {
            // recursively loop through the elements of the sub-stack
            Node<T>* node = first;
            while (node != NULL) {
                // get the next node
                Node<T>* next = node->next;
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
