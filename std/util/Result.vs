package "util"

/**
 * Represents a container, which includes either a value or an error 
 * if the value was unable to be retrieved.
 * 
 * # Examples
 * ```
 * let user = database.fetchUser("John Doe")
 *     .expect("Unable to fetch user.")
 * ```
 * 
 * @since 1.0
 */
public:
enum Result<T, E> {
    /**
     * `Ok` indicates, that the result was completed successfully.
     */
    Ok(T),

    /**
     * `Err` indicates, that an error occurred whilst completing.
     */
    Err(E)

    /**
     * Indicate, whether the result was successful and contains a value.
     * 
     * @return `true` if the result was successful
     */
    bool ok() {
        return this is Ok
    }

    /**
     * Indicate, whether the result was unsuccessful and contains an error.
     * 
     * @return `true` if the result was unsuccessful
     */
    bool err() {
        return this is Err
    }

    /**
     * Retrieve the contained value of this result wrapped into an option. 
     * If the result is failed, `None` is returned.
     */
    Option<T> value() = switch (this) {
        case Ok(value) -> ?value
        default -> Empty
    }

    /**
     * Retrieve the contained error of this result wrapped into an option. 
     * If the result is successful, `None` is returned.
     */
    Option<E> error() = switch (this) {
        case Err(error) -> ?error
        default -> Empty
    }

    /**
     * Retrieve the contained value of this error. If this result is failed,
     * the program panics with an error.
     * 
     * @return the value inside the result
     */
    T unwrap() = switch (this) {
        case Ok(value) -> value
        case Err(error) -> panic($"Called `unwrap()` on an `Err` `Result` value with: {error}")
    }

    /**
     * Retrieve the contained value of this result. If this result is failed,
     * the default value is returned.
     * 
     * @param def the default value to return if this result is `Err`
     * @return the value inside the result
     */
    T unwrapOr(T def) = switch (this) {
        case Ok(value) -> value
        case Err(_) -> def
    }

    /**
     * Retrieve the contained value of this result. If this result is failed,
     * the default value is supplied.
     * 
     * @param supplier the default value to be supplied if this result is `Err`
     * @return the value inside the result
     */
    T unwrapOrGet(T || supplier) = switch (this) {
        case Ok(value) -> value
        case Err(_) -> supplier()
    }

    /**
     * Retrieve the contained value of this result. If this result is failed,
     * the program panics with the specified error message.
     * 
     * @return the value inside the result
     */
    T expect(string msg) = switch (this) {
        case Ok(value) -> value
        case Err(_) -> panic(msg)
    }
}
