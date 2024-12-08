#include <iostream>
#include <thread>
#include <mutex>
#include <unistd.h>

using namespace std;

mutex counterMutex;
int counter = 0;

void foo() {
    sleep(1);
    {
        lock_guard<mutex> lock(counterMutex);
        counter++;
        cout << counter << endl;
    }
}

int main() {
    thread threads[20];
    for (int i = 0; i < 20; i++) {
        threads[i] = thread(foo);
    }
    for (int i = 0; i < 20; i++) {
        threads[i].join();
    }

    cout << "Final counter value: " << counter << endl;
    return 0;
}
