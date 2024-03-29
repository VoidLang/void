#pragma once

#include "../../Common.hpp"
#include "../token/Token.hpp"
#include "Node.hpp"

#include "nodes/MethodNode.hpp"
#include "nodes/FieldNode.hpp"
#include "nodes/FileInfo.hpp"
#include "nodes/TypeNode.hpp"
#include "nodes/LocalNode.hpp"
#include "nodes/ValueNode.hpp"
#include "nodes/ControlFlow.hpp"

#include "../builder/Package.hpp"

namespace Compiler {
    /**
     * The map of the operation's precedences and associativities.
     */
    static TreeMap<UString, Pair<int, int>> OPERATION_INFO = {
        {U"+", {1, 0}},
        {U"-", {1, 0}},
        {U"*", {2, 0}},
        {U"/", {2, 0}},
        {U"%", {2, 0}},
        {U"^", {3, 1}},
        {U".", {4, 0}}
    };

    /**
     * Represents a parser that transforms raw tokens to instructions.
     */
    class NodeParser {
    private:
        /**
         * The target package of the node parser.
         */
        Package* package;

        /**
         * The list of the tokens to be parsed.
         */
        List<Token> tokens;

        /**
         * The index of the currently parsed token.
         */
        uint cursor = 0;

    public:
        /**
         * Initialize the token parser.
         */
        NodeParser(Package* package, List<Token> tokens);

        /**
         * Parse the next instruction node.
         * @return new instruction node
         */
        Node* next();

        /**
         * Get the node at the current index.
         * @return currently parsed token
         */
        Token peek();

        /**
         * Get the node at the current index.
         * Check if the retrieved token does not match the given type.
         * @param type required token type
         * @return currently parsed token
         */
        Token peek(TokenType type);

        /**
         * Get the node at the index.
         * Check if the retrieved token does not match any of the given typs.
         * @param size required token types' length
         * @return currently parsed token
         */
        Token peek(uint size, ...);

        /**
         * Get the token at the current index and move to the next position.
         * @return currently parsed token
         */
        Token get();

        /**
         * Get the token at the current index and move to the next position.
         * Check if the retrieved token does not match the given type.
         * @param type required token type
         * @return currently parsed token
         */
        Token get(TokenType type);

        /**
         * Get the token at the current index and move to the next position.
         * Check if the retrieved token does not match the given type or value.
         * @param type required token type
         * @return currently parsed token
         */
        Token get(TokenType type, UString value);

        /**
         * Get the token at the current index and move to the next position.
         * Check if the retrieved token does not match any of the given types.
         * @param size required token types' length
         * @return currently parsed token
         */
        Token get(uint size, ...);

        /**
         * Move the cursor with the give amount.
         * @param amount cursor move amount
         */
        void skip(uint amount);

        /**
         * Get the token at the given index.
         * @param index token data index
         * @return token at the index or null if not in bounds
         */
        Token at(uint index);

        /**
         * Determine if the given index is in bounds of the data size.
         * @param index target index to check
         * @return true if the index is in bounds
         */
        bool has(uint index);

        /**
         * Parse the next package declaration.
         * @return new declared package
         */
        Node* nextPackage();

        /**
         * Parse the next package import.
         * @return new package import
         */
        Node* nextImport();

        /**
         * Parse the next method node.
         * @return new method node
         */
        Node* nextMethod();

        /**
         * Parse the next field declaration.
         * @return new field node
         */
        Node* nextField();

        /**
         * Parse the next multi-field declaration.
         * @param type multi-field type
         * @param generics type generic token
         * @param name first field's name
         * @param value first field's value
         * @return new multi-field node
         */
        Node* nextMultiField(Token type, List<Token> generics, UString name, Option<Node*> value);

        /**
         * Parse the next type declaration.
         * @return new declared type
         */
        Node* nextTypeDeclaration();

        /**
         * Parse the next class type declaration.
         * @param name type name
         * @param genericNames type generic names
         * @return new declared class
         */
        Node* nextClass(UString name, List<UString> genericNames);

        /**
         * Parse the next struct type declaration.
         * @param name type name
         * @param genericNames type generic names
         * @return new declared struct
         */
        Node* nextStruct(UString name, List<UString> genericNames);

        /**
         * Parse the next tuple struct type declaration.
         * @param name type name
         * @param genericNames type generic names
         * @return new declared tuple struct
         */
        Node* nextTupleStruct(UString name, List<UString> genericNames);

        /**
         * Parse the next class enum type declaration.
         * @param name type name
         * @param genericNames type generic names
         * @return new declared enum
         */
        Node* nextEnum(UString name, List<UString> genericNames);

        /**
         * Parse the next interface type declaration.
         * @param name type name
         * @param genericNames type generic names
         * @return new declared interface
         */
        Node* nextInterface(UString name, List<UString> genericNames);

        /**
         * Parse the next annotation type declaration.
         * @param name type name
         * @param genericNames type generic names
         * @return new declared annotation
         */
        Node* nextAnnotation(UString name, List<UString> genericNames);

        /**
         * Parse the next type or method declaration.
         * @return new declared type or method
         */
        Node* nextTypeOrMethod();

        /**
         * Parse the next content of a type, which might be a type, method or field.
         * @return new declared type, method or field
         */
        Node* nextContent();

        /**
         * Parse the next expression instruction.
         * @return new expression
         */
        Node* nextExpression(bool ignoreJoin);

        /**
         * Parse the next expression instruction.
         * @return new expression
         */
        Node* nextExpression();

        /**
         * Parse the next local variable declaration.
         * @return new local declaration
         */
        Node* nextLocalDeclaration();

        /**
         * Parse the next multi-local-variable declaration.
         * @param type multi-local type
         * @param generics type generic token
         * @param name first local's name
         * @param value first local's value
         * @return new multi-variable declaration
         */
        Node* nextMultiLocalDeclaration(Token type, List<Token> generics, UString name, Option<Node*> value);

        /**
         * Parse the next local variable value assignation.
         * @return new local assignation
         */
        Node* nextLocalAssignation();

        /**
         * Parse the next lambda function declaration.
         * @return new lambda function
         */
        Node* nextLambdaFunction();

        /**
         * Parse the next literal value or method call declaration.
         * @return new literal or method call
         */
        Node* nextLiteralOrMethodCall(bool ignoreJoin);

        /**
         * Parse the next string template declaration.
         * @return new string template 
         */
        Node* nextStringTemplate(bool ignoreJoin);

        /**
         * Parse the next single value operator declaration.
         * @return new single operator
         */
        Node* nextSingleOperator();

        /**
         * Parse the next value return statement declaration.
         * @return new return statement
         */
        Node* nextReturnStatement();

        /**
         * Parse the next instruction deferrer statement declaration.
         * @return new defer statement
         */
        Node* nextDeferStatement();

        /**
         * Parse the next group or tuple declaration.
         * @return new group or tuple
         */
        Node* nextGroupOrTuple(bool ignoreJoin);

        /**
         * Parse the next if statement declaration.
         * @return new if statement
         */
        Node* nextIfStatement();

        /**
         * Parse the next else if statement declaration.
         * @return new else if statement
         */
        Node* nextElseIfStatement();

        /**
         * Parse the next else statement declaration.
         * @return new else statement
         */
        Node* nextElseStatement();

        /**
         * Parse the next while loop statement declaration.
         * @return new while statement
         */
        Node* nextWhileStatement();

        /**
         * Parse the next do-while statement declaration.
         */
        Node* nextDoWhileStatement();

        /**
         * Parse the new statement declaration.
         * @return new "new" statement
         */
        Node* nextNewStatement(bool ignoreJoin);

        /**
         * Parse the next structure initializator declaration.
         * @return new structure initializatior
         */
        Node* nextInitializator();

        /**
         * Parse the next modifier list or block.
         * @return new modifier list or block
         */
        Node* nextModifiers();

        /**
         * Parse the next type specifier declaration.
         * @return new type specifier
         */
        Type nextType();

        /**
         * Parse the next named type specifier declaration
         * @param expectName should a name be parsed for the named type
         * @return new named type specifier
         */
        NamedType nextNamedType(bool expectName);

        /**
         * Parse the next parameter type declaration.
         * @return new parameter type
         */
        ParameterType nextParameterType();

        /**
         * Check if the first operator has a predecende priority over the second operator.
         * @param first first operator to check
         * @param second second operator to check
         * @return true if the first operator has higher precedence than the second one
         */
        bool hasPrecedence(UString first, UString second);

        /**
         * Fix the order of the operation sequences in the parsed value node.
         * @param root root value expression node
         * @return fixed node operations
         */
        Node* fixOperationTree(Node* root);

        /**
         * Parse the next join operation.
         * @param target fisrt node of join operation
         * @return new join operation
         */
        Node* nextJoinOperation(Node* target);

        /**
         * Parse the generic types of a type.
         * @return generic type tokens
         */
        List<Token> parseGenerics();

        /**
         * Parse the generic names of a method or type.
         * @return generic type names
         */
        List<UString> parseGenericNames();

        /**
         * Parse the array declaration of a type.
         * @return array dimensions
         */
        uint parseArray();

        /**
         * Parse the modifiers of the given node type.
         * @param type target node type
         * @return parsed modifier list
         */
        List<UString> parseModifiers(NodeType type);

        /**
         * Parse the next operator target.
         * @return parsed operator
         */
        UString parseOperator();

        /**
         * Test if the given operator is applicable for a left-right use.
         * @return true if the operator expects two values
         */
        bool isComplexOperator(UString target);

        /**
         * Determine if the given operator should be terminated as it is.
         * @param target target operator
         * @return true if the operator parsing should terminate
         */
        bool shouldOperatorTerminate(UString target);

        /**
         * Test if the given operator is applicable before a value.
         * @return true if the operator expects a value on its right
         */
        bool isLeftOperator(UString target);

        /**
         * Test if the given operator is applicable after a value.
         * @return true if the operator expects a value on its left
         */
        bool isRightOperator(UString target);

        /**
         * Test if there are variadic arguments declared.
         * @return true if varargs are declared
         */
        bool testVarargs();

        /**
         * Parse the next condition of a condition block, such as if, else if, while.
         * @return new conditional node
         */
        Node* parseCondition();

        /**
         * Parse the next block of instructions that belong to a block, such as if, else if, while.
         * @return new block statement body
         */
        List<Node*> parseStatementBody();

        /**
         * Parse the next argument list declaration.
         * @return new argument list
         */
        List<Node*> parseArguments();

        /**
         * Parse the next fully qualified name of a type.
         * @return new fully qualified type tokens
         */
        List<Token> parseType();

        /**
         * Parse the next parameter list declaration.
         * @param begin parameter list prefix
         * @param end parameter list suffix
         * @return new parameter list
         */
        void parseParameters(Token begin, Token end, List<Parameter>& parameters, bool& typed);

        /**
         * Parse the next tuple parameter list declaration.
         * @param parameters result of the tuple parameters
         * @param named result that is true if the parameters are named
         */
        void parseTupleParameters(List<TupleParameter>& parameters, bool& named);
    };
}