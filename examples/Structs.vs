// structs are simplified value holders
// by default, unlike classes, structs are passed by value, not reference
// this way mutating struct references in an other context (eg. method) call,
// will take no effect on the original struct

// this is a normal struct
struct Person {
    string name
    uint age
}

// this is a tuple struct with named members
struct Point(int x, int y)

// this is a tuple struct with unnamed members
struct Matrix(float, float, float, float)

void main() {
    // create a new person using the initializer pattern
    let person = new Person { name: "John Doe", age: 24 }

    // create a new person with a simplified initializer
    let name = "John Doe"
    let age = 24
    // as you can see, the variable name and the field name are equal
    // this way we don't have to explicitly write eg. name: name
    let person = new Person { name, age }

    // pass the person struct to a function that mutates the value of it
    modifyPerson(person)
    // in this debug, the value of name will still be "John Doe"
    // as structs are passed by value, not reference
    println($"Hello, {person.name}")

    
    // you can initialize tuple structs with two syntax
    // by default you should use the constructor initializator
    let point = new Point(2, 3)

    // however, you can initialize tuple structs with the initializer pattern,
    // if they have named members
    let point = new Point { x: 2, y: 3 }

    // you can destructure the members of a named struct
    let { x, y } = point
    println($"point: {x}, {y}")
    
    // you can also use the following syntax on tuples
    let (x, y) = point


    // unnamed tuple structs can be only initialized using this syntax
    let matrix = new Matrix(1.2, 2.5, 7.3, 4.6)
    println($"first member: {matrix.0}")
}

// modify the person struct that is passed by value
// the modification will be only applied in the method's context
void modifyPerson(Person person) {
    person.name = "Classified"
    // prints "Classified" to the console
    println(person.name)
}
