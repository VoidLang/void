package "async"

/**
 * Represents an union of future states. Initially, the Future is `Empty`, which indicates, that it is not yet completed.
 * If the future completes successfully, its state is set to `Completed(T)`, which contains the value of the completion.
 * If an error occurrs whilst completing, the future state is set to `Failed(Error)`, which contains the occurred error.
 */
public:
union FutureState<T> {
    /**
     * The `Empty` state indicates, that the future is currently empty, and is yet to be completed.
     */
    Empty,

    /**
     * The `Completed` state indicates, that the future has been completed sucessfully, and it helds the result value.
     */
    Completed(T),

    /**
     * The `Failed` state indicates, that the future has failed completing, and it helds the completion error.
     */
    Failed(Error)
}

/**
 * Represents an error, that is thrown, if a `Future` has completed
 * unsuccessfully with an exception. The original cause can be retrieved
 * with `#getCause()`.
 */
public:
class FutureExecutionError : Error {
    /**
     * Initialize the future execution error.
     * 
     * @param error the error occurred whilst retrieving a value for the vuture
     */
    FutureExecutionError(Error error) {
        super(error)
    }
}

/**
 * Represents an error, that is thrown, if a `Future` did not complete in fime.
 */
public:
class FutureTimeoutError : Error {
    /**
     * Initialize the future timeout error.
     * 
     * @param timeout the time that the future retrieving exceeded
     */
    FutureTimeoutExcpetion(public long timeout) {
        super("Timeout of " + timeout + " ms exceeded.")
    }
}

/**
 * Represents a callback, which can be completed or failed either synchronously or asynhronously.
 * A future cam be completed with a certain <T> object, or can be failed by an exception happening
 * whilst executing a future task.
 * 
 * This class also contains useful methods to attach callbacks for completion or failure events,
 * and to create new future objects based on this instance.
 * 
 * Error recovery is also possible using the `#fallback(T)` and `#fallback(T||)}` methods.
 * The syntax encourages chaining, therefore less code is needed to handle certains tasks and events.
 *
 * # Examples
 * ```
 * async User getUser(string id) {
 *     return myUser
 * }
 * 
 * let user = await getUser("example-001")
 * ```
 * 
 * @param <T> the type of the returned value of the completed future
 * 
 * @author AdvancedAntiSkid
 * @author MrGazdag
 * 
 * @since 1.0
 */
public class Future<T> {
private:
    /**
     * The list of the future completion handlers.
     */
    List<|T|> completionCallbacks

    /**
     * The list of the future failure handlers.
     */
    List<|Error|> errorCallbacks

    /**
     * The current state of the future. If the future is not yet completed, it is `Empty`. If it has been completed successfully,
     * the state changes to `Completed`. If the future failed completing, it is set to `Error`.
     */
    FutureState<T> state

    /**
     * The lock that is used for blocking the awaiting thread, which waits for the future to retrieve a value.
     */
    Lock lock

public:
    /**
     * Create a new, uncompleted, empty future.
     */
    Future() {
    }

    /**
     * Block the current thread and wait for the future completion to happen.
     * After the completion, the result T object is returned.
     * 
     * If the future completes with an exception, an error is returned.
     * 
     * # Examples
     * ```
     * let result = await getUserAsync("John Doe")
     * ```
     * This code will block until the `getUserAsync()` retrieves a value.
     * 
     * @return the completion value
     */
    Result<T, Error> get() {
        return blockAndGet(0, Empty)
    }

    /**
     * Block the current thread and wait for the future completion to happen.
     * After the completion, the result T object is returned.
     * 
     * If the future completes with an exception, an error is returned.
     * 
     * If the blocking exceeds the specified time interval, a FutureTimeoutExcpetion is retrieved.
     * If the timeout is 0, the method wil lblock indefinitely.
     * 
     * # Examples
     * ```
     * let result = await getUserById("0000-1111-2222-3333")
     * ```
     * An error is retrieved if the `getUserById()` does not respond within 3 seconds.
     * 
     * @param timeout the maximum time interval to wait for the value, it this exceeds, a timeout error is returned
     * @return the completion value
     */
    Result<T, Error> get(long timeout) {
        return blockAndGet(timeout, Empty)
    }

    /**
     * Block the current thread and wait for the future completion to happen.
     * After the completion, the result T object is returned.
     * 
     * If the future completes with an exception, the default value is returned.
     * 
     * Examples
     * ```
     * let result = findBookByTitle("The Magic Tree")
     *     .getOr("Unknown book")
     * ```
     * The result will be "Unknown book", if `findBookByTitle()` fails to complete.
     * 
     * @param fallback the fallback value to be returned if the future execution fails
     * @return the completion value
     */
    T getOr(T fallback) {
        return blockAndGet(0, ?fallback)
    }

    /**
     * Block the current thread and wait for the future completion to happen.
     * After the completion, the result T object is returned.
     * 
     * If the future completes with an exception, the default value from the fallback supplier is returned.
     * 
     * # Examples
     * ```
     * let result = getProfile(287258735465)
     *     .getOr(|| callOnlyIfFailed())
     * ```
     * The default value supplier is be called, if the `getProfile()` fails.
     * 
     * @param fallback the fallback value supplier to be called if the future execution fails
     * @return the completion value
     */
    T getOr(T || fallback) {
        return blockAndGet(0, ?fallback())
    }

    /**
     * Block the current thread and wait for the future completion to happen.
     * After the completion, the result T object is returned.
     * 
     * If the future completes with an exception, the default value is returned.
     * 
     * If the blocking exceeds the specified time interval, a FutureTimeoutExcpetion is retrieved.
     * If the timeout is 0, the method wil lblock indefinitely.
     * 
     * # Examples
     * ```
     * let result = getProfile("test").getOr(1000, fallbackProfile)
     * ```
     * 
     * @param fallback the fallback value to be returned if the future execution fails or the timeout is exceeded
     * @return the completion value
     */
    Result<T, Error> getOr(long timeout, T fallback) {
        return blockAndGet(timeout, ?fallback)
    }

    /**
     * Block the current thread and wait for the future completion to happen.
     * After the completion, the result T object is returned.
     * 
     * If the future completes with an exception, the default value is returned.
     * 
     * If the blocking exceeds the specified time interval, a FutureTimeoutExcpetion is retrieved.
     * If the timeout is 0, the method wil lblock indefinitely.
     * 
     * # Examples
     * ```
     * let result = getProfile("test").getOr(1000, || fallbackProfile)
     * ```
     * 
     * @param fallback the fallback value supplier to be called if the future execution fails or the timeout is exceeded
     * @return the completion value
     */
    Result<T, Error> getOr(long timeout, T || fallback) {
        return blockAndGet(timeout, ?fallback())
    }

    /**
     * Get instantly the completion value, or the default value, if the future hasn't been completed yet.
     * 
     * # Examples
     * ```
     * let result = getProfile("test").getNow(fallbackProfile)
     * ```
     * 
     * @param fallback default value to return if the future isn't completed
     * @return the completion value or the default value
     */
    Option<T> getNow(T fallback) = switch (state) {
        case Completed(value) -> Ok(value)
        default -> Empty
    }

    /**
     * Block the current thread and wait for the future completion to happen.
     * After the completion happened, the completion result `T` object is returned.
     * 
     * If the future completes with an exception, a `FutureExecutionException` is retrieved,
     * or the `defaultValue` is returned if present.
     * The actual error that made the future fail can be obtained using `FutureExecutionException#cause()`.
     * 
     * If the request has a timeout and exceeds the given time interval, a `FutureTimeoutException` is retrieved.
     * If the timeout is 0, the method will block indefinitely resulting the future have an infinite timeout.
     * 
     * @param timeout the maximum time interval to wait for the value, if this is exceeded, then a `FutureTimeoutException` is retrieved.
     * @param defaultValue the default value which is returned on a completion failure, if it is empty, the error is retrieved instead
     * @return the completion value or a default value,
     * or FutureTimeoutException, if the timeout interval has exceeded,
     * or FutureExecutionException, if the completion failed and a default value was not specified
     *
     * @see #get()
     * @see #get(long)
     * @see #getOr(T)
     * @see #getOr(long, T)
     */
    private Result<T, Error> blockAndGet<E>(long timeout, T? defaultValue) {
        // check if the future has been already completed
        if (let Completed(value) = state) 
            return Ok(value)

        // check if the future has been failed
        else if (let Failed(error) = state) {
            // retrieve the default value if it is specified
            returnif defaultValue
            // there is no default value set, throw a completion error
            return Err(new FutureTimeoutError(error))
        }

        // the future hasn't been completed yet
        // block the current thread until the future receives a completion value
        synchronized (lock)
            lock.freeze(timeout)

        // the lock has been released, which means that either the timeout has been exceded, 
        // or the future state has been changed
        return switch (state) {
            // check if the future has still not been completed, after the lock has been released, which
            // means that the future exceeded the specified timeout limit
            case Empty -> Err(FutureTimeoutError(timeout))

            // check if the future has been completed successfully
            case Completed(value) -> Ok(value)

            // check if the future has failed which trying to complete
            case Failed(error) -> Err(error)
        }
    }

    /**
     * Complete the future successfully with the specified value.
     * Call all the callbacks waiting on the completion of this future.
     * 
     * If this future was already completed (either successfully or unsuccessfully), this method does nothing.
     * 
     * # Examples
     * ```
     * Future<string> getUsername() {
     *     let future = new Future<string>()
     *     Task.delay(1000, || {
     *         future.complete("John2000")
     *     })
     *     return future
     * }
     * 
     * let username = await getUsername().unwrap()
     * ```
     * `getUsername()` will block until the future completes with a value
     * 
     * @param value completion value
     * @return true if the future as completed with the value, false otherwise
     */
    bool complete(T value) {
        // check if the future has been already completed
        if (!(state is Empty))
            return false
        // update the future state and wake up the awaiting thread
        synchronized (lock) {
            state = Completed(value)
            lock.unlock()
        }
        // call the completion handler callbacks
        handleCompleted(value)
        return true
    }

    /**
     * Call the future successful completion handlers.
     */
    private void handleCompleted(T value) = for (|T| handler in completionCallbacks) {
        handler.accept(value)
    }

    /**
     * Fail the future completion with the specified error.
     * Call all callbacks waiting on the failure of this future,
     * 
     * If this future was already completed (either successfully or unsuccessfully), this method does nothing.
     * 
     * # Examples
     * ```
     * Future<string> getUsername() {
     *     let future = new Future<string>()
     *     Task.delay(1000, || {
     *         future.fail(new Exception("Unable to get username"))
     *     })
     *     return future
     * }
     * 
     * let username = await getUsername().unwrapOr("No such username")
     * assert username == "No such username"
     ```
     * `getUsername()` will block until the future completes with a value
     * 
     * @param error the error occurred whilst completing
     * @return true if the future was completed with an error, false otherwise
     */
    bool fail(Error error) {
        // check if the future has been already completed
        if (!(state is Empty))
            return false
        // update the future state and wake up the awaiting thread
        synchronized (lock) {
            state = Failed(error)
            lock.unlock()
        }
        // call the failure handler callbacks
        handleFailed(value)
        return true
    }

    /**
     * Call the future failed completion handlers.
     */
    private void handleFailed(Error error) {
        for (|T| handler in completionCallbacks) 
            handler.accept(value)
    }

    /**
     * Register a completion handler to be called when the future completes without an error.
     * 
     * If the future completes with an exception, the specified callback will not be called.
     * If you wist to handle exceptions as well, use `result(|T, Error|)` or `except(|Error|)`.
     * 
     * If the future is already completed successfully, the callback is called immediately with the completion value. 
     * If the future is already failed with an exception, the callback will not be called.
     * 
     * # Examples
     * ```
     * getProfile("test").then(|e| {
     *     println($"Welcome, {e.name}")
     * })
     * ```
     * 
     * @param callback the successful completion handler
     * @return this future
     */
    Future<T> then(|T| callback) = synchronized (lock) {
        // call the callback if the future has been already completed
        if (let Completed(value) = state)
            callback(value)
        // register the completion callback if the future hasn't been completed yet
        else if (let Empty = state)
            completionCallbacks.add(callback)
    }

    /**
     * Register a completion handler to be called when the future completes without an error.
     * 
     * If the future completes with an exception, the specified callback will not be called.
     * If you wist to handle exceptions as well, use `result(|T, Error|)` or `except(|Error|)`.
     * 
     * If the future is already completed successfully, the callback is called immediately with the completion value. 
     * If the future is already failed with an exception, the callback will not be called.
     * 
     * If the completion handler callback fails, this future will be failed with the thrown error.
     * 
     * # Examples
     * ```
     * getProfile("test").then(|e| {
     *     return e.tryUpdateName("New Name")
     * })
     * ```
     * 
     * @param callback the successful completion handler
     * @return this future
     */
    Future<T> tryThen(Result<?, Error> |T| callback) = synchronized (lock) {
        // call the callback if the future has been already completed
        if (let Completed(value) = state) {
            let result = callback(value)
            if (let Err(error) = result)
                fail(error)
        }

        // register the completion callback if the future hasn't been completed yet
        else if (let Empty = state) {
            completionCallbacks.add(|value| {
                let result = callback(value)
                if (let Err(error) = result)
                    fail(error)
            })
        }
    }

    /**
     * Register an asynchronous completion handler to be called when the future completes without an error.
     *
     * If the future completes with an exception, the specified action will not be called.
     * If you wist to handle exceptions as well, use `result(|T, Error|)` or `except(|Error|)`.
     *
     * If the future is already completed successfully, the action is called immediately with the completion value. 
     * If the future is already failed with an exception, the action will not be called.
     * 
     * # Examples
     * ```
     * getProfile("test").then(|e| {
     *     println($"Welcome, {e.name}")
     * })
     * ```
     *
     * @param action the successful completion handler to be called asynchronously
     * @return this future
     */
    Future<T> thenAsync(|T| action) = synchronized (lock) {
        // call the callback if the future has been already completed
        if (let Completed(value) = state)
            executeLockedAsync(|| callback(value))
        // register the completion callback if the future hasn't been completed yet
        else if (let Empty = state)
            completionCallbacks.add(|value| executeLockedAsync(|| callback(value))) 
    }

    /**
     * Create a new future that will transform the value to a new future, using the specified transformer.
     * 
     * After this future completes, the result is passed to the specified transformer.
     * The output of the transformer will be the input of the new future.
     *
     * If this future completes with an exception, the new future will be completed with the same exception.
     * 
     * If the current future is already completed successfully, the transformer will be called
     * immediately, and a completed future will be returned.
     *
     * # Examples
     * ```
     * let balance = database.getBalance("John Doe")
     *     .transform(|x| x.into())
     *     .get()
     * ```
     * 
     * @param transformer the function that transforms the value from T to U type
     * @return a new future of the U type
     */
    Future<U> transform<U>(U |T| transformer) = synchronized (lock) {
        // check if the future has been already completed either successfully or unsuccessfully 
        switch (state) {
            // let the transformer transform the successful completion value
            case Completed(value) -> return completed(transformer(value))

            // return a failed future of the parent's error
            case Failed(error) -> return failed(error)
        }

        // the future hasn't been completed yet, create a new Future,
        // that will try to transform the value once it is completed
        let future = new Future<U>()
        completionCallbacks.add(|value| {
            // let the transformer transform the value when it arrives
            future.complete(transformer(value))
        })

        // proxy the error handling of this future to the new future
        errorCallbacks.add(future::fail)
        return future
    }

    /**
     * Create a new future that will try transform the value to a new future, using the specified transformer.
     * If the transformer is unable to transform the completion value, the new future is failed with an error.
     * 
     * After this future completes, the result is passed to the specified transformer.
     * The output of the transformer will be the input of the new future.
     *
     * If this future completes with an exception, the new future will be completed with the same exception.
     * 
     * If the current future is already completed successfully, the transformer will be called
     * immediately, and a completed future will be returned.
     *
     * # Examples
     * ```
     * let balance = database.getBalance("John Doe")
     *     .transform(|x| x.into())
     *     .get()
     * ```
     * 
     * @param transformer the function that transforms the value from T to U type
     * @return a new future of the U type
     */
    Future<U> tryTransform<U>(Result<U, Error> |T| transformer) = synchronized (lock) {
        // check if the future has been already completed either successfully or unsuccessfully 
        switch (state) {
            // let the transformer transform the successful completion value
            case Completed(value) -> return completed(transformer(value))

            // return a failed future of the parent's error
            case Failed(error) -> return failed(error)
        }

        // the future hasn't been completed yet, create a new Future,
        // that will try to transform the value once it is completed
        let future = new Future<U>()
        completionCallbacks.add(|value| {
            // let the transformer transform the value when it arrives
            let result = transformer(value)
            // complete the future successfully if the transformer did succeed
            if (let Ok(val) = result)
                future.complete(val)
            // fail the future if the transformed did fail
            else if (let Err(err) = result)
                future.fail(err)
        })

        // proxy the error handling of this future to the new future
        errorCallbacks.add(future::fail)
        return future
    }

    /**
     * Create a new future that does not care about the completion value, it only check for successful or failed completions.
     * 
     * After this future completes, an empty value is passed to the new future.
     *
     * If this future completes with an exception, the new future will be completed with the same exception.
     * If the current future is already completed successfully, a completed future will be returned with the value of an empty tuple.
     * 
     * # Examples
     * ```
     * database.getBalance("John Doe")
     *     .callback()
     *     .then(|| println("Balance has been found"))
     * ```
     * 
     * @return new future of an empty tuple type
     */
    Future<void> callback() = synchronized (lock) {
        // check if the future has been already completed either successfully or unsuccessfully 
        switch (state) {
            // let the transformer transform the successful completion value
            case Completed(value) -> return completed(default)

            // return a failed future of the parent's error
            case Failed(error) -> return failed(error)
        }

        // the future hasn't been completed yet, create a new Future,
        // that will try to transform the value once it is completed
        let future = new Future<U>()
        completionCallbacks.add(|value| {
            future.complete(default)
        })

        // proxy the error handling of this future to the new future
        errorCallbacks.add(future::fail)
        return future
    }

    /**
     * Register a failure handler to be called when the future completes with an error.
     *
     * If the future completes successfully, the specified callback will not be called.
     * If you wish to handle successful completions as well, use `result(|T, Error|)` or `then(|T|)`.
     * 
     * If the future is already completed unsuccessfully, the callback will be called immediately with the completion error.
     * If the future has completed with a result, the callback will not be called.
     *
     * # Examples
     * ```
     * database.getName("user-0001")
     *     .then(|name| println($"found name: {name}"))
     * ```
     * 
     * @param callback a failed completion handler
     * @return this future
     */
    Future<T> except(|Error| callback) = synchronized (lock) {
        // call the callback if the future has been already completed
        if (let Failed(error) = state)
            callback(error)
        // register the failure callback if the future hasn't been completed yet
        else if (let Empty = state)
            errorCallbacks.add(callback)
    }

    /**
     * Register an asynchronous failure handler to be called when the future completes with an error.
     *
     * If the future completes successfully, the specified action will not be called.
     * If you wish to handle successful completions as well, use `result(|T, Error|)` or `then(|T|)`.
     * 
     * If the future is already completed unsuccessfully, the action will be called immediately with the completion error.
     * If the future has completed with a result, the action will not be called.
     * 
     * # Examples
     * ```
     * database.getName("user-0001")
     *     .then(|name| println($"found name: {name}"))
     * ```
     * 
     * @param action an async failed completion handler
     */
    Future<T> exceptAsync(|Error| action) = synchronized (lock) {
        // call the callback if the future has been already completed
        if (let Failed(error) = state)
            executeLockedAsync(|| callback(error))
        // register the failure callback if the future hasn't been completed yet
        else if (let Empty = state)
            errorCallbacks.add(|error| executeLockedAsync(|| callback(value)))
    }

    /**
     * Create a new future that will transform the old future's exception to a fallback value.
     *
     * If this future completes successfully, the future is completed with the same exact value.
     *
     * If this future fails with an exception, the transformer is called to try to trasform the exception 
     * to a fallback value. Finally, the new future is completed with this value.
     * 
     * If the transformer's result is a constant, consider using `fallback(T)` instead.
     * 
     * # Examples
     * ```
     * database.getName("user-0001")
     *     .fallback(|error| "fallback name")
     * ```
     * 
     * @param transformer the function that transforms an error to T
     * @return a new future 
     */
    Future<T> fallback(T |Error| transformer) = synchronized (lock) {
        // check if the future has been already completed either successfully or unsuccessfully 
        switch (state) {
            // let the transformer transform the successful completion value
            case Completed(value) -> return completed(value)

            // return a failed future of the parent's error
            case Failed(error) -> return completed(transformer(error))
        }

        // the future hasn't been completed yet, create a new Future,
        // that will try to transform the value once it is completed
        let future = new Future<U>()
        completionCallbacks.add(|value| {
            // let the transformer transform the value when it arrives
            future.complete(transformer(value))
        })

        // proxy the error handling of this future to the new future
        errorCallbacks.add(future::fail)
        return future
    }

    Future<T> tryFallback(Result<T, Error> |Error| transformer) = synchronized (lock) {
        // check if the future has been already completed either successfully or unsuccessfully 
        switch (state) {
            // let the transformer transform the successful completion value
            case Completed(value) -> return completed(value)

            // return a failed future of the parent's error
            case Failed(error) -> {
                // let the transformer try to transform the completion error
                let result = transformer(error)
                // handle successful fallback transforming
                if (let Ok(value) = result)
                    return completed(value)
                // unable to transform error, retrieve the transforming error
                else if (let Err(err) = result)
                    return failed(err)
            }
        }

        // the future hasn't been completed yet, create a new Future,
        // that will try to transform the value once it is completed
        let future = new Future<U>()
        completionCallbacks.add(|value| {
            // let the transformer transform the value when it arrives
            let result = transformer(value)
            // complete the future successfully if the transformer did succeed
            if (let Ok(val) = result)
                future.complete(val)
            // fail the future if the transformed did fail
            else if (let Err(err) = result)
                future.fail(err)
        })

        // proxy the error handling of this future to the new future
        errorCallbacks.add(future::fail)
        return future
    }

    /**
     * Create a new future that will complete with the fallback value if this future fails.
     *
     * If this future completes successfully, the new future will be completed with the same exact value.
     *
     * If this future fails with an exception, the fallback value will be used to complete the new future,
     * This can be used for error recovery, or to produce a fallback object, that will be returned upon 
     * unsuccessful completion.
     * 
     * If the fallback object is not a constant, consider using `fallback(|T|)` instead.
     * 
     * # Examples
     * ```
     * database.getName("user-0001")
     *     .fallback("fallback name")
     * ```
     *
     * @param fallback the value used if an exception occurs
     * @return a new future
     */
    Future<T> fallback(T fallback) = synchronized (lock) {
        // check if the future has been already completed either successfully or unsuccessfully 
        switch (state) {
            // let the transformer transform the successful completion value
            case Completed(value) -> return completed(value)

            // return a failed future of the parent's error
            case Failed(error) -> return completed(fallback)
        }

        // the future hasn't been completed yet, create a new Future,
        // that will try to transform the value once it is completed
        let future = new Future<U>()
        completionCallbacks.add(future::complete)

        // proxy the error handling of this future to the new future
        errorCallbacks.add(|err| future.complete(fallback))
        return future
    }

    /**
     * Register a special handler, that listens to both successful and unsuccessful completions.
     *
     * After a successful completion, the specified callback is called with `Completed(T)`.
     * 
     * If the future completes with an exception, the callback is called with `Failed(Error)`. 
     * 
     * If you wish to determine if the completion was successful, consider pattern matching the result state. 
     * 
     * If the future is already completed, the callback is called immediately
     * with the completed value or error.
     * 
     * # Examples
     * ```
     * future.result(|state| {
     *     if (let Completed(value) = state) { 
     *         println($"Completed result: {value}")
     *     } else if (let Failed(error) = state) {
     *         println($"Unable to fetch result: {error}")   
     *     }
     * })
     * ```
     * 
     * @param callback future state change callback
     * @return this future
     */
    Future<T> result(|FutureState| callback) = synchronized (lock) {
        // call the callback if the future is already completed
        if (!(state is Empty)) { 
            callback(state)
        } else {
            // register a completion and a failure handler if the future is not yet completed
            completionCallbacks.add(|value| callback(state))
            errorCallbacks.add(|error| callback(state))
        }
        return this
    }

    /**
     * Register a special handler, that listens to both successful and unsuccessful completions.
     * Use the transformer to create a new future using the completion value and error.
     * 
     * After a successful completion, the specified callback is called with `Completed(T)`.
     * 
     * If the future completes with an exception, the callback is called with `Failed(Error)`. 
     * 
     * If you wish to determine if the completion was successful, consider pattern matching the result state. 
     * 
     * If the future is already completed, the callback is called immediately
     * with the completed value or error.
     * 
     * # Examples
     * ```
     * future.result(|state| {
     *     if (let Completed(value) = state) { 
     *         println($"Completed result: {value}")
     *         return value
     *     } else if (let Failed(error) = state) {
     *         println($"Unable to fetch result: {error}")
     *         return getMyFallbackValue()
     *     }
     * })
     * ```
     *
     * @param transformer the future value transformer
     * @return a new future of type U
     */
    Future<U> result<U>(U |FutureState| transformer) = synchronized (lock) {

    }


    Future<U> tryResult<U>(Result<U, Error> |FutureState| transformer) = synchronized (lock) {

    }

    /**
     * Create a new future, that will be completed unsuccessfully using a `FutureTimeoutException`
     * if the specified time has elapsed without a response. 
     * 
     * If this future completes before the timeout has passed, 
     * the new future is completed with this future's result value.
     * 
     * If this future completes unsuccessfully, the new future is completed with the same exception.
     * 
     * # Examples
     * ```
     * getProfile("test")
     *     .timeout(1000)
     *     .get()
     * ```
     *
     * @param timeout the time to wait (in milliseconds) until a `FutureTimeoutException` is thrown.
     * @return a new Future
     */
    Future<T> timeout(long timeout) = synchronized (lock) {
        // check if the future has been already completed either successfully or unsuccessfully 
        switch (state) {
            // let the transformer transform the successful completion value
            case Completed(value) -> return completed(value)

            // return a failed future of the parent's error
            case Failed(error) -> return failed(error)
        }
        // create a new future that is failed if the execution exceeds the specified timeout
        let future = new Future<T>()
        // create a new task that to
        let task = new Task()
        // proxy the completion handler to the new future and kill the timeout task
        completionCallbacks.add(|value| {
            future.complete(value)
            task.kill()
        })
        // proxy the error handler to the new future and kill the timeout task
        errorCallbacks.add(|error| {
            future.fail(error)
            task.kill()
        })
        // fail the future if the completion did not arrive in time
        task.delay(|| {
            future.fail(new FutureTimeoutError(timeout))
        }, timeout)
    }

    /**
     * Indicate, whether the future has been completed either successfully or unsuccessfully.
     * 
     * # Examples
     * ```
     * let future = Future.completed("test")
     * assert future.done() == true
     * 
     * let future = Future.failed(new Exception("Something went wrong"))
     * assert future.completed() == true
     * ```
     * 
     * @return `true` if this future has already completed, `false` otherwise
     * @see #completed()
     * @see #failed()
     * @see #Empty
     */
    bool done() = switch(state) {
        case Completed, Failed -> true
        default -> false
    }

    /**
     * Indicate, whether the future has been completed successfully.
     * 
     * # Examples
     * ```
     * let future = Future.completed("test")
     * assert future.completed() == true
     * 
     * let future = Future.failed(new Exception("Something went wrong"))
     * assert future.completed() == false
     * ```
     * 
     * @return `true` if this future has already completed successfully, `false` otherwise
     * @see #done()
     * @see #failed()
     * @see #Empty
     */
    bool completed() {
        return state is Completed
    }

    /**
     * Indicate, whether the future was completed unsuccessfully.
     * If the future hasn't been completed yet, this method returns false.
     *
     * # Examples
     * ```
     * let future = Future.completed("test")
     * assert future.failed() == false
     * 
     * let future = Future.failed(new Exception("Something went wrong"))
     * assert future.failed() == true
     * ```
     * 
     * @return `true` if the completion was unsuccessful, `false` otherwise
     * @see #done()
     * @see #completed()
     * @see #Empty
     */
    bool failed() {
        return state is Failed
    }

    /**
     * Indicate, whether the future hasn't been completed yet neither successfully or unsuccessfully.
     * 
     * # Examples
     * ```
     * let future = Future.completed("test")
     * assert future.failed() == false
     * 
     * let future = Future.failed(new Exception("Something went wrong"))
     * assert future.failed() == false
     * ```
     * 
     * @return `true` if the future hasn't completed yet, `false` otherwise
     * @see #done()
     * @see #completed()
     * @see #failed()
     */
    bool Empty {
        return state is Empty
    }

    /**
     * Create a new future, that is completed initially using the specified value.
     * 
     * # Examples
     * ```
     * Future<int> getBalance(string user) {
     *     return Future.completed(1000)
     * }
     * let balance = await getBalance().unwrap()
     * ```
     * `getBalance()` does not block here, because the future immediately completes with a value
     * 
     * @param value the completion result
     * @return a new completed future
     */
    static Future<T> completed<T>(T value) {
        // create a new empty future
        let future = new Future<T>()
        // mark the future as completed
        future.state = Completed(value)
        return future
    }

    /**
     * Create a new future, that is completed without a specified value.
     * 
     * # Examples
     * ```
     * Future<void> disconnect() {
     *     sendDisconenctPacket()
     *     closeSocket()
     *     return Future.completed()
     * }
     * 
     * disconnect().then(|| {
     *     println("disconnected from the server")
     * })
     * ```
     * 
     * @return a new completed future
     */
    static Future<void> completed() {
        // create a new empty future
        let future = new Future<void>()
        // mark the future as completed
        future.state = Completed(default)
        return future
    }

    /**
     * Create a new future, that is completed initially using the specified value supplier.
     * 
     * # Examples
     * ```
     * Future<int> getBalance(string user) {
     *     return Future.completed(|| 1000)
     * }
     * let balance = await getBalance("test").unwrap()
     * ```
     * 
     * @param supplier the completion result supplier
     * @return a new completed future
     */
    static Future<T> completed(T || supplier) {
        // create a new empty future
        let future = new Future<void>()
        // mark the future as completed
        future.state = Completed(supplier())
        return future
    }

    /**
     * Create a new future, that is failed initially using the specified error.
     * 
     * # Examples
     * ```
     * Future<int> getBalance(string user) {
     *     return Future.failed(new Exception("Unable to get balance"))
     * }
     * let balance = await getBalance("test").unwrapOr(-1)
     * assert balance == -1
     * ```
     * 
     * @param error the completion error
     * @return a new, failed Future
     */
    static Future<T> failed<T>(Error error) {
        // create a new empty future
        let future = new Future<void>()
        // mark the future as failed
        future.state = Failed(error)
        return future
    }

    /**
     * Create a new future, that will be completed automatically on a different thread using the specified value.
     * 
     * Note that if the new future is completed faster, than the current one is able to append any callbacks on it,
     * then some callbacks might be executed on the current thread.
     * Therefore, make sure to register the callbacks to this future first.
     * 
     * If the result object is not a constant, consider using `#completeAsync(T||)` instead,
     * as it does allow dynamic object creation.
     * 
     * # Examples
     * ```
     * Future<string> getBalance(string user) {
     *     return Future.completeAsync(user)
     * }
     * 
     * getBalance("test").then(|balance| {
     *     println($"Got balance async {balance}")
     * })
     * ```
     *
     * @param result the value that is used to complete the future with
     * @param task the executor used to complete the future on
     * @return a new Future
     */
    static Future<T> completeAsync<T>(T result, Task task) {
        // create a new empty future to complete asynchronously
        let future = new Future<T>()
        // complete the future using the specified task
        task.run(|| {
            future.complete(result)
        })
    }

    /**
     * Create a new future, that will be completed automatically on a different thread using the specified value.
     * 
     * Note that if the new future is completed faster, than the current one is able to append any callbacks on it,
     * then some callbacks might be executed on the current thread.
     * Therefore, make sure to register the callbacks to this future first.
     * 
     * If the result object is not a constant, consider using `#completeAsync(T||)` instead,
     * as it does allow dynamic object creation.
     * 
     * # Examples
     * ```
     * Future<string> getBalance(string user) {
     *     return Future.completeAsync(user)
     * }
     * 
     * getBalance("test").then(|balance| {
     *     println($"Got balance async {balance}")
     * })
     * ```
     *
     * @param result the value that is used to complete the future with
     * @param task the executor used to complete the future on
     * @return a new Future
     */
    static Future<T> completeAsync<T>(T || supplier, Task task) {
        // create a new empty future to complete asynchronously
        let future = new Future<T>()
        // complete the future using the specified task
        task.run(|| {
            future.complete(supplier())
        })
    }

    /**
     * Create a new future, that will be completed automatically on a different thread using the specified value.
     * 
     * Note that if the new future is completed faster, than the current one is able to append any callbacks on it,
     * then some callbacks might be executed on the current thread.
     * Therefore, make sure to register the callbacks to this future first.
     * 
     * If the result object is not a constant, consider using `#completeAsync(T||)` instead,
     * as it does allow dynamic object creation.
     * 
     * # Examples
     * ```
     * Future<string> getBalance(string user) {
     *     return Future.completeAsync(user)
     * }
     * 
     * getBalance("test").then(|balance| {
     *     println($"Got balance async {balance}")
     * })
     * ```
     *
     * @param result the value that is used to complete the future with
     * @return a new future
     */
    static Future<T> completeAsync<T>(T result) {
        // create a new empty future to complete asynchronously
        let future = new Future<T>()
        // complete the future using the specified task
        Task.run(|| {
            future.complete(result)
        })
    }

    /**
     * Create a new future, that will be completed automatically on a different thread using the specified value.
     * 
     * Note that if the new future is completed faster, than the current one is able to append any callbacks on it,
     * then some callbacks might be executed on the current thread.
     * Therefore, make sure to register the callbacks to this future first.
     * 
     * If the result object is a constant, consider using `#completeAsync(T)` instead,
     * as it does not require allocating a supplier.
     * 
     * # Examples
     * ```
     * Future<string> getBalance(string user) {
     *     return Future.completeAsync(|| getBalanceSync(user))
     * }
     * 
     * getBalance("test").then(|balance| {
     *     println($"Got balance async {balance}")
     * })
     * ```
     * 
     * @param supplier the value supplier that is used to complete the future with
     * @return a new Future
     */
    static Future<T> completeAsync<T>(T || supplier) {
        // create a new empty future to complete asynchronously
        let future = new Future<T>()
        // complete the future using the specified task
        Task.run(|| {
            future.complete(supplier())
        })
    }

    /**
     * Create a new future, that will be completed automatically on a different thread, after running the specified task.
     * 
     * Note that if the new future is completed faster, than the current one is able to append any callbacks on it,
     * then some callbacks might be executed on the current thread.
     * Therefore, make sure to register the callbacks to this future first.
     * 
     * If the result object is a constant, consider using `#completeAsync(T)` instead,
     * as it does not require allocating a supplier.
     * 
     * # Examples
     * ```
     * Future<void> executeAsync(|| task) {
     *     return Future.completeAsync(task)
     * }
     * 
     * executeAsync(|| {
     *     myHeavyTask()
     * }).then(|| {
     *     println("My heavy task has been completed")
     * })
     * ```
     * 
     * @param task the task to run to complete the future
     * @return a new future
     */
    static Future<void> completeAsync(|| task) {
        // create a new empty future to complete asynchronously
        let future = new Future<T>()
        // complete the future using the specified task
        Task.run(|| {
            task()
            future.complete(default)
        })
    }

    /**
     * Create a new future, that will be completed automatically on a different thread, after running the specified task.
     * 
     * Note that if the new future is completed faster, than the current one is able to append any callbacks on it,
     * then some callbacks might be executed on the current thread.
     * Therefore, make sure to register the callbacks to this future first.
     * 
     * If the result object is a constant, consider using `#completeAsync(T)` instead,
     * as it does not require allocating a supplier.
     * 
     * # Examples
     * ```
     * Future<void> executeAsync(|| task) {
     *     return Future.completeAsync(task)
     * }
     * 
     * executeAsync(|| {
     *     myHeavyTaskWithResult()
     * }).then(|| {
     *     println("My heavy task has been completed")
     * })
     * ```
     * 
     * @param task the task to run to complete the future
     * @return a new future
     */
    static Future<void> completeAsync(Result<? Error> || task) {
        // create a new empty future to complete asynchronously
        let future = new Future<T>()
        // complete the future using the specified task
        Task.run(|| {
            let result = task()
            if (let Ok(value) = result)
                future.complete(default)
            else if (let Err(error) = result)
                future.fail(error)
        })
    }

    /**
     * Perform a task on a new thread that locks the future whilst the task is running.
     * 
     * @param task the task to be ran asynchronously
     */
    private static void executeLockedAsync(|| task) {
        Task.run(|| {
            synchronized (lock) {
                task()
            }
        })
    }
}
