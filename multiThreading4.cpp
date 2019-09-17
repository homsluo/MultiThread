//
// Created by homsl on 2019/9/16.
//
#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

void ThreadFn( mutex & mtx){
    lock_guard<mutex> lock(mtx);
    cout << "I locked the Mutex..." << '\n';
    this_thread::sleep_for(chrono::seconds(5));
}

int main(){
    mutex mtx;
    thread th { ThreadFn, ref(mtx)};
    this_thread::sleep_for(chrono::seconds(1));
    unique_lock<mutex> lock(mtx);
    cout << "I am inside the Main Thread..." << '\n';
    lock.unlock();
    lock.lock();

    th.join();
    return 0;
}