#include <iostream>
#include <thread>
#include <chrono>
#include <semaphore>
#include <future>

using namespace std;

binary_semaphore semaphoreMain(0);
binary_semaphore semaphoreParallel(0);

void parallelThread()
{
    for (int i = 0; i < 10; i++)
    {
        semaphoreMain.acquire();
        
        cout << "\t" << this_thread::get_id() << " " << i << "\n";
        this_thread::sleep_for(500ms);
        semaphoreParallel.release();
    }
        
}

int Counter(int n)
{
    int counter{};
    for (int i = 1; i <= n; i++)
    {
        counter += i;
        this_thread::sleep_for(50ms);
    }
        
    return counter;
}

int main()
{
    /*
    thread th1(parallelThread);

    for (int i = 0; i < 10; i++)
    {
        semaphoreMain.release();
        semaphoreParallel.acquire();
        cout << this_thread::get_id() << " " << i << "\n";
        this_thread::sleep_for(500ms);
    }

    th1.join();
    */

    future<int> res1;
    
    res1 = async(Counter, 100);
    auto res2 = async(Counter, 50);

    //res1.wait();
    //res2.wait();

    auto v1 = async([&res1]() {cout << res1.get() << "\n"; });
    auto v2 = async([&res2]() {cout << res2.get() << "\n"; });
    
    //cout << res2.get() << "\n";

    
}
