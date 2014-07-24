


#include "Error_Struct.h"	// Structure used to create error lookup table.

namespace Common {
	// Common namespace error code definitions.
	// Error code table ABI version.
	const unsigned int COMMON_ERROR_ABI_VER = 1; // Increment this if you alter the table.

	// Error code table.
	enum {
		// Generic error codes.
		COMMON_SYSTEM_SPECIFIC = 99,
		COMMON_SUCCESS = 0,
		COMMON_UNKNOWN_ERROR = -1,
		COMMON_INVALID_ARGUMENT = -2,
		COMMON_FUNCTION_NOT_IMPLEMENTED = -3,
		COMMON_ACCESS_DENIED = -4,
		COMMON_EXCEPTION_THROWN = -5,
		COMMON_INTERNAL_ERROR = -6,
		COMMON_IO_ERROR = -7,
		COMMON_RANGE_ERROR = -8,
		COMMON_MEMORY_ERROR = -9,
		// Rendering Subsystem error codes.
		RENDERER_UNABLE_TO_ALLOC_OI_BUF = -12,	// Overlay image buffer.
		RENDERER_UNABLE_TO_ALLOC_TD_BUF = -13,	// Transparency data buffer.
		RENDERER_MEM_BUF_ALLOC_EXCEPTION = -14, 
		RENDERER_DUPE_OVERLAY_EXCEPTION = -15,
		RENDERER_INVAL_OVERLAY_SELF_OVERWRITE = -16,
		RENDERER_TRANSPARENCY_DISABLED = -17,
		// Threading Subsystem error codes.
		THREAD_UTILS_EXCEPTION_THROWN = -31,
		THREAD_UTILS_INVALID_LIBRARY_ID = -32,
		THREAD_UTILS_PLUGIN_LOAD_FAILURE = -33,
		// FileUtills error codes.
		FILEUTILLS_EXISTANT = -60,
		FILEUTILLS_NON_EXISTANT = -61,
		FILEUTILLS_READ_ONLY = -62,
		FILEUTILLS_PATH_LENGTH_INVALID = -63,
		FILEUTILLS_PATH_FILE_AS_DIRECTORY = -64,
		FILEUTILLS_PATH_IS_A_FILE = -65,
		FILEUTILLS_PATH_IS_A_DIRECTORY = -66,
		FILEUTILLS_FILESYSTEM_FULL = -67,
		FILEUTILLS_FILESYSTEM_QUOTA_REACHED = -68,
		FILEUTILLS_EMPTY_DIRECTORY = -69,
	};

	/*!
	 * 	const Common_Error_Object Common::commonErrorTable[]
	 * 
	 * 	This array contains all of the error codes that a Common namespace
	 * 	function may return, in addition to a human readable string describing
	 * 	the error code's meaning. (This is a work in progress, some error codes
	 * 	conflict with error codes in other functions, as such these are slowly
	 * 	being corrected.)
	 * 
	 * 	The easiest way of fetching the human readable string from this table
	 * 	is to call Common::GetErrorMessage().
	 * 
	 * 	Do not reuse an existing error code. (If the error is generic then use a
	 * 	generic error code.)
	 * 
	 * 	Do not change an existing error code. (This is to keep the API stable
	 * 	between revisions.)
	 */
	const Common_Error_Object commonErrorTable[] = {
		{COMMON_SYSTEM_SPECIFIC, "System specific error code. Check log."},
		{COMMON_SUCCESS, "Success."},
		{COMMON_UNKNOWN_ERROR, "Unknown error code."},
		{COMMON_INVALID_ARGUMENT, "Invalid argument."},
		{COMMON_FUNCTION_NOT_IMPLEMENTED, "Function not implemented."},
		{COMMON_ACCESS_DENIED, "Access Denied."},
		{COMMON_EXCEPTION_THROWN, "Execption thrown."},
		{COMMON_INTERNAL_ERROR, "Internal error."},
		{COMMON_IO_ERROR, "Input / Output error. (Normally this is a hardware issue.)"},
		{COMMON_RANGE_ERROR, "Given range is invalid."},
		{COMMON_MEMORY_ERROR, "Memory error (Could not allocate memory / Control loop out of bounds.)"},
		// Rendering Subsystem error codes.
		{RENDERER_UNABLE_TO_ALLOC_OI_BUF, "Could not allocate memory for overlay image buffer."},
		{RENDERER_UNABLE_TO_ALLOC_TD_BUF, "Could not allocate memory for transparency data buffer."},
		{RENDERER_MEM_BUF_ALLOC_EXCEPTION, "Exception thrown while attempting to allocate memory buffer(s)."},
		{RENDERER_DUPE_OVERLAY_EXCEPTION, "Exception thrown while duplicating overlay, clearing dest overlay."},
		{RENDERER_INVAL_OVERLAY_SELF_OVERWRITE, "Given overlays are the same. Cannot overwrite an overlay with itself."},
		{RENDERER_TRANSPARENCY_DISABLED, "Transparency is disabled on given overlay."},
		// Threading Subsystem (Thread_Utils) error codes.
		{THREAD_UTILS_EXCEPTION_THROWN, "Exception thrown in threading subsystem."},
		{THREAD_UTILS_INVALID_LIBRARY_ID, "Given LibraryID does not match a supported library or a loaded plugin."},
		{THREAD_UTILS_PLUGIN_LOAD_FAILURE, "Unable to load plugin(s). Internal error."},
		// FileUtills.
		{FILEUTILLS_EXISTANT, "The path exists."},
		{FILEUTILLS_NON_EXISTANT, "The path (or a component of the path) does not exist."},
		{FILEUTILLS_READ_ONLY, "The path is read only."},
		{FILEUTILLS_PATH_LENGTH_INVALID, "The path's length is beyond the filesystem's maximum length."},
		{FILEUTILLS_PATH_FILE_AS_DIRECTORY, "The path has a file in it that is being treated as a directory."},
		{FILEUTILLS_PATH_IS_A_FILE, "Given path is a file."},
		{FILEUTILLS_PATH_IS_A_DIRECTORY, "Given path is a directory."},
		{FILEUTILLS_FILESYSTEM_FULL, "Given filesystem is full."},
		{FILEUTILLS_FILESYSTEM_QUOTA_REACHED, "User's disk usage quota for the given filesystem has been reached."},
		{FILEUTILLS_EMPTY_DIRECTORY, "The given directory is empty."},
		// TODO: Need to add the error codes from all common namespace functions.
	};

	/*!
	 * 	static int Common::commonLastErrorCode
	 * 
	 * 	Contains the last error code encountered by a Common namespace function.
	 * 
	 * 	Note: Calling Common::GetErrorMessage() or Common::GetErrorTableSize()
	 * 	will NOT clear this variable.
	 * 	Calling any other Common namespace function WILL clear this variable.
	 */
	static int commonLastErrorCode = COMMON_SUCCESS;
};
