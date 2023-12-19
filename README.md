# API Redirect Example
This is a code that calls the API from a module other than the existing module.

* Copy kernel32.dll and ntdll.dll and load them by calling LoadLibraryEx.
Get the API address from the function table of the module and call it.
