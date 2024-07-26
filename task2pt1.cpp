#include <iostream>
#include "fiber.hpp"

volatile int x = 0;
Context mainContext; // Global context for switching back to main

void foo();
void goo();

fiber* f_goo; // Global pointer to fiber for goo, needed for switch_to_goo

void switch_to_foo() {
    get_context(&mainContext); // Save the current context (main)
    if (x == 0) {
        x = 1;                 // Mark that foo has been called
        Context foo_ctx = f_goo->get_context(); // Get context from fiber object
        set_context(&foo_ctx); // Switch to foo
    }
}

void switch_to_goo() {
    Context goo_ctx = f_goo->get_context(); // Get context from fiber object
    set_context(&goo_ctx); // Switch to goo
}

void foo() {
    std::cout << "You called foo" << std::endl;
    switch_to_goo(); // Switch to goo from foo
}

void goo() {
    std::cout << "You called goo" << std::endl;
    set_context(&mainContext); // Switch back to main
}

int main() {
    fiber f_foo(foo); // Create a fiber for foo
    fiber f_goo_local(goo); // Create a fiber for goo
    f_goo = &f_goo_local; // Assign to global pointer

    switch_to_foo(); // Start by switching to foo

    return 0;
}

