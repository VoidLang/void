void main() {
    let input = ["one", "12", "hello", "-7"]

    let result = input
        .stream()
        .filterMap(int::parse)
        .sort(|a, b| b - a)
        .collect()

    let largest = result
        .get(0)
        .unwrap()
        
    println($"Largest: {largest}")
}

