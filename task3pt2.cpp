#include <iostream>
#include "fiber.hpp"
#include "scheduler.hpp"

// Global scheduler instance
scheduler s;

// Shared data
int sharedData = 0;

// Forward declaration of fibers
fiber* f1_ptr;
fiber* f2_ptr;

// Fiber functions
void func1(fiber* f);
void func2(fiber* f);

// Wrapper functions
void func1_wrapper() {
    func1(f1_ptr);
}

void func2_wrapper() {
    func2(f2_ptr);
}

int main() {
    // Create fibers
    fiber f1(func1_wrapper);
    fiber f2(func2_wrapper, &sharedData);

    // Assign pointers
    f1_ptr = &f1;
    f2_ptr = &f2;

    // Spawn fibers
    s.spawn(&f1);
    s.spawn(&f2);

    // Execute fibers
    s.do_it();

    return 0;
}

void func1(fiber* f) {
    std::cout << "fiber 1 before: sharedData = " << sharedData << std::endl;

    // Increment sharedData
    sharedData++;

    // Yield control to other fibers
    f->yield();

    std::cout << "fiber 1 after: sharedData = " << sharedData << std::endl;
    f->fiber_exit();
}

void func2(fiber* f) {
    // Access shared data
    int* dataPtr = static_cast<int*>(f->get_data());

    std::cout << "fiber 2: sharedData = " << *dataPtr << std::endl;
    f->fiber_exit();
}

