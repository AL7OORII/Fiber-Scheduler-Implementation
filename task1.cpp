#include <iostream>
#include <cstdint>
#include "context/context.hpp"

volatile int x = 0;
Context mainContext, fooContext, gooContext;


void foo();
void goo();

void switch_to_foo() {
    get_context(&mainContext);  // Save the current context (main)
    if (x == 0) {
        x = 1;                  // Mark that foo has been called
        set_context(&fooContext); // Switch to foo
    }
}

void switch_to_goo() {
    get_context(&fooContext);   // Save the current context (foo)
    set_context(&gooContext);   // Switch to goo
}

void foo() {
    std::cout << "you called foo" << std::endl;
    switch_to_goo();           // Switch to goo from foo
}

void goo() {
    std::cout << "you called goo" << std::endl;
    set_context(&mainContext);  // Switch back to main
}

int main() {
    // Allocate space for stack
    char fooStack[4096], gooStack[4096];

    // Stacks grow downwards
    char* fooSp = fooStack + 4096;
    char* gooSp = gooStack + 4096;

    // Align the stack to 16 bytes
    fooSp = (char*)((uintptr_t)(fooSp) & -16L);
    gooSp = (char*)((uintptr_t)(gooSp) & -16L);

    // Account for the Red Zone
    fooSp = fooSp - 128;
    gooSp = gooSp - 128;

    // Set up context for foo
    fooContext.rip = (void*)foo;
    fooContext.rsp = fooSp;

    // Set up context for goo
    gooContext.rip = (void*)goo;
    gooContext.rsp = gooSp;

    // Start by switching to foo
    switch_to_foo();

    return 0;
}
