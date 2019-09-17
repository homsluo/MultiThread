//
// Created by homsl on 2019/9/16.
//
#include <iostream>
#include <thread>
#include <initializer_list>
#include <vector>

using namespace std;

void threadFn(initializer_list<int> il){
    cout << "size of list = >" << il.size()<<'\n';
}

int main(){
    initializer_list<int> il = {1,2,3,4,5,6};

    thread t1 {threadFn, il};

    t1.join();

    return 0;
}

