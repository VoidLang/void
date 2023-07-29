package "util"

/**
 * Represents a container, which may or may not contain a value.
 * 
 * This allows you to safely retrieve values from methods.
 *
 * # Examples
 * ```
 * let element = list.get(0)
 *     .expect("No such index")
 * ```
 * 
 * @since 1.0
 */
public union Option<T> {
    /**
     * `Some` indicates, that the option has a value of type `T`.
     */
    Some(T),

    /**
     * `None` indicates, that the option is empty, thus does not contain a value.
     */
    None

    /**
     * Indicate, whether a value is present in the option.
     * 
     * @return `true` if this option is a `Some` value.
     */
    bool some() {
        return this is Some
    }

    /**
     * Indicate, whether the option is empty, and does not contain a value.
     * 
     * @return `true` if this option is a `None` value.
     */
    bool none() {
        return this is None
    }

    /**
     * Retrieve the contained value of this option. If no value is associated for the option,
     * the program panics with an error.
     * 
     * @return the value inside the option
     */
    T unwrap() = switch (this) {
        case Some(value) -> value
        case None -> panic("Called `unwrap()` on a `None` `Option` value")
    }

    /**
     * Retrieve the contained value of this option. If no value is associated for the option,
     * the default value is returned.
     * 
     * @return the value inside the option
     */
    T unwrapOr(T def) = switch (this) {
        case Some(value) -> value
        case None -> def
    }

    /**
     * Retrieve the contained value of this option. If no value is associated for the option,
     * the default value is supplied.
     * 
     * @return the value inside the option
     */
    T unwrapOrGet(T || supplier) = switch (this) {
        case Some(value) -> value
        case None -> supplier()
    }

    /**
     * Retrieve the contained value of this option. If no value is associated for the option,
     * the program panics with the specified error message.
     * 
     * @return the value inside the option
     */
    T expect(string msg) = switch (this) {
        case Some(value) -> value
        case None -> panic(msg)
    }

    /**
     * Map the contained value of this option to the type of `U` using the specified mapper.
     * If the option is empty, a `None` is returned.
     * 
     * @return an option of type `U`
     */
    Option<U> map<U>(U |T| mapper) = switch (this) {
        case Some(value) -> ?mapper(value)
        case None -> None
    }

    /**
     * Map the contained value of this option to the type of `U` using the specified mapper.
     * If the option is empty, a the default value is returned.
     * 
     * @return the mapped value or the default value
     */
    Option<U> mapOr(U |T| mapper, U def) = switch (this) {
        case Some(value) -> ?mapper(value)
        case None -> ?def
    }

    /**
     * Return `None` if this option is `None`. Call the `mapper` with the held value and return the result.
     * 
     * @param mapper - option mapper function
     * @return the map result or `None`
     */
    Option<U> flatMap<U>(Option<U> |T| mapper) = switch (this) {
        case Some(value) -> mapper(value)
        case None -> None
    }

    /**
     * Map the contained value of this option to the type of `U` using the specified mapper.
     * If the option is empty, a the default value is supplied.
     * 
     * @return the mapped value or the default value
     */
    Option<U> mapOrElse(U |T| mapper, U || def) = switch (this) {
        case Some(value) -> ?mapper(value)
        case None -> ?def()
    }

    /**
     * Call the specified callback if the option contains a value.
     */
    Option<T> inspect(|T| callback) {
        if (let Some(value) = this)
            callback(value)
    }

    /**
     * Transform the option to a result, that is `Ok`, if this option has a value, `Err` otherwise.
     * 
     * @param error the error to be given in case of `Err`
     * @return this option as a `Result`
     */
    Result<T, E> okOr<E>(E error) = switch (this) {
        case Some(value) -> Ok(value)
        case None -> Err(error)
    }

    /**
     * Transform the option to a result, that is `Ok`, if this option has a value, `Err` otherwise.
     * 
     * @param error the error to be supplied in case of `Err`
     * @return this option as a `Result`
     */
    Result<T, E> okOrElse<E>(E || error) = switch (this) {
        case Some(value) -> Ok(value)
        case None -> Err(error())
    }

    /**
     * Return `None` if this option is `None`, return `other` otherwise.
     * 
     * @param other the option to return if this option has a value
     * @return the other option or `None`
     */
    Option<U> and<U>(Option<U> other) = switch (this) {
        case Some(_) -> other
        case None -> None
    }

    /**
     * Return the option, if it contains a value, return `other` otherwise.
     * 
     * @param other - the other option to return if this option is empty
     * @return this option or the other option, if this is `None`
     */
    Option<T> or(Option<T> other) = switch (this) {
        case Some(_) -> this
        case None -> other
    }

    /**
     * Return the option, if it contains a value, return `other` otherwise.
     * 
     * @param other - the suppleir for other option to return if this option is empty
     * @return this option or the other option, if this is `None`
     */
    Option<T> orElse(Option<T> || other) = switch (this) {
        case Some(_) -> this
        case None -> other()
    }

    /**
     * Return `Some`, if exactly this or the specified option is `Some`, `None` otherwise.
     * 
     * @param other the other operand of the check
     * @return either this or the specified option if they match the filter, otherwise `None`
     */
    Option<T> xor(Option<T> other) = switch (this, other) {
        case Some(value), None -> this
        case None, Some(value) -> other
        default -> None
    }

    /**
     * Return `None` if this option is `None`. If this is `Some`, call the `predicate` and return
     * the contained value of the option, if the `predicate` passes. Return `None` otherwise.
     * 
     * @param predicate the function to test the contained value with
     * @return `None` if the contained value exists and did not pass the predicate, `this` option otherwise
     */
    Option<T> filter(bool |T| predicate) {
        if (let Some(value) = this && predicate(value))
            return this
        return None
    }

    /**
     * Zip this option with the specified option.
     * 
     * @param other the other option to zip with
     * @return a new option containing this and the other option or `None` if this option is empty
     */
    Option<(T, U)> zip(Option<U> other) = switch (this, other) {
        case Some(a), Some(b) -> Some((a, b))
        case None -> None
    }

    /**
     * Unzip this option of two tuple elements.
     * 
     * @return tuple of two options, if this option has two `Some` values, `None` otherwise.
     */
    (Option<T>, Option<U>) unzip() = switch (this) {
        case Some((a, b)) -> (Some(a), Some(b))
        case None -> (None, None)
    }
}
