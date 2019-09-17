//
// Created by homsl on 2019/9/16.
//
#include <iostream>
#include <thread>

using namespace std;

//void threadFn(int& value){
//    cout << "I am inside a thread function" << '\n';
//    cout << "Value => " <<value++<<'\n';
//}

int main(){
    int localValue = 200;
    int value2 = 100;
    thread t1{[&](){
        cout << "I am inside a thread function" << '\n';
        cout << "Value => " <<localValue++<<'\n';
        value2++;
        }};

    t1.join();
    cout << "Value in Main Thread => " <<localValue<<'\n';
    cout << "Value2 in Main Thread => " <<value2<<'\n';
    return 0;
}