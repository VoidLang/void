# The Void Programming Language

Any fool can write code that a computer can understand. Good programmers write code that humans can understand.
– Martin Fowler.

# Warning!
Void is currently being rewritten, as for now I'm mainly focusing on implementing Void for native.
A temporary compiler is made in Java, which will transform Void source code to machine code using [LLVM](https://github.com/llvm/llvm-project).
Therefore, this repository is now deprecated. Check out [LLVM-Backend](https://github.com/VoidLang/LLVM-Backend) and [VoidCompiler](https://github.com/VoidLang/VoidCompiler) in the meantime.
For further information, join the [discord server](https://discord.gg/HdgnHqqGAW).

## What is Void?
Void is a virtual-machine-based programing language designed for developers to be able to create clean, fast and stable multi-platform applications.

It has has a relatively easy syntax, that follows most of the already existing code conventions.

Void features many utilities that enchant the experience of coding, such as object destruction, variable redeclaration, multi-returning, and much more.

## Why Void?
Void compiles to bytecode, therefore it allows the application with the same exact code, to be ran on all platforms, whilst forward and backward compatibility is guaranteed.
It has many built-in designs, which makes it much easier to develop enterprise-grade applications.

## How to use Void?
Void is designed to satisfy the needs of multiple development paradigms. Unlike many production-oriented languages, Void does not force object-oriented programming on you, however it is recommended to use in most cases.

## Want to know more?
[Join the discord server](https://discord.gg/HdgnHqqGAW)

## Want to help the project?
[Donate to the Void Project](https://paypal.me/voidlang)

## Examples
Below are few examples showcasing what Void provides to enchant programming experience.

### A Hello World application

```java
void main() {
    println("Hello, World")
}
```


### Variable declaration
```
You can declare variables using the "let" keyword. 
It automatically detects the type of the variable, but type can be also declared explicitly.
```
```rust
let value = 100
```
```
In case of explicit type definition:
```
```java
float value = 3.5
```
```
As you may notice, semicolons are not required. 
The compiler automatically places them after the end of lines, when it is required. 
This allows the chaining syntax, unlike many in case of many languages.
```
```cpp
database
    .fetchUser("username")
    .transform(User::from)
    .getOrThrow(err)
```
```
In case of putting multiple statements in one line, 
you can separate them with putting a semicolon between them.
```
```java
int f = 0; float f = 10.0 
```
```
Although it is possible in Void, it is considered a bad practice of coding, 
as it can possibly overcomplicate a line of code. 
You may put only one statement in a line.
```


### Variable redeclaration
```
Normally languages doesn't let you declare variables twice, 
but as for some other languages such as Void, lets you to do that.
```
```
This is becuase in many cases you need to swap between variable types for a value, 
and having too much variables for a single value, 
or having long lines of type conversion is both considered a bad practice.
```
```java
// bad code
int balance = database.getUser("username").balance
String balanceStr = $"{balance} USD"

// also bad code
String balance = String.from(database.getUser("username").balance) + " USD"
```
```rust
// simplified code with variable redeclaration
let balance = database.getUser("username").balance
let balance = $"{balance} USD"
```

### Multi-returning
```
Void lets you have methods return multiple variables at once.
This allows you to have more simple codes, 
without the need of making structs holding multiple values for return.
```
```c#
// overcomplicated code
struct HttpResponse {
    public int code
    public String message
}

HttpResponse fetchURL(String url) {
    return new HttpResponse {
        code: 404,
        message: "Not found."
    }
}

// simplified code
(int, String) fetchURL(String url) {
    return (404, "Not found.")
}
```
```
In the last example, a tuple is returned. 
A tuple can hold values of any length and any type. 
To access these values you can use a feature called tuple destruction.
```
```js
let (code, message) = fetchURL("google.com")
println($"Webserver responded with {code} status code")
```
```
You can also access these values without destructing the tuple. 
You need to specify the index of the tuple you want to retrieve.
```
```rust
let response = fetchURL("google.com")
let code = response.0
let message = response.1
```
```
Void allows you to name tuple members. 
Member names are specified inside the method return type declaration.
```
```c#
(boolean success, String token) authenticate(String username, String password) {
    return (true, "Authenticated.")
}
```
```
In this case, you can access these values by their names.
```
```js
let result = authenticate("admin", "12345")
if (result.success) {
    println("Authenticated.")
    println($"Token: {result.token}")
} else {
    println("Invalid credentials.")
}
```


### Primitive types
```
Void features a wide variety of primitive types.
```
```
byte, short, int, long, float, double
```
```
And their unsigned version.
```
```
ubyte, ushort, uint, ulong, ufloat, udouble
```


### Simplified number constants
```
You can specify the types of numbers in the number constant.
```
```rust
let byteVal = 30B
let shortVal = 150S
let intVal = 540 // you don't need to put 'I' prefix, as non-decimal numbers are integers by default
let longVal = 120000L
let floatVal = 3.5F
let doubleVal = 40D
```

### Class types
```
The most high-level one of types is the class type.
It has the capatibility of holding methods, implementations, fileds, and much more.
```
```java
class Car {
    String type
    int speed

    void move() {
        println("Moving...")
    }
}
```
```
In case of the need of classes, which are only for the purpose of holding values, you can use structs.
Structs are simplified classes with the purpose of holding values.
```
```rust
struct Point {
    int x
    int y
}

let point = new Point { x: 2, y: 3 }
```
```java
// you can use the simplified initializator, if Void knows the type of the struct
Point point = { x: -7, y: 0}

void drawPoint(Point point) { /* do something */ }
drawPoint({ x: 30, y: 40 })
```
```
You can create classes which only show you what methods they have, 
but they don't have an actual implementations.
```
```java
interface Car {
    void move()
} 
```
```
The methods are implemented by a class.
```
```java
class Ferrari implements Car {
    @Override
    void move() {
        println("Vrooooom...")
    }
}
```
```
You can have classes with constant members.
```
```java
enum MimeType {
    PLAIN_TEXT("text/plain"),
    IMAGE("image/png"),
    VIDEO("video/mp4")

    String data;

    MimeType(String data) {
        this.data = data;
    }
}
```
```
You can decorate classes, fields, methods or code blocks with annotations.
```
```java
@interface Subscribe {
    String event
}

@Subscribe(event = "playerJoin")
void onPlayerJoin() {
    println("A player has joined the game.");
}
```
### Access modifiers
```
Void features two types of access modifier declarations.
```
```
You can specify access modifiers separately for each methods and fields.
However this is not a good practise, as you are making method declarations 
much longer by having to put these manually everywhere.
```
```c#
public static void foo() {
    println("bar")
}

struct Point {
    public int x, y
}
```
```
Alternatively, you can use "modifier blocks", 
which allows you to set the visibility modifiers of a section of code.
```
```cpp
class Entity {
public:
    int posX, posY

    int entityId

private:
    float health

    float stamina
}
```
```java
Visibility modifiers are public, protected and private.
```


### Object destruction
```
You can destruct object members in order to make them more accessible in the code.
```
```rust
struct Point {
    int x, y
}
```
```js
let point = new Point { x: 10, y: -2 }
let { x, y } = point

println($"Point {x}, {y}")


// you don't have to deconstruct all the variables of an object
let { x } = point
```


### Lambda objects
```
You can create anonymus functions inside the code. These are also known as lambdas.
```
```rust
let foo = |int x| println(x)
foo(123)
```
```java
interface Callback {
    void handle(int x, int y)
}

void bar(Callback c) {
    c.handle(2, 3)
}

bar(|x, y| println(x * y))

```

### Default values
```
Using the default(Type) function, you can retrieve the default value of the given type.
```
```js
let number = default(int) // 0
let state = default(bool) // false
let car = default(Car) // null
```
```
Void features a system, which allows to create custom default values for your own class types.
You should put a "default" modifier before the class declaration, 
and a default() method must be declared as well.
```
```java
default class Credentials {
    String username, password
	
    default() {
        return {
            username: "admin",
            password: "12345"
        }
    }
}
```
```rust
// initialize credentials to the default value 
let credentials = default(Credentials ) // { username: "admin", password: "12345" }

// you can use the default function without an explicit type, 
if the variable's type is defined explicitly
Credentials credentials = default 

// a simplfied syntax is also available
default Credentials credentials
```


### Null-conditional operators
```
Null-conditional operators provide null-safe access to members.
A '?' mark is placed before the instruction to make it null-conditional.
```
```rust
let profile = database.find("user")

// the profile's balance is retrieved if the profile is not null, otherwise a default value is required
println(profile?.balance ?? 0)

let person = getSomePerson() // might be null
// the "walk" method is not invoked if "person" is null
person?.walk()

// you can use null-conditional operators on nested members as well
person?.entity?.motion?.move()
```

### Static variables
```
By default, variables live only in the scope of a method. 
Static variables however provide a way to statically store data in the method,
that is accessible for further method calls.
```
```ts
int getIncrementId() {
    static let counter = 0
    return counter++
}

getIncrementId() // returns 0
getIncrementId() // returns 1
getIncrementId() // returns 2
```


### Enchanted switch
```
In Void you can use the old switch syntax.
```
```java
switch (status) {
    case 200:
        println("ok")
        break
    case 400:
        println("error")
        break
    default:
        println("unrecognized")
}
```
```
However in most cases, this old design forces us to write a lot of unnecessary code, 
such as always having to write "break" after each cases.
Void's echanted switch allows you to simplify switch blocks and use them as direct expressions.
```
```java
enum Status {
    SUCCESS,
    FAILED,
    UNKNOWN
}

switch (code) {
    200 -> println("success")
    400 -> println("failed")
    else -> println("unknown")
}

// you can merge cases as well
switch (status) {
    FAILED|UNKNOWN -> println("Unable to authenticate")
    SUCCESS -> println("Authenticated")
}
```

### Blocks as expressions
```
You can use code blocks as expressions, including loops and switches.
```
```js
let status = switch (code) {
    200 -> SUCCESS
    400 -> FAILED
    else -> UNKNOWN
}
```
```java
Status getStatus(int code) = switch (code) {
    case SUCCESS -> 200
    case FAILED -> 400
    else -> 0
}

int code = getStatus(SUCCESS)
// code is now 200
```


### Method pre-processing
```
Void allows you to merge an instruction with the return keyword. 
Therefore you don't need two extra lines to do a negated method guard.
```
```c#
// previously you had to use two lines of code to return
void handleCommand(Player p, String command) {
    if (!p.hasPermission("use")) {
        p.sendMessage("no perms")
        return
    }
    // handle the command
}
```
```java
// Void's syntax allows you to merge these two lines together
if (!p.hasPermission("use"))
    return p.sendMessage("no perms")
// note that handleCommand returns void, so there are no conflicts returning something.
// the return value of p.sendMessage (assuming it has one) is ignored
```


### Method post-processing
```
In Void, you can queue post tasks for the method, 
that are going to be executed, when the method returns.
This can be used to prevent duplicating instructions whenever returning.
```
```js
// prevously you had to do something like this
// as you can see you need to call guard.unlock() 3 times
void myThreadSafeMethod() {
    let guard = // get some lock for concurrency
    guard.lock()

    if (myObject.someError) {
        guard.unlock()
        return
    }

    if (myObject.someOtherError) {
        guard.unlock()
        return
    }

    myObject.doSomething()

    guard.unlock()
}
```
```
In Void, you can replace these duplicates using the "defer" keyword. 
Deferred instructions will be executed whenever the method returns.
```
```js
void myThreadSafeMethod() {
    let guard = // get some lock for concurrency
    guard.lock()
    defer guard.unlock()

    if (myObject.someError) 
        return

    if (myObject.someOtherError) 
        return

    myObject.doSomething()
}
```


### Conditional variables
```
Conditional variables are local variables that only exist in the scope of the condition. 
This prevents keeping unused object in the memory, and unnecessary variable name reservation.
```
```js
// previously you had to code something like this
let created = createFolder("myFolder")
if (!created)
    return error
```
```js
// Void allows you to simplify this code the following way
if (let created = createFolder("folder"); !created)
    return error
```
```
When checking the isntance of objects, in older code practices, 
you had to first check the instance, then manually cast the value to the new type.
```
```js
if (animal is Parrot) {
    let parrot = (Parrot) animal
    parrot.fly()
}
```
```
However this code requires us to write an extra line of code and manually cast the value.
```
```rust
if (animal is Parrot parrot) {
    parrot.fly()
}
```


### Labels
```
You can name certain parts of code in order to allow jumps in scopes and nested loops.
```
```rust
// you may label your outer loop in order to allow "break" or "continue" on it.
myLoop: 
for (let i in 1..10) {
    for (let j in 1..10) {
        println($"{i} {j}")
        if (j == 5) {
            break myLoop
        }
    }
}
```
```cpp
// you can put labels to non-blocks as well
// this example shows a loop jump to a section
hello:
doSomething()
if (condition)
    goto hello
```

### Multithreading
```
Void features an async value retrieval system. In other programming languages, 
you might have seen these ad promises, tasks or futures.
```
```js
Future<User> getUser() {
    return Future.completed(myUser)
}

let user = getUser().get()
```
```
Although Void lets you to explicitly declare future types, 
you should rather use the async/await syntax.
This automatically wraps the return type to be a Future, and calls get().
```
```js
async User getUser() {
    return myUser
}

let user = await getUser()
```
```
You can create threads as well and have full control over them.
```
```js
let thread = new Thread(||
    println("hello"))
    .setName("my-thread")
    .setPriority(0)
thread.start()
```


### JSON in code
```
Void has a built-in JSON serializer, which allows you to directly 
map Void objects to JSON and vice versa.
```
```rust
// object to string
let entity = @Json {
    entityId: 100,
    meta: {
        health: 20,
        food: 10,
        stamina: 3
    },
    position: {
        x: 200,
        y: 4
        z: -55
    }
}

let json = Json.serialize(entity)
println($"Data: {json}")

// string to object
let data = "{ \"name\": \"admin\", \"userId\": 12345 }"

struct User {
    String name
    int userId
}

let user = Json.deserialize<User>(data)
println($"Welcome, {user.name}")
```


### HTML in code
```
Void lets you have HTML code inside source code. 
By default, tags are mapped with Void's built-in tag system, however this can be extended.
```
```jsx
let page = @Html {
    <div class="container">
        <h1>Hello, World</h1>
    </div>
}
```


### Bytecode in code
```
Void features direct bytecode instructions to be placed inside the source code.
```
```rust
int getSomeMagicValue() {
    let magic = 30

    @Bytecode
    unsafe {
        ipush 100    // push 100 to the stack
        istore magic // store the value on the stack in the "magic" variable 
    }

    return magic
}

// the value of "test" will be 100
let test = getSomeMagicValue()
```


### Interaction with native code
```
Void allows you to call native library methods. 
It also has a framework that makes it possible to interace with Void from native context.
```
```java
// get the implementation of the method from native code
@Link("library.dll")
public native int multiply(int a, int b)

// call the native implementation from Void context
let result = multiply(2, 6)
println($"Result: {result}")
```
```java
// you can also link native methods of different signature

@Link("library.dll")
@NativeTarget("bar")
native void foo(@NativeParam("int") int a)
```
```java
// in case of having multiple native methods in a class, you should annotate the class instead

@Link("library.dll")
class MyNativeImplementation {
    native int foo()

    native void bar(float f)

    @NativeTarget("baz")
    native void something()
}
```


### Dynamic native implementation loading
```js
let library = new NativeLibrary()
    .target(typeof(object))

library.load()
```



### Creating an HTTP server
```
Void's built-in http module allows you to create efficient web servers with the express-js design.
```
```js
void main() {
    // create a new server instance which will take care of handling the request routes
    let server = new HttpServer()

    // create a GET request handler for the "/" route
    server.get("/", |req, res|
        // respond to the request with a plain text message
        res.send("Hello, World")
    )

    // start the web server and listen on port 80
    server.listen(80)
}
```
