#include <iostream>
#include "fiber.hpp"
#include "scheduler.hpp"

scheduler s;

void func1(fiber* f);
void func2(fiber* f);

// Global pointers for fibers
fiber* f1_ptr = nullptr;
fiber* f2_ptr = nullptr;

// Wrapper functions
static void func1_wrapper() {
    func1(f1_ptr);
}

static void func2_wrapper() {
    func2(f2_ptr);
}

void func1(fiber* f) {
    std::cout << "fiber 1 before" << std::endl;
    f->yield();
    std::cout << "fiber 1 after" << std::endl;
    f->fiber_exit();
}

void func2(fiber* f) {
    std::cout << "fiber 2" << std::endl;
    f->fiber_exit();
}


int main() {
    fiber f1(func1_wrapper);
    fiber f2(func2_wrapper);

    // Assign the global pointers
    f1_ptr = &f1;
    f2_ptr = &f2;

    s.spawn(&f1);
    s.spawn(&f2);

    s.do_it();

    return 0;
}



