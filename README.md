# MultiThread in C++ <br><br>
## Creating & Managing Threads<br><br>
#### Creating Threads
```cpp
#include<thread>
...
thread t1();
thread t2{};// Either "()" or "{}"

t1.join();
t2.join(); // Stop the thread
```
#### Calling Function in Thread
```cpp
thread t1{threadfn}; // No "()" followed by "threadfn";
```
#### Passing Value to Function in Thread
```cpp
thread t1{threadfn, value}; // Passing by value
thread t2{threadfn, ref(value)}; // Passing by reference
```
#### Using Lambda Function in Thread
```cpp
/*
void threadFn(int& value){
    cout << "I am inside a thread function" << '\n';
    cout << "Value => " <<value++<<'\n';
}
*/

int main(){
    int localValue = 200;
    int value2 = 100;
    
    thread t1{[&](){ // Passing all local value by reference
        cout << "I am inside a thread function" << '\n';
        cout << "Value => " <<localvalue++<<'\n';
        value2++;
        }};

    t1.join();
    cout << "Value in Main Thread => " <<localValue<<'\n';
    cout << "Value2 in Main Thread => " <<value2<<'\n';
    return 0;
}
```
<br><br>
## Thread and Templates & STL

