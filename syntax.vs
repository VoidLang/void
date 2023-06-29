// Void Expression Syntax


/**
 * variable declaration 
 */
<Type> <Name> ([= <Expression>] | !'(')

// a type follows a name, and after the name there is an equals sign, or not a '('
<QualifiedName> [<GenericArgumentList>] [<Array>] <Name> [= <Expression>]
int[] value
My.Document<Json>[] document


{
    // local declare
    let var
    (int, bool) var
    strong let var
    static let lol

    // local declare assign
    let var = 100
    (int, float) var = (1, 3.5F)
    strong let var = 100
    static (int, int) var = 200
    
    let (x, y) = desctructuredTuple
    let { code, msg } = desctructuredObject
    static let (x, y) = loller()
}
