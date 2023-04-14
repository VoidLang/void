#include "NodeBuilder.hpp"

namespace Compiler {
    /**
     * Initialize the node builder.
     * @param nodes raw nodes input
     */
    NodeBuilder::NodeBuilder(List<Node*> nodes)
        : nodes(nodes)
    { }

    /**
     * Build the program from raw parsed tokens.
     */
    void NodeBuilder::build() {
        ModifierList* modifiers = nullptr;
        while (has(cursor)) {
            // set the modifiers of the following object
            if (modifiers != nullptr) {
                // check if the following element is non-modifiable 
                if (!instanceof(peek(), Modifiable))
                    error("Trying to set the modifiers of a non-modifiable node: " << peek()->type);
                // set the modifiers of the node
                as(peek(), Modifiable)->modifiers = modifiers->modifiers;
                modifiers = nullptr;
            }

            // handle package declaration
            if (peek()->is(NodeType::Package))
                nextPackage();
            // handle package method declaration
            else if (peek()->is(NodeType::Method))
                nextPackageMethod();
            // handle package class declaration
            else if (peek()->is(NodeType::Class))
                nextPackageClass();
            // handle package struct declaration
            else if (peek()->is(NodeType::Struct))
                nextPackageStruct();
            // handle package tuple struct declaration
            else if (peek()->is(NodeType::TupleStruct))
                nextPackageTupleStruct();
            // handle modifier list declaration
            else if (peek()->is(NodeType::ModifierList))
                modifiers = as(get(), ModifierList);
            // handle unexpected node
            else 
                error("Unexpected node: " << peek()->type);
        }
    }

    /**
     * Handle the next package declaration.
     */
    void NodeBuilder::nextPackage() {
        Package* package = as(get(), Package);
        UString name = package->name;
        checkTypeNameAvailable(name);
        this->package = name;
    }

    /**
     * Handle the next package method declaration.
     */
    void NodeBuilder::nextPackageMethod() {
        MethodNode* method = as(get(), MethodNode);
        checkMethodAvailable(method->name, method->parameters);
        methods.push_back(method);
    }

    /**
     * Handle the next package class declaration.
     */
    void NodeBuilder::nextPackageClass() {
        Class* classNode = as(get(), Class);
        UString name = classNode->name;
        checkTypeNameAvailable(name);
        classes[name] = classNode;
    }

    /**
     * Handle the next package struct declaration.
     */
    void NodeBuilder::nextPackageStruct() {
        NormalStruct* normalStruct = as(get(), NormalStruct);
        UString name = normalStruct->name;
        checkTypeNameAvailable(name);
        structs[name] = normalStruct;
    }

    /**
     * Handle the next pacakge tuple struct declaration.
     */
    void NodeBuilder::nextPackageTupleStruct() {
        TupleStruct* tupleStruct = as(get(), TupleStruct);
        UString name = tupleStruct->name;
        checkTypeNameAvailable(name);
        tupleStructs[name] = tupleStruct;
    }

    /**
     * Check if the given name is already used by a type in the package.
     * @param name type name to check
     */
    void NodeBuilder::checkTypeNameAvailable(UString name) {
        if (getType(name) != nullptr)
            error("Type name '" << name << "' is already declared in this package.");
    }

    /**
     * Check if the given method signature is already used by a method in the package.
     * @param name method name to check
     * @param parameters method parameters to check
     */
    void NodeBuilder::checkMethodAvailable(UString name, List<Parameter> parameters) {
        if (getMethod(name, parameters) != nullptr) {
            print("Method " << name << "(");
            for (uint i = 0; i < parameters.size(); i++) {
                print(parameters[i].type.value);
                if (i < parameters.size() - 1)
                    print(", ");
            }
            error(") is already declared in this package.");
        }
    }

    /**
     * Get a type from the package by its name.
     * @param name target type name
     * @return found type or nullptr if not found
     */
    TypeNode* NodeBuilder::getType(UString name) {
        // check if a package class uses the given name
        for (auto& [_, classNode] : classes) {
            if (classNode->name == name)
                return classNode;
        }

        // check if a package struct uses the given name
        for (auto& [_, structNode] : structs) {
            if (structNode->name == name)
                return structNode;
        }

        // check if a package tuple struct uses the given name
        for (auto& [_, tupleStruct] : tupleStructs) {
            if (tupleStruct->name == name)
                return tupleStruct;
        }

        // package type not found, return null type pointer
        return nullptr;
    }

    /**
     * Get a method from the package by its signature.
     * @param name target method name
     * @param parameters target method parameters
     * @return found method or nullptr if not found
     */
    MethodNode* NodeBuilder::getMethod(UString name, List<Parameter> parameters) {
        // get the length of the required parameters list
        ulong checkLength = parameters.size();
        // loop through the declared package methods
        for (MethodNode* method : methods) {
            // get the length of the method's parameter list
            ulong methodLength = method->parameters.size();
            // ignore the method if the method name or parameters length does not match
            if (method->name != name || methodLength != checkLength)
                continue;
            // check if the method parameters match
            for (ulong i = 0; i < checkLength; i++) {
                // ignore method if the parameter at the 
                // current index does not match
                if (method->parameters[i].type.value != parameters[i].type.value)
                    goto search;
            }
            // method parameters matches, method found
            return method;
        search:;
        }
        // method not found, return a null method pointer
        return nullptr;
    }

    /**
     * Get the node at the current index.
     * @return currently parsed token
     */
    Node* NodeBuilder::peek() {
        return at(cursor);
    }

    /**
     * Get the node at the current index.
     * Check if the retrieved token does not match the given type.
     * @param type required token type
     * @return currently parsed token
     */
    Node* NodeBuilder::peek(NodeType type) {
        // get the current node
        Node* node = peek();
        // check if the current node does not match the required type
        if (!node->is(type))
            error("Invalid node. Expected " << type << ", but got " << node->type);
        return node;
    }

    /**
     * Get the node at the current index.
     * Check if the retrieved token does not match any of the given typs.
     * @param size required token types' length
     * @return currently parsed token
     */
    Node* NodeBuilder::peek(uint size, ...) {
        // declare the list of the dynamic arguments
        List<NodeType> types;

        // begin the processing of the varargs
        va_list list;
        va_start(list, size);

        // handle vararg parameters
        for (uint i = 0; i < size; i++)
            types.push_back(va_arg(list, NodeType));

        // end varargs processing
        va_end(list);

        // get the current node
        Node* node = peek();

        // check if the current node does not match any of the required types
        for (NodeType type : types) {
            if (node->is(type))
                return node;
        }
        // node does not match any of the types
        print("Invalid node. Expected ");

        // print the expected node types
        if (size == 1) {
            print(types[0]);
            goto end;
        }
        for (uint i = 0; i < size - 1; i++)
            print(types[i] << ", ");

        print("or " << types.back());

    end:
        println(", but got " << node->type);

        exit(-1);
        return new ErrorNode();
    }

    /**
     * Get the node at the current index and move to the next position.
     * @return currently parsed node
     */
    Node* NodeBuilder::get() {
        return at(cursor++);
    }

    /**
     * Get the node at the current index and move to the next position.
     * Check if the retrieved node does not match the given type.
     * @param type required node type
     * @return currently parsed node
     */
    Node* NodeBuilder::get(NodeType type) {
        // get the current node and move the cursor
        Node* node = get();
        // check if the current node does not match the required type
        if (!node->is(type))
            error("Invalid node. Expected " << type << ", but got " << node->type);
        return node;
    }

    /**
     * Get the node at the current index and move to the next position.
     * Check if the retrieved node does not match any of the given types.
     * @param size required node types' length
     * @return currently parsed node
     */
    Node* NodeBuilder::get(uint size, ...) {
        // declare the list of the dynamic arguments
        List<NodeType> types;

        // begin the processing of the varargs
        va_list list;
        va_start(list, size);

        // handle vararg parameters
        for (uint i = 0; i < size; i++)
            types.push_back(va_arg(list, NodeType));

        // end varargs processing
        va_end(list);

        // get the current node and move the cursor
        Node* node = get();

        // check if the current node does not match any of the required types
        for (NodeType type : types) {
            if (node->is(type))
                return node;
        }
        // node does not match any of the types
        print("Invalid node. Expected ");

        // print the expected node types
        if (size == 1) {
            print(types[0]);
            goto end;
        }
        for (uint i = 0; i < size - 1; i++)
            print(types[i] << ", ");

        print("or " << types.back());

    end:
        println(", but got " << node->type);

        exit(-1);
        return new ErrorNode();
    }

    /**
     * Move the cursor with the give amount.
     * @param amount cursor move amount
     */
    void NodeBuilder::skip(uint amount) {
        cursor += amount;
    }

    /**
     * Get the node at the given index.
     * @param index node data index
     * @return node at the index or null if not in bounds
     */
    Node* NodeBuilder::at(uint index) {
        return has(index) ? nodes[index] : new ErrorNode();
    }

    /**
     * Determine if the given index is in bounds of the data size.
     * @param index target index to check
     * @return true if the index is in bounds
     */
    bool NodeBuilder::has(uint index) {
        return index >= 0 && index < nodes.size();
    }
}