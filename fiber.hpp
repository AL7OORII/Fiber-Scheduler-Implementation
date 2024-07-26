#include <iostream>
#include <cstdint>
#include "context/context.hpp"

class fiber {
    private:
        Context context_;
        char* stack_bottom_;
        char* stack_top_;
        void* data_ptr_;

    public:
        fiber(void (*function)(), void* data_ptr = nullptr) : data_ptr_(data_ptr) {
            // Allocate space for the stack
            stack_bottom_ = new char[4096];
            stack_top_ = stack_bottom_ + 4096;

            // Align the stack to 16 bytes and account for the Red Zone
            stack_top_ = (char*)((uintptr_t)(stack_top_) & -16L) - 128;

            // Set up the context
            context_.rip = (void*)function;
            context_.rsp = stack_top_;
        }

        ~fiber() {
            delete[] stack_bottom_;
        }

        Context* get_context() const {
            return &context_;
        }

        void* get_data() const {
            return data_ptr_;
        }
        
    };
