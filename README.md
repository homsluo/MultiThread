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
#### Get the Threads' ID
```cpp
void threadFn(){
    cout << "I am inside a thread function" << '\n';
    cout << this_thread::get_id()<<'\n'; // Get the thread id of threadFn
}

int main(){

    thread t1 {threadFn};
    cout << this_thread::get_id()<<'\n'; // Get the thread id of main function
    t1.join();

    return 0;
}
```
#### Template Thread Funcion
```cpp
template<typename Type>
void threadFn(){
    cout << "Type is =>" << typeid(Type).name() << '\n';
}

int main(){
    thread t1 {threadFn<int>};
    this_thread::sleep_for(chrono::milliseconds(1000)); // Make sure two threads output seperately
    thread t2 {threadFn<float>};
    
    t1.join();
    t2.join();
    return 0;
}
```
#### Apply STL in Thread Function
```cpp
#include<initializer_list>
#include<vector> // Can use vector replace all initializer_list

void threadFn(initiailizer_list<int> il){
    cout << "Size of the list =>" << il.size() << '\n';
}

int main(){
    initializer_list<int> il = {1,2,3,4,5}; 

    thread t1 {threadFn, il}; // Can't use implicit expression like: {threadFn, {1,2,3,4}};

    t1.join;

    return 0;
}
```
## Future & Promise
Future:
* Async Programming
* Without creating explicit threads
<br>
Promise:
* Contains a Future
