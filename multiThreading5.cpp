//
// Created by homsl on 2019/9/17.
//
#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
using namespace std;

void ThrdFn(mutex & mtx, condition_variable & convar){
    unique_lock<mutex> lock(mtx);
    convar.wait(lock);
    ///....
    cout << "End of the thread.." << '\n';
}

int main(){
    mutex mtx;
    condition_variable convar;
    thread th{ ThrdFn, ref(mtx), ref(convar)};
    this_thread::sleep_for(chrono::seconds(5));

    {
        lock_guard<mutex> lg(mtx);
        convar.notify_all();
    }

    th.join();
    cout << "End of Code.." << '\n';
}