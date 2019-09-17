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
* Without creating explicit threads <br><br>
Promise:
* Contains a Future
#### Future
```cpp
#include<future>
int asyncFunc(int value){
    cout << "Async Thread =>" << this_thread::get_id()<< '\n';
    cout << "I am inside a async..." << '\n';
    
    return value + 1000;
}

int main(){
    cout << "Main Thread =>" << this_thread::get_id() << '\n';
    future<int> fn = async(launch::async, asyncFunc, 200); //launch::async launch the function in async ways

    if(fn.valid()) //Gate can only get once, check if the return value has already got
        cout << fn.get() << '\n'; 
    
    if(fn.valid())
        cout << fn.get() << '\n';
    else
        cout << "Invalid gate" << '\n';
    return 0;
}
```
Using 'launch::async' means call the function asynchronous. <br>
Using 'launch::deffered' means call the function when we call the gate, means function works in the same thread with main funcion.
#### Promise
![](https://thispointer.com/wp-content/uploads/2015/06/promise.png)
```cpp
void ThrdFunc(promise<int>& prom){ // In the thread function, set the value in promise
    this_thread::sleep_for(chrono::seconds(2));
    prom.set_value(200);
}

int main(){
    promise<int> mypromise;  //Create a promise 
    future<int> fut = mypromise.get_future();   //Create a future in that promise
    cout << "Main..." << '\n';
    thread t1 {ThrdFunc, ref(mypromise)}; // Pass the promise to the Thread t1(the second thread) funcion.

    cout << "Main Thread =>" << fut.get() << '\n'; // Call the future(Call thread function to return value)
    t1.join();
    return 0;
}
```
## Mutex(Mutual Exclusion)
```cpp
#include<mutex>
void ThreadFn( mutex & mtx){
    lock_guard<mutex> lock(mtx);
    cout << "I locked the Mutex..." << '\n';
    this_thread::sleep_for(chrono::seconds(5)); // Lock for 5 seconds
}

int main(){
    mutex mtx; //Create a mutex
    thread th { ThreadFn, ref(mtx)}; //Pass the mutex to thread function by reference   
    this_thread::sleep_for(chrono::seconds(1)); // Wait for the thread function to lock
    unique_lock<mutex> lock(mtx); //Wait till the thread function unlock the mutex
    cout << "I am inside the Main Thread..." << '\n';

    th.join();
    return 0;
}
```
Noted that 'lock_guard' can only lock, while 'unique_lock' can lock 'lock.lock()' and unlock 'lock.unlock()'.
## Condition Variables
```cpp
void ThrdFn(mutex & mtx, condition_variable & convar){
    unique_lock<mutex> lock(mtx);
    convar.wait(lock); // Compare  with wating for some boolean become true(take 100% CPU), this take 0% and this will unlock the mutex
    ///....
    cout << "End of the thread.." << '\n';
}

int main(){
    mutex mtx;
    condition_variable convar; // Create the condition variable
    thread th{ ThrdFn, ref(mtx), ref(convar)};
    this_thread::sleep_for(chrono::seconds(5)); // While main thread sleep, lock the ThrdFn thread.

    {
        lock_guard<mutex> lg(mtx); // Because convar.wait(lock) unlock the mutex, here we can lock the mutex
        convar.notify_all(); // Notify the convar nolonger wait
    }

    th.join();
    cout << "End of Code.." << '\n';
}
```
