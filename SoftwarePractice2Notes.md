# CS 3505 Software Practice II Notes 

## Separation of Concerns
Separating "concerns" or tasks is very important to produce code that is good for maintainable code.

## C/C++
C++ was built on top of C in the 1970's. C++ has grown immensely since then in terms of functionality and what it can be used for, can be used for more 'high' level things now.
- C is 'clunky' to use but is close to the machine and can be highly optimal.
- Original C compilation was costly, compilers were originally designed to make a single pass through the code
- Intermediate object files were typically produced in this compilation process which are linked to build the application
  - Code is small units that are later stitched to form the application
  - C compilation is still done like this today
- Modern object-oriented practeces were imposed later
  - C structs became C++ classes
  - Templates were addedd to allow generic types
  - etc.
- #include actually just pastes in imported code, not as "smart" as other languages 
- C++ has a one definition rule
  - Every function or class should have at most one definition
  - User can accidentally define functions twice
    - Compilation is done a bit at a time and duplicates are not detected until linking
- When executing C/C++ code in the shell, command line arguments are passed to main.
  - int main (int argc, char** argv)
    - argc is a count of the arguments.
    - argv is an array of char * (text strings).
    - The first argument is always the executable name.
- When returning from main, return a 0 to indicate “no error” to the shell.
- Can "partially compile" to a .o file using g++ -c
- Debugging reccomendation- look at first error then go to next errors after, this first error may cause the others
  
### ANSI C
- Many libraries are written in ANSI C for compatibility and performance.
- C++ adds some unavoidable overhead (constructor call and destructor call)
- Adherence to ANSI C encourages portable code
- structs instead of objects
  - Loss of OO engineering advantages, extra care is required
  - Pointers to structs serve as 'this', use functions where the first parameter is a pointer to a struct 
- Use gcc not g++ and name files with .c not .cpp
- Header files end with .h
- Use ‘malloc’ to get bytes of memory, and ‘free’ to release
memory.
- Memory pointers are void*. Cast them to whatever you
need.
- Use ‘sizeof’ to determine how many bytes of storage
something takes up
- Strings are harder to deal with in ANSI C, really just char arrays, must take some care in dealing with them, size/length of array may not be enforced explicitly 
- static in C
  - Declaring functions as static means the function will not be visible outside the current
compilation scope (its identifiers is suppressed in the .o file)
    - Avoids function identifier collisions during linking.
      - File ‘alpha.c’ declares static void foo ()
      - File ‘beta.c’ declares static void foo ()
      - No collision – foo is not visible during linking
  - Declaring local variables static
    - static int count = 0;
    - Variable holds its value between function calls
    - Initializer must be constant

## Shell 
- Commands typed at the shell represent programs to be run
- The shell is itself a running program
- Shell performs a simple built-in command or searches filesystem for a program with that name and executes it
  - The list of locations where the shell wil search is call the 'path'
  - Programs not in the 'path' will not be found
- Shell activities take place within some environment
  - Working directory
  - Environment settings
  - User permissions
- These environment settings are not shown by default
  - pwd # print working directory
  - printenv # print environment variable settings
  - whoami # display current user's id
  - groups # display the groups the user is part of 
- Some useful commands
  - cd # change directory
  - ls # list files
  - chmod # change accessibility settings of file
    - chmod 2700 # makes the folder accessible and viewable only by you
    - chmod 600 # makes the file accessible only by you (not executable)
    - chmod 700 # makes the file accessible and executable only by you
    - and more see documentation
  - jobs # lists the jobs
  - fg # moves top background job to foreground
  - kill %2 # terminates the job in job slot 2
  - xterm & # Runs another terminal window (as a background job) with a shell in it
  - ssh user@machinename # Connects to the machine, starts a shell on it. 
  - Compiling for C++ using g++
    - g++ file.cpp # Compiles the file, creates an executable named a.out
    - g++ file.cpp -o doit # Compiles the file, creates an executable named doit
    - ./a.out # Executes a.out from current directory
- When executing graphical programs over ssh need a special program to draw the graphical information locally that is sent over as the graphical program runs on the remote machine
  - Using a Windows ssh client like PuTTY will draw this graphical information
- & after a program will run a program in the background
- Can pipe a command's raw output into another commands input in bash using '|'

## C++ Classes
-  C++ separates declaration from definition. Classes and functions can be declared then defined later.
-  Include files (header files) are .h files that have forward declarations in them. 
-  To create a class:
   -  Declare the class in a .h file (no definitions)
   -  Define the class in a .cpp file (include the declaration)
   -  Use the class in other files (and include the declaration)
-  Compile .cpp files together using the same g++ command
-  Do not compile .h files. These are jsut snippets of text that you include in .cpp files.
   -  If you do you end up with a .gch file that will cause issues. Remove it.
-  Files can be compiled separately
- Declarations are traditionally placed in header files, .h files
- Definitions are traditionally placed in .cpp files
- C++ builds on C 
  - Classes are built upon the idea of structs
  - Why care?
    - Often library code can contain c code and these older c coding patterns may appear, compatibility may also be needed
- Static class variables
  - Remember, .h files are declarations
    - Static variables do not get storage by being declared
    - You must define static class variables in your .cpp files 
      - static int string_set::constructor_count = 0;
    - Caution -- initialization order is indeterminate. 
      - Avoid: static vector *string_set::x = foo();
    - Initialization will involve a call to foo()
      - Does foo depend on other static data?
      - Which static data gets initialized first?
      - Avoid interdependent static/global data.

## C++ Strings
There are two ways to keep a string in C++.  First, let's look at the old-school way.
- `char *text = "Hello";`
This captures the memory address of some character array holding 'Hello' in a variable named 'text'.  Any time you use double quotes, this type of string is used (char *).  
- `std::string text = "Hello";`
This builds a string object and converts the old style string into the object.  (Make sure to #include <string>.)  The character array is hidden within the object.

You can declare a function that takes a string parameter either way:
- `vector<pntvec> read_file (std::string filename)`

or
- `vector<pntvec> read_file (char *filename)`

If you keep a filename in a std::string, the only issue you'll have is that when you open the file, you need the older style string, a (char*): 
- `ifstream myFile(filename); // Only if filename is a char*.`
- `ifstream myFile(filename.c_str());  // Only if filename is a std::string.`

## C++ Improvements to Memory vs C
- C++ adds reference types to prevent some of the possible bad behaviors of pointers
  - These are just a concealed pointer in a sense
  - References allow for aliasing (two variables appear to use same storage)
  - References avoid copying 
- Pointers can allow very bad behavior
  - Pointer arithmetic
  - Creating pointers to local variables (bad)
  - Type un-safety (pointer casting)

## Pointers and References
- Local variables are on the stack
- Global variables in the globals space
- Parameters are on the stack 
- Assignments of any kind defaults to copying object memory
- Given code like: `polynomial curve; // Assumes default constructor`
  - Object storage is not dynamic
    - No new call
    - The compiler reserves space on the stack for local objects
    - The compiler reserves global space for global objects
- Why is copying object memory the default?
  - C++ classes are built upon the idea of c structs
  - C++ also is generally compatible with c code 
- More OO basics needed, dynamic memory and functions that support 'pass-by-reference'
- Memory Management in C
  - Use malloc and gree to allocate and deallocate memory
  - Keep memory addresses in special memory address variables (pointers)
  - Pointers are essentially a type to hold a memory address
  - i.e. `int *x; x = malloc(4); *x = 42;` the x pointer is of type int pointer (int *) 
  - Declaring a pointer does **NOT** create storage (pointer will point to random place in memory initially)
  - Pointers are usually a fixed size, pointers are memory locations
- Memory management improvements in C++
  - Use the new and delete keywords appear in C++
    - Essentially an abstraction of malloc that sets storage aside and invokes constructor
  - Memory leaks
    - Remember a call to new (this just gives a pointer to a location on the heap of the data created by executing the constructor) allocates memory on the "heap" but it needs to be cleaned up using delete (calls destructor and frees that memory on the heap). Memory will leak if the pointer to the memory location on the "heap" is deleted before the memory on the heap is cleaned up (by using delete). This is because there are no more pointers to the data on the "heap" and thus this data cannot be accessed and is never cleaned up. Thus we have a memory leak.
  - Reference types help reduce pointer issues
    - A reference type is just a concealed pointer
      - `int z, x = 42; // Allocates storage for two ints`
      - `int &y = x; // Y is a pointer to x, but is used as an integer, not a pointer.`
      - `y = 99; // The pointer in y was followed, 99 stored`
      - `Z = y + 5; // Y is still a pointer, but is automatically followed.`
    - References allow aliasing:
      - Two variables appear to use the same storage.
    - References avoid copying:
      - It is easier to pass around a reference to an object than to copy the object into a parameter.
  - Reference behavior in C++ is similar to the behavior in Java and C#, with some exception
- Remember that many operators in C/C++ are overloaded, thus depending on the context operators may have different behavior. i.e. * and &
  - For many cases spaces don't matter with placing of * and &, just relative location, just be consistent. For example `std::istream& operator>> (std::istream &in, Point &point){}` has & in slightly different places although spacing doesn't matter for & just its relative location. A common pattern would be to put & "on" the parameter names (think initializing multiple parameters, may want to associate & with each one) and if not a parameter name then "on" the type.

- Syntax for pointers (can you spot the bug?):
  - `person *p; // A memory address of a person struct'`
  - `int *x; // A memory address of an int`
  - `int y;`
  - `*x = 42; // Follow the pointer, store 42 at that address`
  - `y = *x; // Follow the pointer, retrieve 42, store in y`
  - `x[4] = 7; // Arrays are just pointers. // Follow the pointer, go forward 4 locations, store a 7.`
  - Declaring a pointer does not create storage. (This is
the flaw/bug with the previous example.)
  - We followed the pointer to some **unknown** address.
  - We stored data at that **unknown** address.
  - We just corrupted something.
  - Additionally, we later treated the pointer as an array without
knowing if it was array storage.

- Syntax for following pointers to a struct (or class):
  - `(*p).salary = 3.14; (p->salary) = 3.14;` 
- You can explicitly create a pointer to any variable, struct, or object:
  - `int *x; int y; x = &y; // Computes the address of y, stores it in x.`
- Pointer types:
  - int -- A stored value in memory
  - int * -- A memory address of a stored int
  - int ** -- A memory address of a stored memory address
  - void * -- A memory address of an unknown kind of data

## Polymorphism and Inheritance in C++
### Inheritance in C++
- Syntax
  - Use a single semi colon after the class header to specify superclasses 
    - It is possible to inherit from more than one class
- Following class members are inherited:
  - All member functions
  - All member variables
  - These become part of the derived class, and can be
inherited by sub-sub classes. Note, while private members
are inherited, they are still only accessible by superclass
functions.
- The following are not inherited:
  - All constructors and the destructor
  - Static functions and variables
  - Operator =
  - Friend declarations
- Visibility modifiers
  - Inherited members appear to exist in the derived class. Their visibility in the derived class is controllable.
    - public: parent class items exist in the derived class. Their visibility (in the derived class) is at most ‘public’.
    - protected: parent class items exist in the derived class. Their visibility (in the derived class) is at most ‘protected’.
    - private: parent class items exist in the derived class. Their visibility (in the derived class) is at most ‘private’.
    - None: Default is ‘private’.`
- Must manually call the superclass constructor from the subclass constructor properly or C++ will search for superclass default constructor when creating a subclass object
- Objects can be **'sliced'** on assignment or copy (Thus pointers can prevent slicing but must be careful with them. Pointers or similar must be used to enable the polymorphic effects of inheritance)
  - This occurs because objects are often stored directly in
variables (instead of by reference or pointer).
  - Each type of object takes a certain amount of space.
  - When a subclass object is assigned to a superclass object, the superclass object does not have the space needed to receive the subclass object.
    - Only superclass members are copied.
  - Bad, bad, bad. This destroys polymorphism.
    - Polymorphism in C++ must:
      - Use pointers
      - Declare functions as virtual
      - Use dynamic casts when needed
  - Ex: assume Alpha is superclass and Beta inherits from alpha (Alpha has int x and int y. Beta has int x, int y, and int z) (int z will get sliced in the code below)
```
Alpha a;
Beta b;
a = b; // Slicing must occur, b cannot fit in a
```
### Polymorphism Generally in C++
- Polymorphism by overriding is not enabled by default in C++, must use virtual keyword.
  - Enables virtual dispatch
- Abstract classes in c++ are implied by the presence of pure virtual functions.
  - In the function declaration, set it equal to 0.
- Effects of declaring a pure virtual function:
  - The function cannot be defined within this class.
  - The function must be overridden by a subclass.
  - The class is now abstract – you can only build subclass objects.

## Covariance and Contravariance and Invariance
- Think controlling behavior of relationship between types
- Applies to parameters and behavior of types
### Covariance
- Covariance is when two things vary in the same manner 
  - As class types become subtypes, so may return types on virtual methods
  - The same does not hold true for parameters in C++ (contravariance is allowed)
### Contravariance
- Parameters become more general in subclasses which is ok if the type is still satisfied 
### Invariance
- Invariance is when we cannot traverse the inheritance tree
  - Pointers to pointers cannot be upcast
    - If this was possible could change the "middle" pointer value (think pointer points to "middle" pointer which points to something) value and make it point to different things (breaking the inheritance hierarchy), causing undesired/potentially uncontrolled behavior)
  - Pointers to pointers cannot be downcast
    - Same reason as upcasting, we can point the "middle" pointer to something that would break the inheritance hierarchy
  - This "double-reference invariant rule" occurs in many languages
### Multiple Inheritance 
- Use comma separted list of base classes
- Members of both base classes become members of the subclass
- Ex: `class Phi : Gamma, Beta`
- If Gamma and Beta defines foo() can be hard to determine which foo to use, can do two different things to specify which to use:
  - Can use static cast to change view of object:
    - `Phi p; static_cast<Gamma>(p).foo(); //or static_cast<Beta>(p).foo();`
  - Can qualify each name:
    - `Phi p; p.Alpha::foo(); //or p.Beta::foo();`
- Inheritance trees can be complicated for multiple inheritance, it is possible to inherit the same thing multiple times across different branche
  - Every node in an inheritance tree contributes members to the derived class
- Ex: 
```
class Alpha
{…};
class Beta : public Alpha
{…};
class Gamma : public Alpha
{…};
class Phi: public Beta, public Gamma
{…};
```
- Every memebr of Alpha is inherited twice- considered "intentional"
- This usage of inheritance (above) is often considered erroneous 
  - Breaks ISA model ("is a")
    - Think a phi object is two Alpha objects?
    - Inheritance is a relationship based on type, not content
    - Sometimes is unavoidable 
  - Recall If you want an object to have functionality or data thatbelongs to another class, **do not use** inheritance.
    - Use HASA ("has a") relationships - always use variables.
- Common multiple inheritance graph is a diamond like pattern (think last example above but alpha has only one copy)
  - To ensure only one copy of some base class declare class inheritance as virtual:
- Ex:
```
class Alpha
{…};
class Beta : public virtual Alpha
{…};
class Gamma : public virtual Alpha
{…};
class Phi: public Beta, public Gamma
{…};
```
- There are more issues though
- Ex:
```
class Alpha
{ virtual void foo(); };
class Beta : public virtual Alpha
{ void foo(); };
class Gamma : public virtual Alpha
{ void foo(); };
class Phi: public Beta, public Gamma
{ /* code calls this->foo() */ };
```
- Virtual functions in the virtual base class may be overridden in the ‘sister’ classes (direct subclasses)
  - Which ‘foo()’ should be called in this case?:
  - ` Phi *p = new Phi(); Alpha *a = p; a.foo();`
  - This is ambiguous and disallowed 
  - To get rid of it, override foo in Phi (not always possible)
  - There are many subtle variants of this kind of error
- Java and C# removed multiple inheritance
  - Too many problems and side effects
  - Interfaces allow a type graph without variable or function overlap issues.
- There are very few cases where multiple inheritance is a good idea.
  - The best practice is to voluntarily avoid it.
    - Not always possible when interfacing with library code
  - A better model is that if an object HASA behavior, it has a variable that supports this behavior and this behavior is exposed through member functions.
  
## Object Oriented Class Patterns
- Consider object 'behavior'
  - Language syntax can define methods and variables, but additional information is needed to communicate behavior
    - Methods define type and value behavior through parameters and return values and functional behavior through code
    - Instance variables define value existence, modifiability, and visibility, but little else
- Contracts and specifications (as simple text) are commonly used for more abstract descriptions of behavior
  - Representational Invariant (AKA "class invariant")
    - A constraint on the state of an object
    - Defines'well-formed' instances of an object
    - Code inside of the class can depend on (and must ensure the validity of) these invariants
  - Precondition 
    - Specifies conditions (objects and parameter restrictions) that must be true when a method begins execution
    - If preconditions are met, postconditions are guaranteed
    - A well formed object instance is an implied precondition
  - Postcondition 
    - Specifies outcomes of the method call
    - Includes all changes of object state, return values, and side effects
    - It is implied that the object instance will remain well-formed
- Liskov Substitution Principle
  - Subclass object should be usable through the base class interface without the user knowing they are using a subclass (without altering any of the desirable properties of the program). 

## Const Keyword
Equivalent to final in other languages
- Designates storage that is immutable.
- Can apply to variables and parameters.
- Can apply to return values. Can apply to ‘this’:
  - Put ‘const’ at the end of a function header
- If a function is declared const, then ‘this’ is const.
  - Operator = is not const, it changes ‘this’.
  - Many other operators are const.
  - Accessors/getters should be const.
  - You cannot call a non-const member function from within a
const member function.
    - The non-const function might change ‘this’ somehow.
  - Solution: Make helper functions static, or declare them
‘const

## Casting
- In modern C++ use the following to cast (Can still use traditional Java/C# like casting but these provide additional control and type checking behind the scenes):
  - static_cast<type>(expresssion)-  casting like "usual" (changing type like Java/C# casting)
  - dynamic_cast<type>(expresssion)- casting pointers
  - reinterpret_cast<type>(expresssion)- reinterpret a type as another 
  - const_cast<type>(expresssion)- remove or add const to something

## Overloading Operators 
- Operators (such as *, +, =, ==, etc.) can be
overloaded to perform special functions.
A few key points on overloading:
  - We pass objects by reference to avoid copies
  - We mark parameters as const to indicate we won’t change
them.
    - We also mark const functions that don’t change ‘this’
    - We also mark const return values (to avoid a+b = c)
  - Overloaded operators are just functions.
    - ‘This’ is the left-hand operand (or unary operand)
    - ‘This’ is a pointer to the current object.

## Friend functions
Want a function that is not a member of the class to have access to private members of a class. Use friend keyword to do so.

## Docker
- Virtual machines simulate a computer system, these are generally heavier weight and take a lot of memory to use.
- Docker spins up a virtual machine of sorts that is lightweight and can be created and killed quickly. 
- Docker containers are generally stateless and immutable to be used like designed, allows for abstraction of the state of the os, maximizing compatibility and portability of an application 
- Docker is not a virtual machine in the traditional sense but can be used like one
  - Open ports, access storage(usually binding to cloud storage rather than local storage), use interactively, etc.
  - Docker is lightweight and can be easilh moved around and bound to different storage which makes them flexible for deployment
- Containers use native OS resources, expose them as linux resources to the container 
- The main idea is to separate the state (storage) and the rest of the application, thus the application can be bound to different storage. 
- An "image" in Docker is a prebuilt application environments
  - Linux OS
  - Installed applications
  - Other data files (as needed)
- A "container" in Docker is one instance of an image
  - One execution of an image (A running image)
    - Holds state temporarily 
  - The lifecycle of a container is not meant to be unlimited
    - Containers should be removed when not needed
    - containers rely on the underlying image
      - Cannot remover or change image until all containers using it are removed 
- Many prebuilt images exist in Docker
  - Docker retains a repository of prebuilt images 
  - Images have tags to identify them
    - Also a numeric hash identifier
  - A 'pull' command is used to get an image from a repository 
- You can create your own images based on some other image
  - Specify commands in a Dockerfile
  - Use the 'build' command to process a Dockerfile and create an image
- Building images requires 'context'
  - The context is one directory and its contents (recursively)
  - The context is specified when you use the build command
- When an image is built
  - The build command automatically finds the Dockerfile within the context (within the directory) 
    - The instructions in the Dockerfile are used to create the image. Some instructions run within images.
    - Already completed steps are skipped
      - Docker caches each step as a separate image
    - You may choose to copy files from the context into the new image
- Test your commands in a container 
  - If they do what you need, move them into a Dockerfile
- Try to keep your images small
- Don't use Dockerfile files (directly) for application execution (A Dockerfile is a text document that contains all the commands a user could call on the command line to assemble an image) 
  - You are building a reusable image
  - Its OK to run install/build commands (but run your image to execute an application in it)
  - Run your image to execute an application in it
- The run command starts a container based on a docker image
  - Interactive mode is only useful for debugging/development
  - Most containers are used to run one application
    - These containers are short lived  
  - Container state is lost on exit
  - You may attach external storage to your running containers
    - Keep state externally
    - Can bind a local directory to a folder inside of a container (changes to that folder will be changes to the local directory)

## Drop lists
Add forward links(pointers) to different locations in linked list. This allows for "hopping" to locations in the list. Each node in the list essentially has a random width which is connected to nodes on that same width level. In some ways is balanced like a tree.
- This allows faster traversal of a sorted list, we can hop to the different forward links and find which forward link will get close enough to what we are looking for then go from there.
- Essentially each node in a linked list now gets a **width**, which can randomly assigned a width (like flipping a coin until you get a tails then that is the "width" of that node)
- Nodes on the same width level are all connected like a linked list for that width level.
- Get to end of drop list by starting at head/sentinal node (which is as wide as widest node and doesn't contain a value) following outermost nodes to the end then following next most outer node then keep going one node width level in until you get to the node level that is fully connected (width 1 node width level, like a linked list) and then follow to end which will be end of drop list.
- When implementing want to keep track of prior node at each width level we traverse, this will help for inserting into drop list. When removing, we link over the node we want to remove at all levels then delete.

## Git 
Version control system with numerous features
- Git Workflow (Git has commands to move files/code between each of these areas):
  - Working directory (Local)
  - Staging area (Local)
  - Local repository (Local)
  - Remote repository (Remote)

## Shell Scripting
- A shell is an interpreter
  - A program that translates keywords (typed or from file) into actions
- A shell script is just another way of supplying commands to a shell
- Script is creating by writing shell commands in a file then making it executable
- After you run a script, what directory are you in?
  - The script gets executed in a separate shell that loses it's state/variables when the shell ends
  - Use source before script name to execute in current shell
- When the script was loaded the first line is checked by the current cell. #! allows specification of the path to the shell executable
- Scripts are great for complex, commonly repeated tasks

## Makefiles
Can compile one source code file at a time using -c flag on g++
- Creates but doesn't link 
Compile source code into .o (object) files then link together with any needed libraries
- Example: 
```
g++ -c tester.cpp 
g++ -c hashset.cpp 
g++ tester.o hashset.o 
```
  - Links together object files into a.out executable

Makefiles are simple rulesets for compiling files (or just about any other activity)
To use: Create a makefile and put rules like:
- **"Thing to make": "What it depends on"**
  - **"How to make it"**

Makefiles are whitespace dependent (see indent on "How to make it")
```
tester: tester.c hashset.h hashset.c 
  g++ tester.c hashset.c -o tester
```

When you run a makefile
- The makefile is loaded
- The rule 'tester' is located
- A decision is made: Is the file 'tester' newer than all it's dependencies?
  - If so the rule is satisfied, no action
  - If not, the compilation command is executed
  - Make simply checks file dates to see if a file needs to be rebuilt

- Rules can depend on other rules. If so, the sub rules are evaluated first to build the things the current rule depends on.
  - In the example below, ‘a’ depends on ‘b’. If needed, ‘b’ will
be built before ‘a’.
  - First rule is the default rule
```
a: b c tester.cc
  g++ …
b:
  g++ …
c:
  g++ …
```

Makefiles help with partial compilation. For large project systems, makefiles are used to 'program' he build process.

## UML
- Process: how we go about organizing the development of software
  - Lots of different ways of doing this process
- Modeling: how we abstract software structure, requirements, and behavior
  - Will discuss UML a visual modeling language
    - UML is widely understood
    - Goal is to use models to communicate effectively
- UML is a standardized modeling language
- Graphical representation of complex systems
- Modeling supports analysis and design of software
- Gives an abstract view of code
- In a nutshell, UML gives a standard notation for various models (diagrams)
- Can show as little or as much detail as you like in diagrams
- Two major types of models
  - Static models (Structure)
    - Use cases, Classes, Composite Structure, Component Deployment
  - Dynamic models (Behavior)
    - Interaction (Sequence), State, Activity, Protocol
- The main features of UML
  - It is a metamodel (model of a model)
  - It provides a standard set of elements
  - Defines how those elements can relate to other elements
  - Elements have semantic meaning often useful to software designers
  - Allows for elements to be extended and new elements to be added (extensibility)
- See UML specification documentation: 
  - https://www.uml-diagrams.org/
- UML Class Diagrams- Squared cornered rectangle with:
  - Top compartment contains class name (Italicized if abstract, other modifiers can be specified)
  - The middle compartment (attribute compartment) has class data members ("static" ones are underlined)
  - Bottom compartment is the parameter list 
  - Visibility 
    - \+ is public
    - \- is private
    - \# is protected
    - ~ is package level visibility
  - Multiplicity- Indicates how many objects may fill property (using [] after parameter) 
  - Unary association- A knows about B, but B knows nothing about A
    - Can add as B as attribute of A or draw directional arrow to indicate this dependance as well
  - Binary association is a line with no arrows
  - Self association- An association that connects a class to itself is called self association
  - There is many more specifications for a UML class, see UML specification documentation 
    - https://www.uml-diagrams.org/class-diagrams-overview.html
- State Machines
  - A computer can be thought of a state machine with many states (essentially the processor just takes the machine from one state to the next each clock cycle (there is a **lot** of states though))
  - State machines are used to abstract the way an object's state (the machine's state) changes in response to various events
    - An older, common representation of state machines represent states as a node
  - State machines can have concurrency 
  - UML specifies how to represent a state machine 
    - https://www.uml-diagrams.org/state-machine-diagrams.html 
- Activity Diagrams
  - Used to model sequential and parallel work flows
    - Useful to model what really happens in a business to help understand that work flow to help you understand how to write code 
  - Much like flowcharts of old
  - Differs from state machines 
  - UML specifies how to represent activity diagrams
    - https://www.uml-diagrams.org/activity-diagrams.html
- State machines vs activity diagrams ("orthogonal" diagrams in a sense)
  - State machines emphasize condition
  - Activity diagrams emphasize actions
    - high level support for concurrency
  - Generally activity diagrams imply state between actions, state diagrams imply actions between states (this is how they are "orthogonal")
- Sequence Diagrams
  - Goal is to show interactions between objects
    - Object, as a class instance
    - Also can show actors, participants in a more general sense
    - Often is used to help understand what is happening in a "use case"
    - Not precise enough to show activity inside of an object
  - Focuses on "messages" between "lifelines"
  - Sequence diagram describes an interaction by focusing on the sequence of messages that are exchanged, along with their corresponding occurrence specifications on the lifelines
  - UML specifies how to represent sequence diagrams
    - https://www.uml-diagrams.org/sequence-diagrams.html
  - Participants
    - Actors
      - Taken directly from a use case
      - Roles
        - Anonymous instance of a class (can also be specific instance)
        - Box notation
      - Objects
        - Box notation
        - Underline name
        - Object:Class (both parts optional)
      - Participants drawn at top of diagram, left to right
        - Extended downward from middle of participant is lifeline
          - A dashed line indicating activity of the participant
        - Time flows from top to bottom
  - Activation 
    - An activation is a long rectangle placed on top of the life line
    - Indicates when the object is active
      - That is, it is “on the stack”
    - Activations are optional, but often make it very clear what is going on
    - If some kind of recursion happens, you nest the activations
    - You may leave off the return if you are using activations 
      - Because it is “obvious” when the return happens
  - Messages
    - The interaction between objects is called a message
    - Lines horizontal
    - Returns are optional
  - Creating and Deleting Objects
    - Use X to indicate object deletion
  - Message labels
    - Text placed above message line
    - Optional but can describe method or operation being invoked
  - It is often useful to take select "use cases" and build a sequence diagram in the design that reflects the use case
    - Insures that the design does cover use case functionality
    - Doesn’t need to be perfect, but enough detail to verify that the use case can be performed as required.

## Filetypes
A file is just a steam of bytes
- The filetype just indicates how to interpret the file (stream of bytes)
- Data comes in a wide variety of forms, not all in files
- Metadata
  - Data that describes other data
  - Indicates how to interpret data
  - A filetype is an example of metadata of a file
- Storing an integer in a file (usually 4 bytes)
  - Which byte do you write first?
    - Little endian
      - Write least significant byte first
    - Big endian
      - Write most significant byte first
    - Both integer formats exist in files and memory
- Data written as bytes must conform to some standard 
- All complex data files have a specified standard

## Design Patterns
- A design pattern is a named descriptions of a solution design for a general design problem in a specific domain 
- Good patterns stem from know successful solutions
- Do not solve every problem from first principles, reuse previous knowledge 
- Antipatterns arise from failures
- Some might say that design patterns exist because the language doesn't support a design feature directly 
- Design patterns can be good to know, especially when they're useful, then it can be easy to lookup the design pattern implementation specifics
- Singleton design pattern
  - Some resources are not shareable
    - Hardware devices
    - Caches, object pools
    - Log files
    - Persistent prefrences
  - Naive solution would be creating a global variables and functions. This is not ideal.
  - Use a single object to represent the shared resource 
    - Resource state can be hidden
    - The interface to the resource can be well defined
  - Limit usage to a single object of the class
    - Make the constructor of the object private. Then create a static variable that will hold the single object of the class. Then a static function can be used to create the object (if it doesn't exist) and/or return the reference to the single object. There will only be a single object of the class. (Note implementing this way is not thread safe)
    - Can also create a method to clean up the single object.
  - Singleton classes shouldn't be inherited. Can result in breaking the singleton pattern.
  - To make a singleton thread safe:
    -  Mark the singleton backing variable as "volatile" thus each time the variable is accessed in code it will refetch the value of the variable.
    - Require that the creation of a singleton is always on the same thread using locks

## FFMPEG
A C library for the manipulation of audio and video. Basically can read and write various audio and video formats and convert between them.
- General process is to: decode an audio/video format to a raw format -> make modifications to the raw format -> encode raw format into an audio/video format

## Aggregates and Iterators
- Aggregates 
  - Name for a collection (sets, lists, etc.)
  - Most aggregates provides a "view" of the content in the aggregate
- Iterators 
  - In C++ can get an iterator from a std::vector by calling .begin() (will return a pointer which represents an iterator for the vector) then by dereferencing the iterator we can get the first element, then doing ++ we can get the next item. (This is more overloading of operators)