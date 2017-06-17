# Code

The source code is organized in several directories.
- util_sc_tests/ contains basic_tests/ and lib/ with the googletest framework.
- util_sc/ contains the implementation of C smartcard and p2abc IoT toolkit.
  + A CMakeLists.txt file defines it as a library, and organizes the code in three main categories:
    * common: Pure C code that implements the smart card functionality and is platform independent with IoT systems in mind. Relies on the adaptors, interfaces to external utilities that are not standard in IoT and may need custom implementations.
    * utils_interface: Interfaces (.h) to functions that not all IoT devices can provide, like standard libraries or cryptography utilities (some may have HW implementations, some SW, some none). The source files (.c) are the implementations of the interfaces, and **are the files to be modified** when porting the toolkit to new systems.
    * external_utilities: Usually the adaptor .c files won't implement everything from scratch, and simply rely on other external libraries, the adaptees, which files should be copied in the this directory. These directories **are the ones to be modified** when porting the toolkit to new systems.


In summary, to port the implementation, change the TODO.

This file was written before the implementation of the main process that will handle how the smartcard works in a system, so things may change in the future.





## Special Interfaces

* sc_status_io_util: one of the 2 only interfaces called from outside the core.

    Varies depending on method of storing the static data. Current implementation: json files.
Delegates on serialize_util for the json parser.
 
 * serialize_util: only interface that knows the internal data structures of the core, 
 and one of the 2 only interfaces to be called from outside the core (for APDU Command parsing).
  