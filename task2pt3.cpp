#include <iostream>
#include "fiber.hpp"
#include "scheduler.hpp"

scheduler s; // Global scheduler instance

// Fiber function 1
void func1() {
    std::cout << "fiber 1" << std::endl;
    int* dp = static_cast<int*>(s.get_current_fiber()->get_data());
    if (dp) {
        std::cout << "fiber 1: " << *dp << std::endl;
        *dp += 1;
    }
    s.fiber_exit();
}

// Fiber function 2
void func2() {
    int* dp = static_cast<int*>(s.get_current_fiber()->get_data());
    if (dp) {
        std::cout << "fiber 2: " << *dp << std::endl;
    }
    s.fiber_exit();
}
int main() {
    // Shared data between fibers
    int d = 10;

    // Create fibers with shared data
    fiber f1(func1, &d);
    fiber f2(func2, &d);

    // Add fibers to the scheduler
    s.spawn(&f1);
    s.spawn(&f2);

    // Execute the fibers
    s.do_it();

    return 0;
}

