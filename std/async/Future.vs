package "async"

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

public:
class Future<T> {
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
     * Note that if the future completes successfully with null, the method will also return null.
     * 
     * # Examples
     * ```
     * let result = await getUserAsync("John Doe")
     * ```
     * This code will block until the `getUserAsync()` retrieves a value.
     * 
     * @return the completion value
     */
    native Result<T, E> get<E>()
    where 
        E : Throwable

    /**
     * Block the current thread and wait for the future completion to happen.
     * After the completion, the result T object is returned.
     * 
     * If the future completes with an exception, an error is returned.
     * 
     * If the blocking exceeds the specified time interval, a FutureTimeoutExcpetion is retrieved.
     * If the timeout is 0, the method wil lblock indefinitely.
     * 
     * Note that if the future completes successfully with null, the method will also return null.
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
    native Result<T, E> get<E>(long timeout)
    where
        E : Throwable

    /**
     * Block the current thread and wait for the future completion to happen.
     * After the completion, the result T object is returned.
     * 
     * If the future completes with an exception, the default value is returned.
     * 
     * Note that if the future completes successfully with null, the method will also return null.
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
    native T getOr(T fallback)

    /**
     * Block the current thread and wait for the future completion to happen.
     * After the completion, the result T object is returned.
     * 
     * If the future completes with an exception, the default value from the fallback supplier is returned.
     * 
     * Note that if the future completes successfully with null, the method will also return null.
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
    native T getOr(T || fallback)

    /**
     * Block the current thread and wait for the future completion to happen.
     * After the completion, the result T object is returned.
     * 
     * If the future completes with an exception, the default value is returned.
     * 
     * If the blocking exceeds the specified time interval, a FutureTimeoutExcpetion is retrieved.
     * If the timeout is 0, the method wil lblock indefinitely.
     * 
     * Note that if the future completes successfully with null, the method will also return null.
     * 
     * # Examples
     * ```
     * let result = getProfile("test").getOr(1000, fallbackProfile)
     * ```
     * 
     * @param fallback the fallback value to be returned if the future execution fails or the timeout is exceeded
     * @return the completion value
     */
    native Result<T, E> getOr<E>(long timeout, T fallback)
    where
        E : Throwable

     /**
     * Block the current thread and wait for the future completion to happen.
     * After the completion, the result T object is returned.
     * 
     * If the future completes with an exception, the default value is returned.
     * 
     * If the blocking exceeds the specified time interval, a FutureTimeoutExcpetion is retrieved.
     * If the timeout is 0, the method wil lblock indefinitely.
     * 
     * Note that if the future completes successfully with null, the method will also return null.
     * 
     * # Examples
     * ```
     * let result = getProfile("test").getOr(1000, || fallbackProfile)
     * ```
     * 
     * @param fallback the fallback value supplier to be called if the future execution fails or the timeout is exceeded
     * @return the completion value
     */
    native Result<T, E> getOr<E>(long timeout, T || fallback)
    where
        E : Throwable

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
    native T getNow(T fallback)

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
    native bool complete(T value)

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
    native bool fail(Throwable error)

    /**
     * Register a completion handler to be called when the future completes without an error.
     * 
     * If the future completes with an exception, the specified action will not be called.
     * If you wist to handle exceptions as well, use `result(|T, Throwable|)` or `except(|Throwable|)`.
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
     * @param action the successful completion handler
     * @return this future
     */
    native Future<T> then(|T| action)

    /**
     * Register an asynchronous completion handler to be called when the future completes without an error.
     *
     * If the future completes with an exception, the specified action will not be called.
     * If you wist to handle exceptions as well, use `result(|T, Throwable|)` or `except(|Throwable|)`.
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
    native Future<T> thenAsync(|T| action)

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
    native Future<U> transform<U>(U |T| transformer)

    /**
     * Create a new future that does not care about the completion value, it only check for successful or failed completions.
     * 
     * After this future completes, a null value is passed to the new future.
     *
     * If this future completes with an exception, the new future will be completed with the same exception.
     * If the current future is already completed successfully, a completed future will be returned with the value of null.
     * 
     * # Examples
     * ```
     * database.getBalance("John Doe")
     *     .callback()
     *     .then(|| println("Balance has been found"))
     * ```
     * 
     * @return new future of void type
     */
    native Future<void> callback()

    /**
     * Register a failure handler to be called when the future completes with an error.
     *
     * If the future completes successfully, the specified action will not be called.
     * If you wish to handle successful completions as well, use `result(|T, Throwable|)` or `then(|T|)`.
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
     * @param action a failed completion handler
     * @return this future
     */
    native Future<T> except(|Throwable| action)

    /**
     * Register an asynchronous failure handler to be called when the future completes with an error.
     *
     * If the future completes successfully, the specified action will not be called.
     * If you wish to handle successful completions as well, use `result(|T, Throwable|)` or `then(|T|)`.
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
    native Future<T> exceptAsync(|Throwable| action)

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
    native Future<T> fallback(T |Throwable| transformer)

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
    native Future<T> fallback(T fallback)

    /**
     * Register a special handler, that listens to both successful and unsuccessful completions.
     *
     * After a successful completion, the specified action is be called with the result value and the exception is null.
     * 
     * If the future completes with an exception, the is null, and the exception is specified.
     * 
     * If you wish to determine if the completion was successful, consider checking if the exception is null, as the 
     * completion might be successful with a null result.
     * 
     * If the future is already completed, the action is called immediately
     * with the completed value or exception.
     * 
     * # Examples
     * future.result(|result, error| {
     *     if (error == null) {
     *         println($"Completed result: {result}")
     *     } else {
     *         println("Unable to fetch result")
     *     }
     * })
     */
    native Future<T> result(|T, Throwable| action)

    /**
     * Register a special handler, that listens to both successful and unsuccessful completions.
     * Use the transformer to create a new future using the completion value and error.
     * 
     * After a successful completion, the specified action is called with the result value,
     * and the exception is `null`.
     * 
     * If the future is completed with an exception, the the result is null, and the exception is given.
     * 
     * If you wish to determine if the completion was successful, consider checking if the exception is
     * `null`, as the completion might be successful with a `null` result.
     * 
     * If the Future is already completed, the action is called immediately
     * with the completed value or exception.
     * 
     * # Examples
     * ```
     * future.result(|result, error| {
     *     if (error == null) {
     *         println($"Completed result: {result}")
     *     } else {
     *         println("Unable to fetch result, modify value")
     *         result = getMyFallbackValue()
     *     }
     *     return result
     * });
     * ```
     *
     * @param transformer the Future value transformer
     * @return a new Future of type U
     */
    native Future<U> result<U>(U |T, Throwable| transformer)

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
    native Future<T> timeout(long timeout)

    /**
     * Indicate whether the future completion had been done (either successfully or unsuccessfully).
     * In order to determine if the completion was successful, use `#isFailed()`.
     * 
     * # Examples
     * ```
     * let future = Future.completed("test")
     * assert future.completed() == true
     * 
     * let future = Future.failed(new Exception("Something went wrong"))
     * assert future.completed() == true
     * ```
     * 
     * @return `true` if this future has already completed, `false` otherwise
     * @see #isFailed()
     */
    native bool completed()

    /**
     * Indicate whether the future was completed unsuccessfully.
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
     * @see #isCompleted()
     */
    native bool failed()

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
    static native Future<T> completed<T>(T value)

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
    static native Future<T> completed()

    /**
     * Create a new future, that is completed initially using the specified value.
     * 
     * # Examples
     * ```
     * Future<int> getBalance(string user) {
     *     return Future.completed(|| 1000)
     * }
     * let balance = await getBalance("test").unwrap()
     * ```
     * 
     * @param value the completion result
     * @return a new completed future
     */
    static native Future<T> completed(T || value)

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
    static native Future<T> failed<T>(Throwable error)

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
     * @param executor the executor used to complete the future on
     * @return a new Future
     */
    static native Future<T> completeAsync<T>(T result)

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
     * @param result the value that is used to complete the future with
     * @param executor the executor used to complete the future on
     * @return a new Future
     */
    static native Future<T> completeAsync<T>(T || result)

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
    static native Future<void> completeAsync(|| task)
}
