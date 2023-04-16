#pragma once

#include "../../Common.hpp"
#include "../token/Token.hpp"
#include "../builder/Package.hpp"

namespace Compiler {
    class Package;

    /**
     * Represents a registry of the parseable node types.
     */
    enum class NodeType {
        ModifierList,
        ModifierBlock,
        Method,
        Field,
        MultiField,
        Package,
        Import,
        Class,
        Struct,
        TupleStruct,
        Enum,
        Interface,
        Annotation,
        LocalDeclare,
        MultiLocalDeclare,
        LocalDeclareAssign,
        LocalDeclareDestructure,
        LocalAssign,
        Value,
        New,
        Initializator,
        Operation,
        JoinOperation,
        SideOperation,
        MethodCall,
        Group,
        Template,
        Lambda,
        IndexFetch,
        IndexAssign,
        Return,
        Defer,
        Tuple,
        If,
        ElseIf,
        Else,
        While,
        DoWhile,
        For,
        ForEach,
        Error,
        Finish
    };

    OutputStream& operator<<(OutputStream& stream, NodeType& type);

    /**
     * Represents an instruction node that is parsed from raw tokens.
     * A node can be an exact instruction or a holder of multiple instructions.
     * The node hierarchy is then transformed to executable bytecode.
     */
    class Node {
    public:
        /**
         * The type of the node.
         */
        NodeType type;

        /**
         * The target package of the node.
         */
        Package* package;

        /**
         * Initialize the node.
         * @param type node type
         * @param package node parent
         */
        Node(NodeType type, Package* package);

        /**
         * Debug the content of the parsed node.
         */
        virtual void debug(uint& index);

        /**
         * Build bytecode for this node.
         * @param bytecode result bytecode list
         */
        virtual void build(List<UString>& bytecode);
    
        /**
         * Determine if this node has the given type.
         * @param type target type to check
         * @return true if the type matches this node
         */
        bool is(NodeType type);
    };
    
    /**
     * Represewnts a node that holds the information of a compiling error 
     * that occurred whilst parsing tokens to nodes.
     */
    class ErrorNode : public Node {
    public:
        /**
         * Initialize the error node.
         */
        ErrorNode();

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    /**
     * Represents a node that indicates that the parsing of the file has been ended.
     */
    class FinishNode : public Node {
    public:
        /**
         * Initialize the finish node.
         */
        FinishNode();

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class Modifiable : public Node {
    public:
        List<UString> modifiers; // to be initialized later

        Modifiable(NodeType type, Package* package);
    };

    // 
    // TypeNode
    //

    class ModifierList : public Node {
    public:
        List<UString> modifiers;

        ModifierList(Package* package, List<UString> modifiers);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class ModifierBlock : public Node {
    public:
        List<UString> modifiers;

        ModifierBlock(Package* package, List<UString> modifiers);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class TypeNode : public Modifiable {
    public:
        UString name;

        List<UString> genericNames;

        TypeNode* parent = nullptr;

        TypeNode(NodeType type, Package* package, UString name, List<UString> genericNames);

        /**
         * Get the fully qualified name of the type.
         * @return type name with package and parent
         */
        UString getFullName();
    };

    class Class : public TypeNode {
    public:
        List<Node*> body;

        Class(Package* package, UString name, List<UString> genericNames, List<Node*> body);

        /**
         * Build bytecode for this node.
         * @param bytecode result bytecode list
         */
        void build(List<UString>& bytecode) override;
    };

    class NormalStruct : public TypeNode {
    public:
        List<Node*> body;

        NormalStruct(Package* package, UString name, List<UString> genericNames, List<Node*> body);
    };

    class TupleParameter {
    public:
        Token type;

        List<Token> generics;

        int dimensions;

        UString name;

        TupleParameter(Token type, List<Token> generics, int dimensions, UString name);
    };

    class TupleStruct : public TypeNode {
    public:
        bool named;

        List<TupleParameter> parameters;

        TupleStruct(Package* package, UString name, List<UString> genericNames, bool named, List<TupleParameter> parameters);
    };

    class Enum : public Node {

    };

    class Interface : public Node {

    };

    class Annotation : public Node {

    };

    // 
    // ControlFlow
    // 

    class Return : public Node {
    public:
        Option<Node*> value;

        Return(Package* package, Node* value);

        Return(Package* package);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class Defer : public Node {
    public:
        Node* instruction;

        Defer(Package* package, Node* instruction);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class ElseIf : public Node {
    public:
        Node* condition;

        List<Node*> body;

        ElseIf(Package* package, Node* condition, List<Node*> body);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class Else : public Node {
    public:
        List<Node*> body;

        Else(Package* package, List<Node*> body);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class If : public Node {
    public:
        Node* condition;

        List<Node*> body;

        List<ElseIf*> elseIfs;

        Else* elseCase;

        If(Package* package, Node* condition, List<Node*> body);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class While : public Node {
    public:
        Node* condition;

        List<Node*> body;

        While(Package* package, Node* condition, List<Node*> body);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class DoWhile : public Node {
    public:
        List<Node*> body;

        Node* condition;

        DoWhile(Package* package, List<Node*> body, Node* condition);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    //
    // FieldNode
    //

    class FieldNode : public Modifiable {
    public:
        Token type;

        List<Token> generics;

        UString name;

        Option<Node*> value;

        FieldNode(Package* package, Token type, List<Token> generics, UString name, Option<Node*> value);
    };

    class MultiField : public Modifiable {
    public:
        Token type;

        List<Token> generics;

        TreeMap<UString, Option<Node*>> fields;

        MultiField(Package* package, Token type, List<Token> generics, TreeMap<UString, Option<Node*>> fields);
    };

    //
    // FileInfo
    //

    class PackageSet : public Node {
    public:
        UString name;

        PackageSet(Package* package, UString name);
    };

    class Import : public Node {
    public:
        UString target;

        Import(Package* package, UString target);
    };

    // 
    // LocalNode
    //

    class LocalDeclare : public Modifiable {
    public:
        Token type;

        List<Token> generics;

        UString name;

        LocalDeclare(Package* package, Token type, List<Token> generics, UString name);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class MultiLocalDeclare : public Modifiable {
    public:
        Token type;

        List<Token> generics;

        TreeMap<UString, Option<Node*>> locals;

        MultiLocalDeclare(Package* package, Token type, List<Token> generics, TreeMap<UString, Option<Node*>> locals);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class LocalDeclareAssign : public Modifiable {
    public:
        Token type;

        List<Token> generics;

        UString name;

        Node* value;

        LocalDeclareAssign(Package* package, Token type, List<Token> generics, UString name, Node* value);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class LocalDeclareDestructure : public Node {
    public:
        List<UString> members;

        Node* value;

        LocalDeclareDestructure(Package* package, List<UString> members, Node* value);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class LocalAssign : public Node {
    public:
        UString name;

        Node* value;

        LocalAssign(Package* package, UString name, Node* value);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    //
    // MethodNode
    //

    class Parameter {
    public:
        Token type;

        List<Token> generics;

        bool varargs;

        UString name;

        Parameter(Token type, List<Token> generics, bool varargs, UString name);
    };

    class Type {
    public:
        List<Token> types;

        List<Token> generics;

        uint dimensions;

        Type(List<Token> types, List<Token> generics, uint dimensions);
    };

    class NamedType : public Type {
    public:
        bool named;

        UString name;

        NamedType(List<Token> types, List<Token> generics, uint dimensions, bool named, UString name);

        NamedType(Type type, bool named, UString name);
    };

    class ParameterType : public Type {
    public:
        bool variadic;

        UString name;

        ParameterType(List<Token> types, List<Token> generics, uint dimensions, bool variadic, UString name);

        ParameterType(Type type, bool variadic, UString name);
    };

    class MethodNode : public Modifiable {
    public:
        List<NamedType> returnTypes;

        UString name;

        List<Parameter> parameters;

        List<Node*> body;

        UString package = U"";

        TypeNode* parent = nullptr;

        MethodNode(Package* package, List<NamedType> returnTypes, UString name, List<Parameter> parameters, List<Node*> body);

        /**
         * Build bytecode for this node.
         * @param bytecode result bytecode list
         */
        void build(List<UString>& bytecode) override;

    private:
        /**
         * Parse the return type of the method.
         */
        UString parseReturnType();
    };

    class MethodCall : public Node {
    public:
        UString name;

        List<Node*> arguments;

        MethodCall(Package* package, UString name, List<Node*> arguments);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class Lambda : public Node {
    public:
        bool typed;

        List<Parameter> parameters;

        List<Node*> body;

        Lambda(Package* package, bool typed, List<Parameter> parameters, List<Node*> body);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    //
    // ValueNode
    //

    /**
     * Represents a node that holds a single value.
     */
    class Value : public Node {
    public:
        /**
         * The held value of the node.
         */
        Token value;

        /**
         * Initialize the single value node.
         * @param value node value
         */
        Value(Package* package, Token value);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;

        /**
         * Build bytecode for this node.
         * @param bytecode result bytecode list
         */
        void build(List<UString>& bytecode) override;
    };

    /**
     * Represents an instruction that performs an operation on two expressions.
     */
    class Operation : public Node {
    public:
        /**
         * The first expression of the operation.
         */
        Node* left;

        /**
         * The target operator of the operation.
         */
        UString target;

        /**
         * The second expression of the operation.
         */
        Node* right;

        /**
         * Initialize the operation.
         * @param left first expression
         * @param target target operator
         * @param right second expression
         */
        Operation(Package* package, Node* left, UString target, Node* right);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;

        /**
         * Build bytecode for this node.
         * @param bytecode result bytecode list
         */
        void build(List<UString>& bytecode) override;
    };

    class JoinOperation : public Node {
    public:
        /**
         * The target expression of the operation.
         */
        Node* target;

        /**
         * The child expressions of the operation.
         */
        List<Node*> children;

        /**
         * Ubutuakuze the join operation.
         * @param target first expression
         * @param children operatorands
         */
        JoinOperation(Package* package, Node* left, List<Node*> right);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class SideOperation : public Node {
    public:
        UString target;

        Node* operand;

        bool left;

        SideOperation(Package* package, UString target, Node* operand, bool left);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class Group : public Node {
    public:
        Node* value;

        Group(Package* package, Node* value);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;

        /**
         * Build bytecode for this node.
         * @param bytecode result bytecode list
         */
        void build(List<UString>& bytecode) override;
    };

    class Template : public Node {
    public:
        Token value;

        Template(Package* package, Token value);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class IndexFetch : public Node {
    public:
        UString name;

        Node* index;

        IndexFetch(Package* package, UString name, Node* index);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class IndexAssign : public Node {
    public:
        UString name;

        Node* index;

        Node* value;

        IndexAssign(Package* package, UString name, Node* index, Node* value);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class Tuple : public Node {
    public:
        List<Node*> members;

        Tuple(Package* package, List<Node*> members);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    enum ConstructType {
        Default, //  new Foo()
        Struct,  // new Bar { x: true, y: 2 }
        Abstract //  new Baz() { @Override void foo() { } }
    };

    class Initializator : public Node {
    public:
        TreeMap<UString, Node*> members;

        Initializator(Package* package, TreeMap<UString, Node*> members);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };

    class NewNode : public Node {
    public:
        UString name;

        ConstructType type;

        List<Node*> arguments;

        Node* initializator;

        NewNode(Package* package, UString name, ConstructType type, List<Node*> arguments, Node* initializator);

        /**
         * Debug the content of the parsed node.
         */
        void debug(uint& index) override;
    };
}
