package "lang"

public:
/**
 * Print a value to the standard output stream and terminate the line.
 */
native void println<T>(T value) 

/** 
 * Print a value ot the standard output stream.
 */
native void print<T>(T value)

/**
 * Print a value to the standard error stream and terminate the line. 
 */
native void errorln<T>(T value)

/**
 * Print a value to the standard error stream.
 */
native void error<T>(T value)
