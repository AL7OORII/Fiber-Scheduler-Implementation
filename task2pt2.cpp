#include <iostream>
#include "fiber.hpp"
#include "scheduler.hpp"



scheduler s;
// Fiber function 1
void func1() {
    std::cout << "fiber 1" << std::endl;
    s.fiber_exit();
}

// Fiber function 2
void func2() {
    std::cout << "fiber 2" << std::endl;
    s.fiber_exit();
}

int main() {
    // Create the scheduler instance (made global for simplicity)

    fiber f1(func1);
    fiber f2(func2);

    // Add fibers to the scheduler queue
    s.spawn(&f1);
    s.spawn(&f2);

    // Execute fibers in a round-robin fashion
    s.do_it();

    return 0;
}


//other test examples 
/*void fiber_func3() {
    std::cout << "fiber 3" << std::endl;
    s.fiber_exit();
}

void fiber_func4() {
    std::cout << "fiber 4" << std::endl;
    s.fiber_exit();
}

int main() {
    fiber f3(fiber_func3);
    fiber f4(fiber_func4);

    s.spawn(&f3);
    s.spawn(&f4);

    s.do_it();
}*/
