/**
 * Retrieve a handle to the specified standard device (standard input, standard output, or standard error).
 * 
 * # Device Type
 * - STD_INPUT_HANDLE  | -10
 * - STD_OUTPUT_HANDLE | -11
 * - STD_ERROR_HANDLE  | -12
 *
 * @param kind - the standard device type
 * @return the identifier of the device
 * 
 * @see https://learn.microsoft.com/en-us/windows/console/getstdhandle
 */
extern int GetStdHandle(int kind)

/**
 * Retrieves the calling thread's last-error code value. 
 * The last-error code is maintained on a per-thread basis. 
 * Multiple threads do not overwrite each other's last-error code.
 * 
 * @return the calling thread's last-error code.
 * 
 * @see https://learn.microsoft.com/en-us/windows/win32/api/errhandlingapi/nf-errhandlingapi-getlasterror
 */
extern int GetLastError()

/**
 * Writes a character string to a console screen buffer beginning at the current cursor location.
 * 
 * @param handle - The handle to the console screen buffer. The handle must have the GENERIC_WRITE access right. 
 * For more information, see Console Buffer Security and Access Rights.
 * @param buffer - A pointer to a buffer that contains characters to be written to the console screen buffer. 
 * This is expected to be an array of either char for WriteConsoleA or wchar_t for WriteConsoleW.
 * 
 * @see https://learn.microsoft.com/en-us/windows/console/writeconsole
 */
extern int WriteConsoleA(int handle, ubyte* buffer, int length, int* written, int reserved)

/**
 * Writes a character string to a console screen buffer beginning at the current cursor location.
 * 
 * @param handle - The handle to the console screen buffer. The handle must have the GENERIC_WRITE access right. 
 * For more information, see Console Buffer Security and Access Rights.
 * @param buffer - A pointer to a buffer that contains characters to be written to the console screen buffer. 
 * This is expected to be an array of either char for WriteConsoleA or wchar_t for WriteConsoleW.
 * @param length - The number of characters to be written. If the total size of the specified number of characters 
 * exceeds the available heap, the function fails with ERROR_NOT_ENOUGH_MEMORY.
 * @param written - A pointer to a variable that receives the number of characters actually written.
 * @param reserved - Reserved; must be NULL.
 * 
 * @see https://learn.microsoft.com/en-us/windows/console/writeconsole
 */
extern int WriteConsoleA(int handle, ushort* buffer, int length, int* written, int reserved)
