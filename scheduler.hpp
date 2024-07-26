#include <iostream>
#include <deque>

class scheduler {
private:
    std::deque<fiber*> fibers_; // Queue of fibers
    Context context_; // Context for the scheduler
    fiber* current_fiber_;

public:
    scheduler(){
        std::deque<fiber*> fibers_;
    }

    void spawn(fiber* f) {
        fibers_.push_back(f); // Add the new fiber to the end of the queue
    }

    void do_it() {
        get_context(&context_); // Save the scheduler context for returning after fibers complete

        while (!fibers_.empty()) { // As long as there are fibers to execute
            current_fiber_ = fibers_.front(); // Set the current fiber
            fibers_.pop_front();

            const Context* fiber_ctx_ptr = current_fiber_->get_context_ptr();
            set_context(fiber_ctx_ptr);  // Use the pointer directly
        }
    }

    void fiber_exit() {
        // Return control to the scheduler
        set_context(&context_);
    }

    fiber* get_current_fiber() const {
        return current_fiber_;
    }

};

    
