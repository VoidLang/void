#include "NodeParser.hpp"
#include "../../util/Strings.hpp"

using namespace Void;

namespace Compiler {
    /**
     * Initialize the token parser.
     */
    NodeParser::NodeParser(List<Token> tokens)
        : tokens(tokens)
    { }

    /**
     * Parse the next instruction node.
     * @return new instruction node
     */
    Node* NodeParser::next() {
        // handle content ending
        if (peek().is(TokenType::Finish))
            return new FinishNode();
        // handle package declaration
        else if (peek().is(TokenType::Info, U"package")) 
            return nextPackage();
        // handle package import
        else if (peek().is(TokenType::Info, U"import")) 
            return nextImport();
        // handle method or type declaration
        else if (peek().is(5, TokenType::Type, TokenType::Identifier, TokenType::Open, TokenType::Modifier, TokenType::Expression))
            return nextTypeOrMethod();
        // handle unexpected token
        Token error = peek();
        println("Error (Next) " << error);
        return new ErrorNode();
    }

    /**
     * Get the current at the index.
     * @return currently parsed token
     */
    Token NodeParser::peek() {
        return at(cursor);
    }

    /**
     * Get the current at the index.
     * Check if the retrieved token does not match the given type.
     * @param type required token type
     * @return currently parsed token
     */
    Token NodeParser::peek(TokenType type) {
        // get the current token
        Token token = peek();
        // check if the current token does not match the required type
        if (!token.is(type))
            error("Invalid token. Expected " << type << ", but got " << token);
        return token;
    }

    /**
     * Get the current at the index.
     * Check if the retrieved token does not match any of the given typs.
     * @param length of required token types
     * @return currently parsed token
     */
    Token NodeParser::peek(uint size, ...) {
        // declare the list of the dynamic arguments
        List<TokenType> types;

        // begin the processing of the varargs
        va_list list;
        va_start(list, size);

        // handle vararg parameters
        for (uint i = 0; i < size; i++)
            types.push_back(va_arg(list, TokenType));

        // end varargs processing
        va_end(list);

        // get the current token
        Token token = peek();

        // check if the current token does not match any of the required types
        for (TokenType type : types) {
            if (token.is(type))
                return token;
        }
        // token does not match any of the types
        print("Invalid token. Expected ");

        // print the expected token types
        if (size == 1) {
            print(types[0]);
            goto end;
        }
        for (uint i = 0; i < size - 1; i++)
            print(types[i] << ", ");

        print("or " << types.back());

    end:
        println(", but got " << token);

        exit(-1);
        return Token::of(TokenType::None);
    }

    /**
     * Get the token at the current index and move to the next position.
     * @return currently parsed token
     */
    Token NodeParser::get() {
        return at(cursor++);
    }

    /**
     * Get the token at the current index and move to the next position.
     * Check if the retrieved token does not match the given type.
     * @param type required token type
     * @return currently parsed token
     */
    Token NodeParser::get(TokenType type) {
        // get the current token and move the cursor
        Token token = get();
        // check if the current token does not match the required type
        if (!token.is(type))
            error("Invalid token. Expected " << type << ", but got " << token);
        return token;
    }

    /**
     * Get the token at the current index and move to the next position.
     * Check if the retrieved token does not match the given type or value.
     * @param type required token type
     * @return currently parsed token
     */
    Token NodeParser::get(TokenType type, UString value) {
        // get the current token and move the cursor
        Token token = get();
        // check if the current token does not match the required type
        if (!token.is(type) || !token.val(value))
            error("Invalid token. Expected " << type << "|" << Strings::fromUTF(value) << "|" << ", but got " << token);
        return token;
    }

    /**
     * Get the token at the current index and move to the next position.
     * Check if the retrieved token does not match any of the given types.
     * @param type required token type
     * @return currently parsed token
     */
    Token NodeParser::get(uint size, ...) {
        // declare the list of the dynamic arguments
        List<TokenType> types;

        // begin the processing of the varargs
        va_list list;
        va_start(list, size);

        // handle vararg parameters
        for (uint i = 0; i < size; i++)
            types.push_back(va_arg(list, TokenType));

        // end varargs processing
        va_end(list);

        // get the current token and move the cursor
        Token token = get();
        
        // check if the current token does not match any of the required types
        for (TokenType type : types) {
            if (token.is(type))
                return token;
        }
        // token does not match any of the types
        print("Invalid token. Expected ");
       
        // print the expected token types
        if (size == 1) {
            print(types[0]);
            goto end;
        }
        for (uint i = 0; i < size - 1; i++) 
            print(types[i] << ", ");
        
        print("or " << types.back());

    end:
        println(", but got " << token);
        
        exit(-1);
        return Token::of(TokenType::None);
    }

    /**
     * Move the cursor with the give amount.
     * @param amount cursor move amount
     */
    void NodeParser::skip(uint amount) {
        cursor += amount;
    }

    /**
     * Get the token at the given index.
     * @param index token data index
     * @return otken at the index or null if not in bounds
     */
    Token NodeParser::at(uint index) {
        return has(index) ? tokens[index] : Token::of(TokenType::Finish);
    }

    /**
     * Determine if the given index is in bounds of the data size.
     * @param index target index to check
     * @return true if hte index is in bounds
     */
    bool NodeParser::has(uint index) {
        return index >= 0 && index < tokens.size();
    }

    /**
     * Parse the next method node.
     * @return new method node
     */
    Node* NodeParser::nextMethod() {
        // handle method modifiers
        List<UString> modifiers = parseModifiers(NodeType::Method);

        // handle method multi-return types
        // this syntax looks something like this:
        // (int, String) fetchURL(String url)
        // ^           ^  multi-return types are placed in between parenthesis
        // (bool code, String message) authenticate(String username, String password)
        //       ^^^^         ^^^^^^^ you can even name these return types 
        List<ReturnType> returnTypes;
        if (peek().is(TokenType::Open)) {
        parseReturnType:
            get();
            // get the type of the return type
            Token type = get(2, TokenType::Type, TokenType::Identifier);
            // generic types are declared after the type specifier
            // List<User> getAllUsers()
            //     ^    ^ generic types are put in between angle brackets
            // you may have nested, or multiple generic types as well
            // Map<UUID, Player> getPlayer(UUID uuid)
            //         ^ types are separated by a comma
            // List<Set<Float>> 
            //     ^   ^     ^^ this list holds multiple sets of floats
            List<Token> typeGenerics = parseGenerics();
            
            // check if the type has a name
            Option<UString> name;
            if (peek().is(TokenType::Identifier)) 
                name = get().value;

            // register the return type
            returnTypes.push_back(ReturnType(type, typeGenerics, name));

            // handle more arguments
            // Map<String, MoreTokens> doSomething() 
            //           ^ comma indicates, that there are more generic types
            if (peek(2, TokenType::Comma, TokenType::Close).is(TokenType::Comma))
                goto parseReturnType;
            
            // handle multi-return exit
            // (int, int) getTwoNumbers()
            //          ^ closing parenthesis indicates, that the multi-return types' declaration has ended
            else if (peek().is(TokenType::Close)) {
                get();
                goto exitReturnTypes;
            }
        }

        // handle simple return-type
        // for example:
        // int getUserBalance(String user)
        // ^^^ the method has only one return type, "int"
        else {
            // get the type of the method
            Token type = get(2, TokenType::Type, TokenType::Identifier);

            // simple return-types may have generics as well
            // List<Order> getRecentOrders()
            //     ^^^^^^^ these are also placed after the type token
            List<Token> typeGenerics = parseGenerics();

            // register the return type without name
            returnTypes.push_back(ReturnType(type, typeGenerics, {}));
        }

        exitReturnTypes:
        
        // get the name of the method
        // void greet(String person) { println($"Hi, {person}") }
        //      ^^^^^ the identifier after the type token(s) indicate the name of hte method
        UString name = get(TokenType::Identifier).value;

        // handle method generic types
        // method generic type declaration look somewhat different from type generic declaration
        // in here we only define what identifiers we are willing to use as generic types inside the method
        // void concat<T>(List<T> firstList, List<T> secondList)
        //            ^^^ method generics are placed after the method name
        // void createMap<K,V>()
        //                 ^ you may have multiple method generic types
        //                   they are also separated with a comma
        List<UString> genericTypes;
        if (peek().is(TokenType::Operator, U"<")) {
        parseGeneric:
            // skip the '<' or ',' symbol
            // void foo<Bar,Baz>()
            //         ^   ^ we don't care about these two characters, as they are already handled
            get();

            // get the name of the generic 
            // void myMethod<MyGeneric>()
            //               ^^^^^^^^^ the identifier (name) of the method generic type 
            UString genericName = get(TokenType::Identifier).value;
            genericTypes.push_back(genericName);

            // check if there are more generic types
            // U transform<T,U>(T source)
            //              ^ comma indicates, that there are more method generic types
            if (peek().is(TokenType::Comma))
                goto parseGeneric;

            // handle method generic types end
            // T getValue<T>(String key)
            //              ^ close angle bracket indicates, that the declaration of the method generic types has ended
            get(TokenType::Operator, U">");
        }

        // handle method parameter list
        // int multiply(int a, int b)
        //             ^ open parenthesis indicates, that the declaration of the parameter list has begun
        // skip the '(' symbol as it is already handled
        get(TokenType::Open);

        List<Parameter> parameters;

        // check if the method has no parameters
        // void myMethodWithNoParameters()
        //                              ^^ open parenthesis are directly followed by close parenthesis
        if (peek().is(TokenType::Close)) {
            get();
            goto noParams;
        }
        
        parseParam: {
            // get the type of the parameter
            // void foo(int i)
            //          ^^^ this indicates the type of the parameter
            Token paramType = get(2, TokenType::Identifier, TokenType::Type);
            // handle type generic arguments
            // void takeOrders(List<Order> orders)
            //                     ^ just like before, generic types are placed in between angle brackets
            List<Token> paramGenerics = parseGenerics();

            // handle method array type
            // int[] getPositionXYZ()
            //    ^^ square brackets after the type indicates that they are arrays
            int dimensions = parseArray();

            // handle variadic method
            // List<T> fromElements<T>(T... elements)
            //                          ^^^ the spread operator indicates, that the type is variadic
            bool varargs = false;
            if (peek().is(TokenType::Operator, U".")) {
                // skip the remaining three dots
                get();
                get(TokenType::Operator, U".");
                get(TokenType::Operator, U".");
                varargs = true;
            }
            
            // get the name of the parameter
            // void foo(int test)   void bar(List<Float> myList)
            //              ^^^^                         ^^^^^^ the name of the kust
            UString paramName = get(TokenType::Identifier).value;

            // register the method parameter
            parameters.push_back(Parameter(paramType, paramGenerics, varargs, paramName));

            // handle more parameters
            // int subtract(int a, int b)
            //                   ^ the comma indicates, that there are more parameters to be parsed
            // void myMethod(int myParam)
            //                          ^ the closing parenthesis incidate, that the declaration of the parameter list has ended
            Token token = get(2, TokenType::Comma, TokenType::Close);
            if (token.is(TokenType::Comma))
                goto parseParam;
        }

        // handle method without any parameters
    noParams:

        // handle method body begin
        get(TokenType::Begin);

        // parse the body of the method
        List<Node*> body;
        while (!peek().is(TokenType::End)) {
            body.push_back(nextExpression());
        }

        // handle method body end
        get(TokenType::End);
        
        // skip the auto-inserted semicolon
        if (peek().is(TokenType::Semicolon))
            get();

        if (!modifiers.empty())
            print(Strings::join(modifiers, U" ") << " ");

        if (returnTypes.size() > 1)
            print("(");
        for (uint i = 0; i < returnTypes.size(); i++) {
            ReturnType type = returnTypes[i];
            print(type.type.value);
            if (!type.generics.empty()) {
                print("<");
                for (uint j = 0; j < type.generics.size(); j++) {
                    print(type.generics[j].value);
                }
                print(">");
            }
            if (type.name.has_value())
                print(" " << *type.name);
            if (i < returnTypes.size() - 1)
                print(", ");
        }
        if (returnTypes.size() > 1)
            print(")");
        print(" ");

        print(name);

        if (!genericTypes.empty())
            print("<" << Strings::join(genericTypes, U", ") << ">");
        print("(");

        for (uint i = 0; i < parameters.size(); i++) {
            print(parameters[i].type.value);
            if (!parameters[i].generics.empty()) {
                print("<");
                for (uint j = 0; j < parameters[i].generics.size(); j++) {
                    print(parameters[i].generics[j].value);
                }
                print(">");
            }
            if (parameters[i].varargs)
                print("...");

            print(" " << parameters[i].name);
            if (i < parameters.size() - 1)
                print(", ");
        }

        println(") {");

        for (Node* element : body) {
            uint index = -1;
            index++;
            print(Strings::fill(index + 1, "    "));
            element->debug(index);
            index--;
        }

        println("}");

        // skip the auto-inserted semicolon
        if (peek().is(TokenType::Semicolon))
            get();
        
        return new MethodNode(modifiers, returnTypes, name, parameters, List<Node*>());
    }

    /**
     * Parse the next field node.
     * @return new field node
     */
    Node* NodeParser::nextField() {
        return new ErrorNode();
    }

    /**
     * Parse the next type declaration.
     * @return new declared type
     */
    Node* NodeParser::nextType() {
        // handle method modifiers
        List<UString> modifiers = parseModifiers(NodeType::Method);

        // get the kind of the type
        // class MyClass {
        // ^^^^^ the expression indicates the kind of the type
        UString kind = get(TokenType::Expression).value;

        // get the name of the type
        // class Test {
        //       ^^^^ the identifier indicates the name of the type
        UString name = get(TokenType::Identifier).value;

        // handle type generic names
        // struct MyGenericStruct<T> {
        //                       ^^^ the generic names are placed in between angle brackets
        List<UString> genericNames = parseGenericNames();

        print(kind << " " << name);
        if (!genericNames.empty())
            print("<" << Strings::join(genericNames, U",") << ">");

        // TODO generic type implementation (where T implements MyType)

        // handle type-specific body parsing
        if (kind == U"class")
            return nextClass(modifiers, name, genericNames);
        else if (kind == U"struct")
            return nextStruct(modifiers, name, genericNames);
        else if (kind == U"enum")
            return nextEnum(modifiers, name, genericNames);
        else if (kind == U"interface")
            return nextInterface(modifiers, name, genericNames);

        // handle unexpected token
        Token error = peek();
        println("Error (Type) " << error);
        return new ErrorNode();
    }

    /**
     * Parse the next class type declaration.
     * @param modifiers type access modifiers
     * @param name type name
     * @param genericNames type generic names
     * @return new declared class
     */
    Node* NodeParser::nextClass(List<UString> modifiers, UString name, List<UString> genericNames) {
        // handle type body begin
        get(TokenType::Begin);

        println(" {");

        // parse the body of the type
        List<Node*> nodes;
        while (!peek().is(TokenType::End))
            nodes.push_back(nextContent());

        // handle type body end
        get(TokenType::End);

        println("}");

        // handle auto-inserted semicolon at the end or the body
        if (peek().is(TokenType::Semicolon, U"auto"))
            get();

        return new ErrorNode();
    }

    /**
     * Parse the next struct type declaration.
     * @param modifiers type access modifiers
     * @param name type name
     * @param genericNames type generic names
     * @return new declared struct
     */
    Node* NodeParser::nextStruct(List<UString> modifiers, UString name, List<UString> genericNames) {
        // handle normal struct
        if (peek().is(TokenType::Begin)) {

        }

        else if (peek().is(TokenType::Open)) {
            // parse the fields of the tuple struct
            List<Parameter> parameters;
            bool typed = false;
            parseParameters(Token::of(TokenType::Open, U"("), Token::of(TokenType::Close, U")"), parameters, typed);

            // handle semicolon after the declaration
            if (peek().is(TokenType::Semicolon))
                get();

            print("(");
            for (uint i = 0; i < parameters.size(); i++) {
                auto param = parameters[i];
                if (typed)
                    print(param.type.value << " ");
                print(param.name);
                if (i < parameters.size() - 1)
                    print(", ");
            }
            println(")");

            return new TupleStruct(modifiers, name, genericNames, typed, parameters);
        }

        // handle unexpected token
        Token error = peek();
        println("Error (Struct) " << error);
        return new ErrorNode();
    }

    /**
     * Parse the next tuple struct type declaration.
     * @param modifiers type access modifiers
     * @param name type name
     * @param genericNames type generic names
     * @return new declared tuple struct
     */
    Node* NodeParser::nextTupleStruct(List<UString> modifiers, UString name, List<UString> genericNames) {
        return new ErrorNode();
    }

    /**
     * Parse the next class enum type declaration.
     * @param modifiers type access modifiers
     * @param name type name
     * @param genericNames type generic names
     * @return new declared enum
     */
    Node* NodeParser::nextEnum(List<UString> modifiers, UString name, List<UString> genericNames) {
        return new ErrorNode();
    }

    /**
     * Parse the next interface type declaration.
     * @param modifiers type access modifiers
     * @param name type name
     * @param genericNames type generic names
     * @return new declared interface
     */
    Node* NodeParser::nextInterface(List<UString> modifiers, UString name, List<UString> genericNames) {
        return new ErrorNode();
    }

    /**
     * Parse the next annotation type declaration.
     * @param modifiers type access modifiers
     * @param name type name
     * @param genericNames type generic names
     * @return new declared annotation
     */
    Node* NodeParser::nextAnnotation(List<UString> modifiers, UString name, List<UString> genericNames) {
        return new ErrorNode();
    }

    /**
     * Parse the next type or method declaration.
     * @return new declared type or method
     */
    Node* NodeParser::nextTypeOrMethod() {
        // handle package method declaration
        if (peek().is(TokenType::Type) || peek().is(TokenType::Identifier)) 
            return nextMethod();
        // handle multi-return method
        else if (peek().is(TokenType::Open))
            return nextMethod();
        // handle package method or class declaration
        else if (peek().is(TokenType::Modifier))
            return nextMethod();
        // handle package type declaration
        else if (peek().is(TokenType::Expression))
            return nextType();
        // handle unexpected token
        Token error = peek();
        println("Error (Type/Method) " << error);
        return new ErrorNode();
    }

    /**
     * Parse the next expression instruction.
     * @return new expression
     */
    Node* NodeParser::nextExpression() {
        // handle local variable declaration
        // let myVariable = 100
        // ^^^ the "let" keyword indicates that, the local variable declaration has been started
        if (peek().is(TokenType::Type))
            return nextLocalDeclaration();

        else if (peek().is(TokenType::Identifier) && at(cursor + 1).is(TokenType::Identifier))
            return nextLocalDeclaration();

        else if (peek().is(TokenType::Identifier) && at(cursor + 1).is(TokenType::Operator, U"<"))
            return nextLocalDeclaration();

        // handle variable assignation (TODO and non-primitive local variable declaration)
        else if (peek().is(TokenType::Identifier) && at(cursor + 1).is(TokenType::Operator, U"=") && !at(cursor + 2).is(TokenType::Operator, U"="))
            return nextLocalAssignation();

        // handle node grouping
        // let a = (b + c) + d
        //         ^ the open parenthesis indicate, that the following nodes should be placed in a node group
        else if (peek().is(TokenType::Open))
            return nextGroupOrTuple();

        // handle lambda function
        else if (peek().is(TokenType::Operator, U"|"))
            return nextLambdaFunction();

        // handle string template
        else if (peek().is(TokenType::Operator, U"$"))
            return nextStringTemplate();

        // handle literal constant or identifier
        // let name = "John Doe"
        //            ^^^^^^^^^^ the literal token indicates, that a value is expected
        else if (peek().isLiteral() || peek().is(TokenType::Identifier))
            return nextLiteralOrMethodCall();

        // handle single value operation
        // TODO make sure the target operator is a single-value operator
        else if (peek().is(TokenType::Operator))
            return nextSingleOperator();

        // handle return statement
        else if (peek().is(TokenType::Expression, U"return"))
            return nextReturnStatement();

        // handle instruction deferring
        else if (peek().is(TokenType::Expression, U"defer"))
            return nextDeferStatement();

        // handle if statement
        else if (peek().is(TokenType::Expression, U"if"))
            return nextIfStatement();

        // handle while statement
        else if (peek().is(TokenType::Expression, U"while"))
            return nextWhileStatement();

        // handle do-while statement
        else if (peek().is(TokenType::Expression, U"do"))
            return nextDoWhileStatement();

        // handle new statement
        else if (peek().is(TokenType::Expression, U"new"))
            return nextNewStatement();

        // TODO handle local variable assignation
        // handle unexpected token
        Token error = peek();
        println("Error (Expression) " << error);
        return new ErrorNode();
    }

    /**
     * Parse the new local declaration.
     * @return new local declaration
     */
    Node* NodeParser::nextLocalDeclaration() {
        // get the type of the local variable
        // float myNumber = 3
        // ^^^^^ the type or identifier indicates the type of the local variable
        Token type = get(2, TokenType::Type, TokenType::Identifier);

        // handle tuple destruction
        // let (a, b) = foo()
        //     ^ the open parenthesis after "let" indicates, that the tuple value should be destructed
        if (peek().is(TokenType::Open)) {
            // TODO make sure that type is "let"
            List<UString> members;
        parseTupleMember:
            get();
            // register the tuple member
            UString member = get(TokenType::Identifier).value;
            members.push_back(member);
            // handle more tuple members
            if (peek().is(TokenType::Comma))
                goto parseTupleMember;
            // handle tuple destruction ending
            get(TokenType::Close);

            // handle the assignation of the tuple destruction
            // let (a, b) = foo()
            //            ^ the equals sign indicates that the assignation of the local variable has been started
            get(TokenType::Operator, U"=");

            // parse the value of the local variable
            // let (code, msg) = requestSomething()
            //                   ^^^^^^^^^^^^^^^^^^ the instructions after the equals sign is the value of the local variable
            Node* value = nextExpression();

            // skip the semicolon after the declaration
            // let (a, b, c) = fooBar();
            //                         ^ the (auto-inserted) semicolon indicates, that the assigning variable declaration has been ended
            if (peek().is(TokenType::Semicolon))
                get();

            return new LocalDeclareDestruct(members, value);
        }

        // parse the generic tokens of the variable type
        List<Token> typeGenerics; 
        if (type.is(TokenType::Identifier))
            typeGenerics = parseGenerics();

        // get the name of the local variable
        // let variable = "Hello, World"
        //     ^^^^^^^^ the identifier indicates the name of the local variable
        UString name = get(TokenType::Identifier).value;

        // check if the local variable does not have an initial value
        // let myVar;
        //          ^ the (auto-inserted) semicolon indicates that the local variable is not initialized by defualt
        if (peek().is(TokenType::Semicolon)) {
            get();
            return new LocalDeclare(type, typeGenerics, name);
        }

        // handle the assignation of the local variable
        // let number = 100
        //            ^ the equals sign indicates that the assignation of the local variable has been started
        get(TokenType::Operator, U"=");

        // parse the value of the local variable
        // let value = 100 + 50 - 25
        //             ^^^^^^^^^^^^^ the instructions after the equals sign is the value of the local variable
        Node* value = nextExpression();

        // skip the semicolon after the declaration
        // let variable = 100;
        //                   ^ the (auto-inserted) semicolon indicates, that the assigning variable declaration has been ended
        if (peek().is(TokenType::Semicolon))
            get();

        return new LocalDeclareAssign(type, typeGenerics, name, value);
    }

    /**
     * Parse the next local variable value assignation.
     * @return new local assignation
     */
    Node* NodeParser::nextLocalAssignation() {
        // get the name of the local variabl
        UString name = get().value;

        // skip the equals sign
        get(TokenType::Operator, U"=");

        // parse the value of the local variable
        Node* value = nextExpression();

        // skip the semicolon after the declaration
        if (peek().is(TokenType::Semicolon))
            get();

        return new LocalAssign(name, value);
    }

    /**
     * Parse the next lambda function declaration.
     * @return new lambda function
     */
    Node* NodeParser::nextLambdaFunction() {
        // parse the parameters of the lamba function
        List<Parameter> parameters;
        bool typed = false;
        Token token = Token::of(TokenType::Operator, U"|");
        parseParameters(token, token, parameters, typed);

        // parse the body of the lambda function
        List<Node*> body = parseStatementBody();

        return new Lambda(typed, parameters, body);
    }

    /**
     * Parse the next literal value or method call declaration.
     * @return new literal or method call
     */
    Node* NodeParser::nextLiteralOrMethodCall() {
        // handle literal constant or identifier
        // 
        // let name = "John Doe"
        //            ^^^^^^^^^^ the literal token indicates, that a value is expected
        // get the value constant
        // let age = 32
        //           ^^ get the actual value of the literal
        Token value = get(10, TokenType::Identifier,
            TokenType::Boolean, TokenType::Character, TokenType::String,
            TokenType::Byte, TokenType::Short, TokenType::Integer, 
            TokenType::Long, TokenType::Float, TokenType::Double
        );

        // handle single value expression, in which case the local variable is declared, but is not initialized
        // let myUninitializedVariable;
        //                            ^ the (auto-inserted) semicolon indicates, that the variable is declared, but is not yet assigned with a value
        if (peek().is(TokenType::Semicolon))
            return new Value(value);

        // handle operation between two expressions
        // let var = 100 + 
        //               ^ the operator after a literal indicates, that there are more expressions to be parsed
        //                 the two operands are groupped together by an Operation node
        else if (peek().is(2, TokenType::Operator, TokenType::Colon)) {
            UString target = parseOperator();
            // handle right-side single-value operation
            if (isRightOperator(target))
                return new SideOperation(target, new Value(value), false);
            // TODO make more proper error handling
            if (!isComplexOperator(target))
                error("Expected complex operator, but got " << target);
            return fixOperationTree(new Operation(new Value(value), target, nextExpression()));
        }

        // handle method call
        // println("Hello, World!")
        //        ^ the open parenthesis token after an identifier indicates, that a method call is expected
        else if (peek().is(TokenType::Open)) {
            // TODO make sure "value" is an identifier

            List<Node*> arguments = parseArguments();

            // check if the method call is used as a statement or isn't expecting to be passed in a nested context
            // let result = calculateHash("my input"); 
            //                                       ^ the semicolon indicates, that the method call does not have any
            //                                         expressions after. unlike: let res = foo() + bar
            //                                         let test = baz(); <- method call value is terminated, not expecting anything afterwards
            if (peek().is(TokenType::Semicolon))
                get();

            // handle operation after a method call
            // outer(inner(123) + 2)
            //                  ^ the operator indicates, that the method call should be groupped with the expression afterwards
            if (peek().is(TokenType::Operator)) {
                UString target = parseOperator();
                // TODO make more proper error handling
                if (!isComplexOperator(target))
                    error("Expected complex operator, but got " << target);
                return fixOperationTree(new Operation(new MethodCall(value.value, arguments), target, nextExpression()));
            }

            return new MethodCall(value.value, arguments);
        }

        // handle group closing
        // let val = (1 + 2) / 3
        //                 ^ the close parenthesis indicates, that we are not expecting any value after the current token
        else if (peek().is(TokenType::Close))
            return new Value(value);

        // handle argument list or array fill
        // foo(123, 450.7)
        //        ^ the comma indicates, that the expression has been terminated
        else if (peek().is(TokenType::Comma))
            return new Value(value);

        // handle index closing or array end
        // foo[10] = 404
        //       ^ the closing square bracket indicates, that the expression has been terminated
        else if (peek().is(TokenType::Stop))
            return new Value(value);

        // handle initializator end
        // new Pair { key: "value" }
        //                         ^ the closing vracket indicates, that the initializator has been terminated
        else if (peek().is(TokenType::End))
            return new Value(value);

        // handle indexing
        else if (peek().is(TokenType::Start)) {
            // skip the '[' sign
            get();
            // parse the index value
            Node* index = nextExpression();
            // handle the ']' after the index
            get(TokenType::Stop);

            // check if the value is assigned for the index
            if (peek().is(TokenType::Operator, U"=")) {
                // skip the '=' sign
                get();
                // parse the value of index index assignation
                Node* indexValue = nextExpression();

                // handle the semicolon after index assignation
                if (peek().is(TokenType::Semicolon))
                    get();

                return new IndexAssign(value.value, index, indexValue);
            }

            // handle operation after an index fetch
            if (peek().is(TokenType::Operator)) {
                UString target = parseOperator();
                // TODO make more proper error handling
                if (!isComplexOperator(target))
                    error("Expected complex operator, but got " << target);
                return fixOperationTree(new Operation(new IndexFetch(value.value, index), target, nextExpression()));
            }

            // there is no value assignation, handle index fetch
            return new IndexFetch(value.value, index);
        }

        Token error = peek();
        println("Error (Literal / Method Call) " << error);
        return new ErrorNode();
    }

    /**
     * Parse the next string template declaration.
     * @return new string template
     */
    Node* NodeParser::nextStringTemplate() {
        // skip the '$' sign
        get(TokenType::Operator, U"$");
        // get the string value of the template
        Token value = get(TokenType::String);

        // handle operation after template string
        if (peek().is(TokenType::Operator)) {
            UString target = parseOperator();
            // TODO make more proper error handling
            if (!isComplexOperator(target))
                error("Expected complex operator, but got " << target);
            return fixOperationTree(new Operation(new Template(value), target, nextExpression()));
        }

        return new Template(value);
    }

    /**
     * Parse the next single value operator declaration.
     * @return new single operator
     */
    Node* NodeParser::nextSingleOperator() {
        // get the operator of the operation
        UString target = parseOperator();
        // parse the operand of the operation
        Node* operand = nextExpression();
        
        // test if an invalid left operator was given
        // TODO handle this properly
        if (!isLeftOperator(target))
            error("Expected left-side operator, but got " << target);

        return new SideOperation(target, operand, true);
    }

    /**
     * Parse the next value return statement declaration.
     * @return new return statement
     */
    Node* NodeParser::nextReturnStatement() {
        // skip the "return" keyword
        get(TokenType::Expression, U"return");

        // check if the return statement has no value to return
        if (peek().is(TokenType::Semicolon)) {
            get();
            return new Return();
        }

        // parse the value to be retured
        Node* value = nextExpression();

        // handle the semicolon after the return statement
        if (peek().is(TokenType::Semicolon))
            get();

        return new Return(value);
    }

    /**
     * Parse the next instruction deferrer statement declaration.
     * @return new defer statement
     */
    Node* NodeParser::nextDeferStatement() {
        // skip the "defer" keyword
        get(TokenType::Expression, U"defer");

        // parse the instruction to be deferred
        Node* instruction = nextExpression();

        // handle the semicolon after the defer statement
        if (peek().is(TokenType::Semicolon))
            get();

        return new Defer(instruction);
    }

    /**
     * Parse the next group or tuple declaration.
     * @return new group or tuple
     */
    Node* NodeParser::nextGroupOrTuple() {
        // let a = (b + c) + d
        //         ^ the open parenthesis indicate, that the following nodes should be placed in a node group
        // skip the '(' sign
        get(TokenType::Open);

        // parse the expression inside the group
        // let res = (1 + 2 + 3) / 4
        //            ^^^^^^^^^ the nodes between parenthesis are the content of the node group
        Node* value = nextExpression();

        // handle tuples
        if (peek().is(TokenType::Comma)) {
            // append the first value of the group
            List<Node*> members;
            members.push_back(value);

            // parse the members of the tuple
        parseMember:
            // skip the comma token
            get();

            // parse the next member of the tuple
            Node* member = nextExpression();
            members.push_back(member);

            // check if there are more members or the tuple
            if (peek().is(TokenType::Comma))
                goto parseMember;

            // handle tuple ending
            get(TokenType::Close);

            return new Tuple(members);
        }

        // handle the group closing
        // let test = (7 - 1)
        //                  ^ the closing parenthesis indicate, that the declaration of node group has been ended
        get(TokenType::Close);

        // handle operation after a node group
        // (2 + 3) + 7
        //         ^ the operator indicates, that the method call should be groupped with the expression afterwards
        if (peek().is(TokenType::Operator)) {
            UString target = parseOperator();
            // TODO make more proper error handling
            if (!isComplexOperator(target))
                error("Expected complex operator, but got " << target);
            return fixOperationTree(new Operation(new Group(value), target, nextExpression()));
        }

        return new Group(value);
    }

    /**
     * Parse the next if statement declaration.
     * @return new if statement
     */
    Node* NodeParser::nextIfStatement() {
        // skip the "if" keyword
        get(TokenType::Expression, U"if");

        // parse the statement condition
        Node* condition = parseCondition();

        // handle bodyless if statement
        // tbh, I'm not quite sure why is this allowed in so many languages, but I'll just support doing it
        if (peek().is(TokenType::Semicolon)) {
            get();
            return new If(condition, List<Node*>());
        }

        // parse the body of the if statement
        List<Node*> body = parseStatementBody();

        // parse the if statement
        If* statement = new If(condition, body);

        // handle else or else if cases
        if (peek().is(TokenType::Expression, U"else")) {
            // handle else if cases
            if (at(cursor + 1).is(TokenType::Expression, U"if")) {
            parseElseIf:
                // parse the next else if case
                Node* node = nextElseIfStatement();
                // register the case for the if statement
                statement->elseIfs.push_back(dynamic_cast<ElseIf*>(node));

                // check if there are more else if cases to be parsed
                if (peek().is(TokenType::Expression, U"else") && at(cursor + 1).is(TokenType::Expression, U"if")) 
                    goto parseElseIf;
            }

            // check if an else case still follows
            if (peek().is(TokenType::Expression, U"else")) {
                // parse the else statement
                Node* node = nextElseStatement();
                // register the case for the if statement
                statement->elseCase = dynamic_cast<Else*>(node);
            }
        }

        return statement;
    }

    /**
     * Parse the next else if statement declaration.
     * @return new else if statement
     */
    Node* NodeParser::nextElseIfStatement() {
        // skip the "else" keyword
        get(TokenType::Expression, U"else");
        // skip the "if" keyword
        get(TokenType::Expression, U"if");

        // parse the statement condition
        Node* condition = parseCondition();

        // handle bodyless else if statement
        // tbh, I'm not quite sure why is this allowed in so many languages, but I'll just support doing it
        if (peek().is(TokenType::Semicolon)) {
            get();
            return new ElseIf(condition, List<Node*>());
        }

        // parse the body of the else if statement
        List<Node*> body = parseStatementBody();

        return new ElseIf(condition, body);
    }

    /**
     * Prase the next else statement declaration.
     * @return new else statement
     */
    Node* NodeParser::nextElseStatement() {
        // skip the "else" keyword
        get(TokenType::Expression, U"else");

        // parse the body of the else statement
        List<Node*> body = parseStatementBody();

        return new Else(body);
    }

    /**
     * Parse the next while loop statement declaration.
     * @return new while statement
     */
    Node* NodeParser::nextWhileStatement() {
        // skip the "while" keyword
        get(TokenType::Expression, U"while");

        // parse the condition of the while statement
        Node* condition = parseCondition();

        // handle bodyless while statement
        // tbh, I'm not quite sure why is this allowed in so many languages, but I'll just support doing it
        if (peek().is(TokenType::Semicolon)) {
            get();
            return new While(condition, List<Node*>());
        }

        // parse the body of the while statement
        List<Node*> body = parseStatementBody();

        return new While(condition, body);
    }

    /**
     * Parse the next do-while statement declaration.
     */
    Node* NodeParser::nextDoWhileStatement() {
        // skip the "do" keyword
        get(TokenType::Expression, U"do");

        // parse the body of the do-while statement
        List<Node*> body = parseStatementBody();

        // skip the "while" keyword
        get(TokenType::Expression, U"while");

        // parse the condition of the do-while statement
        Node* condition = parseCondition();

        return new DoWhile(body, condition);
    }

    /**
     * Parse the new statement declaration.
     * @return new "new" statement
     */
    Node* NodeParser::nextNewStatement() {
        // skip the "new" keyword
        get(TokenType::Expression, U"new");

        // get the name of the target type
        UString name = get(TokenType::Identifier).value;

        // TODO enum ConstructType { 
        //     DEFAULT -> new Foo() 
        //     STRUCT, -> new Bar { x: true, y: 2 }
        //     ABSTRACT -> new Baz() { @Override void foo() { } }
        // }
        ConstructType type = ConstructType::Default;

        // ignore the auto-inserted semicolon
        if (peek().is(TokenType::Semicolon, U"auto"))
            get();

        // check if the new keyword has an argument list
        List<Node*> arguments;
        if (peek().is(TokenType::Open))
            arguments = parseArguments();

        // ignore the auto-inserted semicolon
        if (peek().is(TokenType::Semicolon, U"auto"))
            get();

        // check if the new keyword has an initializator
        Node* initializator = nullptr;
        if (peek().is(TokenType::Begin)) {
            type = ConstructType::Struct;
            initializator = nextInitializator();
        }

        Node* node = new NewNode(name, type, arguments, initializator);

        // handle operation after constructor
        if (peek().is(TokenType::Operator)) {
            UString target = parseOperator();
            return new Operation(node, target, nextExpression());
        }

        // check if the method call is used as a statement or isn't expecting to be passed in a nested context
        // let result = new Foo("my input"); 
        //                                 ^ the semicolon indicates, that the method call does not have any
        //                                   expressions after. unlike: let res = foo() + bar
        //                                   let test = new Foo(); <- method call value is terminated, not expecting anything afterwards
        if (peek().is(TokenType::Semicolon))
            get();

        return node;
    }

    /**
     * Parse the next structure initializator declaration.
     * @return new structure initializatior
     */
    Node* NodeParser::nextInitializator() {
        // skip the '{' symbol
        get(TokenType::Begin);

        // parse the members of the initializator
        TreeMap<UString, Node*> members;
        if (!peek().is(TokenType::End)) {
        parseMember:
            // parse the key of the member
            UString key = get(TokenType::Identifier).value;

            // handle the separator ':' symbol of the key-value pair
            get(TokenType::Colon);

            // parse the value of the member
            Node* value;
            // check if the value is also an initializer
            if (peek().is(TokenType::Begin))
                value = nextInitializator();
            // handle regular initializator value
            else
                value = nextExpression();

            // register the initializator member
            // TODO warn for duplicate members
            members[key] = value;

            // check if there are are more members yet to be parsed
            if (peek().is(TokenType::Comma)) {
                get();
                goto parseMember;
            }

            // handle auto-inserted semicolon
            if (peek().is(TokenType::Semicolon, U"auto"))
                get();
        }

        // skip the '}' symbol
        get(TokenType::End);

        return new Initializator(members);
    }

    /**
     * Check if the first operator has a predecende priority over the second operator.
     * @param first first operator to check
     * @param second second operator to check
     * @return true if the first operator has higher precedence than the second one
     */
    bool NodeParser::hasPrecedence(UString first, UString second) {
         return OPERATION_INFO[first].first > OPERATION_INFO[second].first ||
            (OPERATION_INFO[first].first == OPERATION_INFO[second].first &&
                OPERATION_INFO[first].second == 0);
    }

    /**
     * Fix the order of the operation sequences in the parsed value node.
     * @param root root value expression node
     * @return fixed node operations
     */
    Node* NodeParser::fixOperationTree(Node* node) {
        // if the node is not an operation, return it as is
        if (dynamic_cast<Operation*>(node) == nullptr) {
            return node;
        }

        Operation* op = static_cast<Operation*>(node);
        // recursively correct the order of the left and right nodes
        op->left = fixOperationTree(op->left);
        op->right = fixOperationTree(op->right);

        // check if the current operator has lower precedence than the operator
        // of its right child
        if (op->right != nullptr &&
            dynamic_cast<Operation*>(op->right) != nullptr &&
            hasPrecedence(op->target, static_cast<Operation*>(op->right)->target)) {
            // perform a right rotation
            Node* tmp = op->right;
            op->right = static_cast<Operation*>(tmp)->left;
            static_cast<Operation*>(tmp)->left = op;
            return tmp;
        }

        // check if the current operator has lower or equal precedence than the
        // operator of its left child, and the left child is also an operation
        if (op->left != nullptr &&
            dynamic_cast<Operation*>(op->left) != nullptr &&
            hasPrecedence(op->target, static_cast<Operation*>(op->left)->target) &&
            OPERATION_INFO[op->target].second == 0) {
            // perform a left rotation
            Node* tmp = op->left;
            op->left = static_cast<Operation*>(tmp)->right;
            static_cast<Operation*>(tmp)->right = op;
            return tmp;
        }

        // the current order is correct, so return the node as it is
        return node;
    }

    /**
     * Parse the next content of a type, which might be a type, method or field.
     * @return new declared type, method or field
     */
    Node* NodeParser::nextContent() {
        // handle method or field declaration
        if (peek().is(2, TokenType::Type, TokenType::Identifier) && at(cursor + 1).is(TokenType::Identifier)) {
            if (at(cursor + 2).is(TokenType::Open))
                return nextMethod();
            return nextField();
        }
        // handle multi-return method
        else if (peek().is(TokenType::Open))
            return nextMethod();
        // handle method or type declaration
        else if (peek().is(TokenType::Modifier)) {
            // temporarily skip the modifiers before the declaration
            uint index = cursor;
            while (at(index).is(TokenType::Modifier))
                index++;
            // handle type decleration
            if (at(index).is(TokenType::Expression))
                return nextType();
            // handle method or field declaration
            else if (at(index).is(2, TokenType::Type, TokenType::Identifier) && at(index + 1).is(TokenType::Identifier)) {
                // handle method declaration
                if (at(index + 2).is(TokenType::Open))
                    return nextMethod();
                return nextField();
            }
        }
        // handle package type declaration
        else if (peek().is(TokenType::Expression))
            return nextType();
        // TODO handle field
        // handle unexpected token
        Token error = peek();
        println("Error (Content) " << error);
        return new ErrorNode();
    }

    /**
     * Parse the next package declaration.
     * @return new declared package
     */
    Node* NodeParser::nextPackage() {
        // handle package declaration
        get(TokenType::Info, U"package");
        // get the name of the package
        UString name = get(TokenType::String).value;
        // ensure that the package is ended by a semicolon
        get(TokenType::Semicolon);
        println("package \"" << name << '"');
        return new Package(name);
    }

    /**
     * Parse the next package import.
     * @return new package import
     */
    Node* NodeParser::nextImport() {
        // handle package import
        get(TokenType::Info, U"import");
        // get the name of the package
        UString name = get(TokenType::String).value;
        // ensure that the package is ended by a semicolon
        get(TokenType::Semicolon);
        println("import \"" << name << '"');
        return new Import(name);
    }

    /**
     * Parse the generic types of a type.
     * @return geneirc type tokens
     */
    List<Token> NodeParser::parseGenerics() {
        List<Token> generics;
        // handle no generic type declaration
        if (!peek().is(TokenType::Operator, U"<"))
            return generics;
        // handle the '<' symbol that starts the generic type
        get();
        // the offset of the nested '<' symbols in the generic type
        // assuming that the code might look something like Map<UUID, List<Data>>
        // it is 1 by default, because the first '<' has been already handled
        uint offset = 1;
        // loop until the generic type declaration ends
        while (true) {
            Token token = get();
            // handle nested generic type
            if (token.is(TokenType::Operator, U"<"))
                offset++;
            // handle generic type end
            else if (token.is(TokenType::Operator, U">") && --offset == 0)
                break;
            // check if the generic type wasn't terminated closed properly before closing
            else if (token.is(TokenType::Close))
                error("Invalid closing of generic type.");
            // register the generic token
            generics.push_back(token);
        }
        // check if the generic symbols were given, but no actual generic types were provided
        if (generics.empty())
            error("Generic type cannot be left empty.");
        return generics;
    }

    /**
     * Parse the generic names of a method or type.
     * @return generic type names
     */
    List<UString> NodeParser::parseGenericNames() {
        // handle method or type generic types
        // method and type generic type declaration look somewhat different from type generic declaration
        // in here we only define what identifiers we are willing to use as generic types inside the method
        // void concat<T>(List<T> firstList, List<T> secondList)
        //            ^^^ method generics are placed after the method name
        // void createMap<K,V>()
        //                 ^ you may have multiple method generic types
        //                   they are also separated with a comma
        List<UString> genericNames;
        if (peek().is(TokenType::Operator, U"<")) {
        parseGeneric:
            // skip the '<' or ',' symbol
            // void foo<Bar,Baz>()
            //         ^   ^ we don't care about these two characters, as they are already handled
            get();

            // get the name of the generic 
            // void myMethod<MyGeneric>()
            //               ^^^^^^^^^ the identifier (name) of the method generic type 
            UString genericName = get(TokenType::Identifier).value;
            genericNames.push_back(genericName);

            // check if there are more generic types
            // U transform<T,U>(T source)
            //              ^ comma indicates, that there are more method generic types
            if (peek().is(TokenType::Comma))
                goto parseGeneric;

            // handle method generic types end
            // T getValue<T>(String key)
            //              ^ close angle bracket indicates, that the declaration of the method generic types has ended
            get(TokenType::Operator, U">");
        }
        return genericNames;
    }

    /**
     * Parse the array declaration of a type.
     * @return array dimensions
     */
    int NodeParser::parseArray() {
        // loop while the token is an array start
        // int[] myArray
        //    ^  square brackets indicate that the type is an array
        // float[][] my2DArray
        //      ^ ^ multiple square brackets indicate the dimensions of an array
        //           this one is a 2 dimensional array for example
        int dimensions = 0;
        while (peek().is(TokenType::Start)) {
            get();
            // float[] getVectorElements()
            //       ^ a closing square bracket must be placed right after an open square bracket
            get(TokenType::Stop);
            dimensions++;
        }
        return dimensions;
    }

    /**
     * Parse the modifiers of the given node type.
     * @param type target node type
     * @return parsed modifier list
     */
    List<UString> NodeParser::parseModifiers(NodeType type) {
        // loop while the token is a modifier
        // public static void test()
        // ^^^^^^ ^^^^^^ modifiers are placed before the target object
        List<UString> modifiers;
        while (peek().is(TokenType::Modifier)) {
            // TODO handle modifier regions (public:)
            // TODO handle node type
            modifiers.push_back(get().value);
        }
        return modifiers;
    }

    /**
     * Parse the next operator target.
     * @return parsed operator
     */
    UString NodeParser::parseOperator() {
        UString result;
        while (peek().is(TokenType::Operator)) 
            result += get().value;
        while (peek().is(TokenType::Colon)) {
            get();
            result += ':';
        }
        return result;
    }

    /**
     * Test if the given operator is applicable for a left-right use.
     * @return true if the operator expects two values
     */
    bool NodeParser::isComplexOperator(UString target) {
        return target == U"+"
            || target == U"+="
            || target == U"-"
            || target == U"-="
            || target == U"*"
            || target == U"*="
            || target == U"/"
            || target == U"/="
            || target == U"&"
            || target == U"&="
            || target == U"|"
            || target == U"|="
            || target == U"&&"
            || target == U"||"
            || target == U"::"
            || target == U"<"
            || target == U"<="
            || target == U">"
            || target == U">="
            || target == U"=="
            || target == U">>"
            || target == U">>>"
            || target == U"<<" // TODO check triple shift operators
            || target == U"??"
            || target == U"?."
            || target == U"?"
            || target == U":"
            || target == U".";
    }

    /**
     * Test if the given operator is applicable before a value.
     * @return true if the operator expects a value on its right
     */
    bool NodeParser::isLeftOperator(UString target) {
        return target == U"!"
            || target == U"++"
            || target == U"--"
            || target == U"-";
    }

    /**
     * Test if the given operator is applicable after a value.
     * @return true if the operator expects a value on its left
     */
    bool NodeParser::isRightOperator(UString target) {
        return target == U"++"
            || target == U"--";
    }

    /**
     * Test if there are variadic arguments declared.
     * @return true if varargs are declared
     */
    bool NodeParser::testVarargs() {
        // ignore non-varargs tokens
        if (!peek().is(TokenType::Operator, U"."))
            return false;
        // parse the variadic arguments indicator
        get(TokenType::Operator, U".");
        get(TokenType::Operator, U".");
        get(TokenType::Operator, U".");
        return true;
    }

    /**
     * Parse the next condition of a condition block, such as if, else if, while.
     * @return new conditional node
     */
    Node* NodeParser::parseCondition() {
        // handle the beginning of the condition
        get(TokenType::Open);

        // parse the statement condition
        // TODO support conditional let, instanceof simplifier
        Node* condition = nextExpression();

        // handle the ending of the condition
        get(TokenType::Close);

        // handle auto-inserted semicolon after condition
        if (peek().is(TokenType::Semicolon, U"auto")) // make sure to only handle auto-inserted semicolons here, as manually inserting 
            get();                                    // one would meanm the statement has no body: 
                                                      // <expression> (condition); outer();
                                                      //                         ^ statement terminated here
        return condition;
    }

    /**
     * Parse the next block of instructions that belong to a block, such as if, else if, while.
     * @return new block statement body
     */
    List<Node*> NodeParser::parseStatementBody() {
        // parse the body of the statement
        List<Node*> body;

        // check if multiple instructions should be assigned for the body
        // <expression> (condition) { /* do something */ }
        //                   ^ the open curly bracket indicates, that the statement body has multiple instructions inside
        if (peek().is(TokenType::Begin)) {
            get();
            // parse the while statement instructions
            while (!peek().is(TokenType::End))
                body.push_back(nextExpression());
            get();
        }

        // handle single-instruction statement
        // <expression> (condition) foo()
        //                          ^ if there is no open curly bracket after the condition, it means
        //                            that there is only one instruction for the statement body
        else /* there is no '{' after the condition */
            body.push_back(nextExpression());
        
        // skip the auto-inserted semicolon after  statement body
        // TODO might wanna ignore manually inserted semicolon as well
        if (peek().is(TokenType::Semicolon, U"auto"))
            get();

        return body;
    }

    /**
     * Parse the next argument list declaration.
     * @return new argument list
     */
    List<Node*> NodeParser::parseArguments() {
        // skip the '(' char
        get(TokenType::Open);
        // handle method arguments
        // foo(123)
        //     ^^^ the tokens in between parenthesis are the arguments
        List<Node*> arguments;
        if (!peek().is(TokenType::Close)) {
        parseArgument:
            // register the parsed argument expression
            arguments.push_back(nextExpression());
            // check for more arguments
            // bar(4.5, true, "hello")
            //        ^ the comma indicates, that there are more arguments to be parsed
            if (peek().is(TokenType::Comma)) {
                // skip the ',' char
                get();
                // expect another method argument
                goto parseArgument;
            }
        }
        // handle argument list ending
        // baz("John Doe")
        //               ^ the close parenthesis indicates, that the argument listhas been ended
        get(TokenType::Close);

        return arguments;
    }

    /**
     * Parse the next parameter list declaration.
     * @param begin parameter list prefix
     * @param end parameter list suffix
     * @return new parameter list
     */
    void NodeParser::parseParameters(Token begin, Token end, List<Parameter>& parameters, bool& typed) {
        // skip the parameter list prefix
        get(begin.type, begin.value);

        // determine if weren't are declared in the lambda's parameter list
        // this must be tracked, because if one parameter sets a type, all
        // of the other parameters must set types as well
        bool noTyped = false;

        if (!peek().is(end.type, end.value)) {
        parseParameter:
            // get the next parameter
            // call(|x| println(x))
            //       ^ here this is just an identifier, which is the name of a lamba parameter
            // let other = |int x| println(x)
            //              ^^^^^ here a type is specified as well, expecting all the arguments to be typed
            Token token = get(2, TokenType::Identifier, TokenType::Type);

            // check if the parameter has a type
            // let foo = |int x| println(x)
            //            ^^^ the type token indicates, that the lambda function must declare a type for all of the parameters
            if (token.is(TokenType::Type)) {
                // TODO make sure value is not "let"
                // TODO make sure only the last argument is variadic
                typed = true;

                // test if the type is variadic
                // let callback = |float... f| print(f[0])
                //                      ^^^ these dots indicate, that the parameter type is variadic
                bool varargs = testVarargs();

                // get the name of the parameter
                // |int foo| bar(foo)
                //      ^^^ the identifier is the name of the parameter
                UString name = get(TokenType::Identifier).value;

                // register the lambda parameter
                parameters.push_back(Parameter(token, List<Token>(), varargs, name));

                if (noTyped) 
                    error("Inconsistent lambda parameter type declaration");
            }

            // check if the type was an identifier and a parameter identifier is following it
            // let func = |User u| u.login()
            //             ^^^^ if two identifiers follow each other, the first one is the type, 
            //                  the second one is the name of the parameter
            else if (peek().is(TokenType::Identifier)) /* assuming token is identifier */ {
                typed = true;
                // TODO parse type generic tokens

                // test if the type is variadic
                bool varargs = testVarargs();

                // get the name of the parameter
                // |Foo foo| bar(foo)
                //      ^^^ the identifier is the name of the parameter
                UString name = get(TokenType::Identifier).value;

                // register the lambda parameter
                parameters.push_back(Parameter(token, List<Token>(), varargs, name));

                if (noTyped)
                    error("Inconsistent lambda parameter type declaration");
            }
            // check if only the parameter name was given
            else /* assuming token is identifier */ {
                // check if types were given previously, but is missing from here
                if (typed)
                    error("Inconsistent lambda parameter type declaration");

                noTyped = true;
                // register the lambda parameter
                parameters.push_back(Parameter(Token::of(TokenType::None), List<Token>(), false, token.value));
            }

            // handle more parameters
            // data.enumerate(|index, value| bar())
            //                      ^ the comma indicates, that more lambda parameters are yet to be parsed
            if (peek().is(TokenType::Comma)) {
                // skip the '^' sign
                get();
                goto parseParameter;
            }

            // handle parameter list ending
            // foo(|x, y, z| baz(x  - y + z))
            //             ^ the "|" operator indicates, that the lambda parameter list has been ended
            get(end.type, end.value);
        }
    }
}
