/**
 * std::shared_ptr is a smart pointer that retains shared ownership of an object through a pointer. 
 * Several shared_ptr objects may own the same object. 
 * The object is destroyed and its memory deallocated when either of the following happens:
 *  - the last remaining shared_ptr owning the object is destroyed;
 *  - the last remaining shared_ptr owning the object is assigned another pointer via operator= or reset(). 
 */
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include <mutex>

struct Base
{
    Base() { std::cout << "Base::Base()\n"; }
    // Note: non-virtual destructor is OK here
    ~Base() { std::cout << "Base::~Base()\n"; }
};

struct Derived : public Base
{
    Derived() { std::cout << "Derived::Derived()\n"; }
    ~Derived() { std::cout << "Derived::~Derived()\n"; }
};

void thr(std::shared_ptr<Base> p)
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::shared_ptr<Base> lp = p; // thread-safe, even though the shared use_count is incremented
    {
        static std::mutex io_mutex;
        std::lock_guard<std::mutex> lk(io_mutex);
        std::cout << "Local pointer in a thread: \n"
                  << "\t lp.get() = " << lp.get()
                  << ", lp.use_count() = " << lp.use_count() << std::endl;
    }
}

int main()
{
    std::shared_ptr<Base> p = std::make_shared<Derived>();

    std::cout << "Created a shared Derived (as a pointer to Base)\n"
              << "\tp.get() = " << p.get()
              << "\tp.use_count() = " << p.use_count() << std::endl;

    std::thread t1(thr, p);
    std::thread t2(thr, p);
    std::thread t3(thr, p);

    p.reset(); // release ownership from main

    std::cout << "Shared ownership between 3 threads and released\n"
              << "\townership from main: "
              << "p.get() = " << p.get()
              << ", p.use_count() = " << p.use_count() << std::endl;

    t1.join();
    t2.join();
    t3.join();

    std::cout << "All threads completed, the last one detected Derived\n";

    return 0;
}