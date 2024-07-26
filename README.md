# Fiber-Scheduler-Implementation
this repositery includes the solution for Advanced systems programming module assignment and has three files:
file named task1:contains the solution for the 1st task
file named task2: contains the solution for the 2nd task
files named task3: contains the solution for the 3rd task
task1:
includes the solution for task1 and has one file which is task1.cpp
Task 1 Documentation:
This implementation demonstrates basic context switching using get_context and set_context functions. The program defines two functions, foo and goo, which represent distinct execution paths. The context of each function is saved in separate stacks (fooStack and gooStack). The main execution flow starts in main, where it initializes these stacks and sets up the contexts for foo and goo. The program then switches to foo, which prints a message and switches to goo. goo also prints a message and then switches back to the main context. This example showcases the fundamental mechanism of saving and restoring execution states, crucial for understanding context switching in fiber implementation.

task2:
includes the solution for task 2 and has 5 files:
Task 2 Documentation: Fiber Class and Scheduler Implementation
Task 2 demonstrates the creation of a fiber class and a scheduler class for managing fibers. The fiber class encapsulates a stack, context, and optional data pointer, allowing for the execution of functions in isolated contexts.


fiber.hpp: Defines the fiber class with methods for context management and data access.

scheduler.hpp: Implements the scheduler class, which queues fibers and executes them sequentially.

The implementation includes three parts:


task2pt1.cpp: re-working task 1 to use fiber class.

task2pt2.cpp: Utilizes the scheduler class to manage two fibers, f1 and f2, each executing a simple print function.

task2pt3.cpp: Extends the example with shared data between fibers, demonstrating data passing and fiber execution control.

This task illustrates the foundational concepts of fiber-based programming, showcasing how fibers can be created, managed, and used to execute separate code paths in a controlled, cooperative multitasking environment.



task 3 :
Task 3 Documentation: Fiber Yield
Task 3 enhances the fiber and scheduler system with yield functionality and shared data handling. This task comprises two parts:


task3pt1.cpp: Implements the yield feature within fibers. Fibers f1 and f2 are created and managed by the scheduler. f1 demonstrates the yield functionality, pausing its execution to allow f2 to run, and then resumes, showing cooperative multitasking.


task3pt2.cpp: Focuses on sharing data between fibers. Here, sharedData is used as shared memory accessed by both f1 and f2. This example illustrates how fibers can interact with shared resources, with f1 modifying the data and f2 accessing it.


The fiber class includes methods yield and fiber_exit to manage execution flow, while the scheduler class orchestrates the fibers, handling yielding and resumption of execution. This task effectively demonstrates the use of fibers for cooperative multitasking and shared data management in a controlled environment.


How to run the programs
For task1 file:
clang++ -std=c++11 -o task1 task1.cpp context.o
For task2 files:
clang++ -std=c++11 -o task2pt1 task2pt1.cpp context.o
clang++ -std=c++11 -o task2pt2 task2pt2.cpp context.o
clang++ -std=c++11 -o task2pt3 task2pt3.cpp context.o
For task3 files:
clang++ -std=c++11 -o task3pt1 task3pt1.cpp context.o
clang++ -std=c++11 -o task3pt2 task3pt2.cpp context.o
