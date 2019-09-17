//
// Created by homsl on 2019/9/16.
//
#include <iostream>
#include <thread>
#include <future>

using namespace std;

void ThrdFunc(promise<int>& prom){
    this_thread::sleep_for(chrono::seconds(2));
    prom.set_value(200);
}

int main(){
    promise<int> mypromise;
    future<int> fut = mypromise.get_future();
    cout << "Main..." << '\n';
    thread t1 {ThrdFunc, ref(mypromise)};

    cout << "Main Thread =>" << fut.get() << '\n';
    t1.join();
    return 0;
}