# CS 100 Programming Project - RShell
Fall Quarter 2019  
Mohamed Rayyan SID 862037325  
Steven Calvert SID 862145034  

# Introduction
  We will be creating a program named RShell that functions similar to a terminal. The program will be able to take in common commands and operators in a command line interface and process each command as they would be executed in a shell environment. The implementation will be primarily composite pattern, but will have small parts of the strategy pattern implemented as well. The input will be handled by taking in a string from standard input, and parsing the string for commands, arguments, and operators to process and sort the commands into a recursively composed structure. This will be represented as a Base pointer to a specific command object, which will call execvp for the specific command and use system calls to handle them, then return the proper output.  

# OMT Diagram  
![RshellUML](/images/Rshell-_parser.png)
![ParserUML](/images/Rshell.png)

# Classes and Drivers 
  * main.cpp
    
    * Driver class that displays the '$' character and get user input and return it to Acessor.hpp.
  * Executable.hpp
    
    * Base class, contains the pure virtual function run_command(). Enables each inheritance to have its own implementation of the function.
  * Cmnd.hpp
    
    * Sub-class that inherits from Executable. Cmnd.hpp holds a null terminated array of C strings that hold the command in it's first index, arguments in the following indices, and a NULL value in the final index. From the Cmnd.hpp, single commands and multiple commands with connectors would be created. The run_command() function would be implemented to run single commands with no connectors. The commands are stored in a vector of executables, which are executed sequentially or until an exit is encountered.
  * Exit_cm.hpp
    
    * Simple class that simply exits if run_command() is called on it. Derives from CMND and acts as one for sorting purposes.
  * Test_cm.hpp
    
    * Class that uses the stat struct and function to get information about a certain file, when given a path. Uses the macros S_ISREG to determine if it is a regular file, and S_ISDIR to determine if it is a directory. Currently supports -e, -f, and -d, which are the file exits, is a regular file, and is a directory respectively. Derives from Cmnd.hpp and returns true if the flags conditions are met and outputs (TRUE), else outputs (FALSE) and returns false.
  * Parentheses.hpp
    
    * Class that exists purely for use as a placeholder in the Shunting-yard algorithm. Returns its type as a "(" or ")" based on the circumstances of a specific objects creation.
  * Connector.hpp
    
    * Sub-class that inherits from Executable. Connector.hpp is a parent class for And_op, and Or_op classes. Connector.hpp holds two pointers of type Executables. Connector.hpp is used for commands that contain connectors such "&&" and "||". One pointer would hold the left executable and the other would hold the right executable that would be inbetween the connectors.
  * Or_op.hpp
    
    * Sub-class of Connector.hpp. Or_op.hpp holds executables separated with the "||" connector. With the function run_command() inherited from Connector.hpp, Or_op.hpp is able to call run_command() on its two children, following the rules of the "||" connector. If the first executable passes, thes second executable is not run. The function returns true if either of the commands return true.
  * And_op.hpp
    
    * Sub-class of Connector.hpp. And_op.hpp mainly holds executables separated with the "&&" connector. With the function run_command() inherited from Connector.hpp, And_op.hpp is be able to call run_command() on its two childern, following the rules of the "&&" connector. The second executable is run only if the first passes. The function returns true if both executables pass.
  * OutputRe_op.hpp
  
    * Our implementation of the output redirection operators > and >>. These commands are differentiated by a flag inside the class that indicates if the file should be opened for truncating or not. The dup2 function is used to redirect stdout to the file descriptor we open in a subprocess, which does not impact the stdout of our primary process
  * InputRe_op.hpp
    
    * The implementation of input redirection operator <. This can be used to funnel input into a process by taking the file and using it as the file descriptor for our stdin, which the process waits for. The EOF is used to indicate the end of the input, which the process understands as the point where it executes on the available input. The primary functionality is done in a suprocess as to not affect the stdin of our primary process.
  * Pipe_op.hpp
  
    * Implementation for bash piping from one process to another. A subprocess is opened that pipes our stdout from the child process into the stdin of the other process, using the pipe() and dup2() functions for reassigning file descriptors. Dup() is also used to save the initial file descriptor for stdin of the main process so it can be reset after completing the necessary input into the other process.
  * Parser.hpp
    
    * The parser takes a string input from our main and splits it up into single command, arguments, or operators. Rules involving quotes and comments apply when parsing the initial string. We then split the string up into multiple smaller substrings of single Executable* types, which are created with respect to what the string contains. The executables are stored in a vector of type Executable*, which is traversed sequentially while we call run_command(). The concept is that the root of our recursively composed structure will be stored in the vector, and subsequent nodes will be roots as well. The parser includes a function named showCmnd(int) which calls show() on the command stored in the vector of type Executable*. This functions primary purpose is for testing. The parser was modified in Assignment 3 to include support for the test command(as well as its symbolic notation [ ] ) and parentheses. This is done by using the sequentially created objects with the Shunting-yard algorithm(https://en.wikipedia.org/wiki/Shunting-yard_algorithm) following the pseudocode algorithm listed on wikipedia to organize and assign the proper children to operators. To accomplish this, we needed to represent Parentheses in an Executable class of their own to implement getType().
    
# Prototypes and Research
  The prototypes are in the prototypes/ folder are not current, and do not reflect our current classes. The OML diagram above represents the current structure of our project for Assignment 2.
  
  The system call execvp is going to be the primary way we pass in commands to the system, and can tell if the executable failed or not by the return value of execvp. If the return value is -1, we can tell that the command was not valid. As such, when we use `fork()` to invoke multiple processes, the return value will let us know how we can handle our connectors. After some experimentation with the `&&` and `||` operators in terminal, we planned out how we will implement the classes. `And_op.hpp` and `Or_op.hpp` will handle the `&&` and `||` operations respectively. The fork command can be used in conjunction in the run_command() of our Cmnd class to ensure that the main process waits for the child process running execvp to finish before moving on, as well as ensuring the return value is correct depending on the exit status of the child process.
  
  The `&&` operator will be handled in our program by checking to ensure that the first command passes before the next one will execute. The `run_command()` function will be defined as such to implement the correct operation. Something we discovered while testing is that while entering the command `ech hello && echo middle || echo goodbye` will first print out the error `-bash: ech: command not found`, and on the next line will print goodbye. Since the first command failed, the second command of the `&&` does not get run. However, the `||` views its left command as a failure, so its right command is run. The last connector wil be the root of our structure, and hold pointers to either an &&, ||, or a Cmnd. 
  
  The other prototypes we made are preliminary the preliminary versions of our composite, Connector, and our interface, Executable. The interface Executable contains basic operations that we believe we will need at the moment, but can be expanded as we require more functionality. The Connector composite holds a pointer to a left and a right `Executable*`, and is the parent class of our operators.  
  
  After submitting the first assignment, we began work on what parsing method would work best, and went with a marking approach. This ensures that each command is marked and processed, and inappropriate input is ignored or seen as an error. The marking approach also allows us to deal with quotations easier, and will be useful in the future when dealing with parenthesis around our operators and commands.  
  
  We tested our functions starting with the operators, then eventually with cmnd objects once we got the fork, execvp, and waitpid set up. The mock cmnd class serves to indicate what the result should be if the command succeed or fails, and functions the same as the actual class does. While testing these classes, we wanted to ensure that commands would fail if the executable is wrong or the arguments are invalid, and the proper return result from the operator, depending if it was and && or || test. Some tests were also written to combine and/or objects.  
  
  We tested our parser by using the show() function from the stored executable after it was parsed in our function showCmnd(int) which would show the command stored at a particular index of our vector. This function was created purely for testing purposes and does not have practical use in our program at this moment.
  
  For Assignment 3, we initially attempted to create a recursive function that would continue attempting to create and assign children, but call itself again when it reaches a left parentheses, and would not stop to return until it finds a matching right parentheses, creating and assigning left and right children as it goes. The difficulties we encountered with that approach was the base cases for assigning outside of left and right parentheses, as well as multiple cases of parentheses. As such, we decided to go with a more common algorithm known as the Shunting-yard algorithm. For this, we created two deques to represent our "operator" and "output" stacks respectively, and wrote out the algorithm pseudocode using the listing on wikipedia as a reference (https://en.wikipedia.org/wiki/Shunting-yard_algorithm). This allowed us to consider that everything in parentheses would be created immediately upon closing a parentheses, and proper order could be achieved. Instead of getting the "operator" from the stack and pushing it directly to the output, we would assign its two children from the top of the output stack, stored in reverse order.
  
  The test command was relatively easy to implement, we simply created a subclass of Cmnd. In our parser we modified it such that it creates a test command whenever we see the first four characters as test in our create function, which handles command creation. In the precheck function, we have an implementation to check for square bracks [ ] and replace instances of them with test on the first bracket, so we can have a standardized format going into the precreate function.
  
  Assignment 4 involved implementing the input redirection operator (<), the output redirection operators (>, >>), and piping (|). The output redirection was the quickest to complete, as we simply redirected the stdout of a subprocess for the left operand into a file descriptor with a filename on the right operand. This implementation was modified based on the type of output redirection, > which would simply overwrite the file, and >> which would truncate the results to the end of the file. The subprocess allowed us to make no modifications to the stdout of our primary  process, so no file descriptors needed to be saved.
  
  The input redirection operator was tackled next. Our first approach was to try to manipulate the input from the file into a stringstream that we could then redirect into a string, which could be piped out. Before implementing this, we realized we could simply open the file as a file descriptor and set this file as the pseudo 'stdin' of the subprocess we created for running the actual command. This would then print to stdout as normal and functions with the rest of our system.
  
  Piping took the most time to develop, and required much redesigning of our input and output redirection to find a style that worked. Our first approach was a direct redescribing of the stdout of the left process to the stdin of the right process, but we noticed that we werent getting any output at all from this. This was because all of the output from the Cmnd class was in the stdout of the subprocess, not the main process. This is where our primary use of pipe() came in. We piped the output from stdout of the subprocess that ran execvp to the main process, which then allowed us to capture stdout from parent classes in this manner. Once this was done, we used a system of capturing stdout from the new classes we had created, and left the existing connectors alone. After making these modifications, piping was simply just redirecting the stdout of a subprocess to the stdin of the right process through a pipe().
  
# Development and Testing Roadmap  
  Our plan for development is from the leaf class, Cmnd, upward through && and ||. While developing each class, we will write appropriate unit tests for each created class. As such, the plan we have to implment is the classes in the following order:
  
* Parser.hpp  
  * - [x] Parse and separate executable from arguments and store in char** variable
  * - [x] Create appropriate Cmnd, And_op, and Or_op objects, in correct structure
  * - [x] Test by counting arguments, and ensuring executable is separated correctly
* Cmnd.hpp
  * - [x] Utilize fork and waitpid to ensure that a child process handles the execvp, while the main process waits for it to finish.
  * - [x] Correctly call and return true if execvp passes on command stored in the private member variable
  * - [x] Write tests to ensure that execvp handles numerous commands correctly, and ensure return value is correct.
* Test_cm.hpp
  * - [x] Implement the stat struct and calll stat on a given path.
  * - [x] Check for -f flag and use the result of S_ISREG to determine proper output
  * - [x] Check for -d flag and use the result of S_ISDIR to determine proper output
  * - [x] If no flag is provided based on size of char**, use -e as default and return true if file is found, else false.
* And_op.hpp
  * - [x] Run the command on the right **only** if the command on the left succeeds
  * - [x] Can hold other &&, ||, or Cmnd objects as type Executable*
  * - [x] Test with working Cmnd objects with known results from running in terminal
  * - [x] Test with other and, or references.
* Or_op.hpp
  * - [x] Run the commannd on the right **only** if the command on the left fails
  * - [x] Can hold other &&, ||, or Cmnd objects as type Executable*
  * - [x] Test with working Cmnd objects with known results from running in terminal
  * - [x] Test with other and, or references
* Connector.hpp
  * - [x] Parent class of And_op and Or_op, holds two type Executable* variables, left and right
* Executable.hpp
  * - [x] The interface of our program, will change depending on new functions and features
  * - [x] Will be implemented at the beginning, so it can be used in some unit tests of && and || operations
* InputRe_op.hpp
  * - [x] Tests input redirection for text files into cat, tr, and other commands
* OutputRe_op.hpp
  * - [x] Tests output redirection from numerous processes into text files and manual checks for completion.
  * - [x] Return value depends on command ran and file write was successful.
* Pipe_op.hpp
  * - [x] Tests that the pipe succeed and that neither of the commands fail.
  * - [x] Output is shown on the screen.
* Integration tests
  * Utilize IO redirection to write integration tests.
  * Test  
    - [x] single commands
    - [x] multiple comm.hppands
    - [x] commented lines
    - [x] exit command integration
    - [x] test_literal_tests.sh
    - [x] test_symbolic_tests.sh
    - [x] precedence_tests.sh
    - [x] input_redirection_tests.sh
    - [x] output_redirection_tests.sh
    - [x] pipe_operator_tests.sh
    
  The project is complete through Assignment 4.
