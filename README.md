# MultiThread
## Learning C++11 Lambda
---
 #### Valid Lambda Syntax: <br>
 ```cpp
 [](){};//[Capture List](Function Arguments){Function Body}:
 ```
 #### Defining and Calling a Lambda
 ```cpp
 int main(){
   [](){
     cout << "I'm inside a lambda function" <<'\n';
   }(); // This "()" will invoke the lambda function
  
 return 0;
 }
 ```
 #### Lambda with a function argument
  ```cpp
 int main(){
   [](int value){ // Lambda taking arguments like normal funcions
     cout << "I'm inside a lambda function, value = " << value <<'\n';
   }(100); // Passing argument to lambda like normal functions
  
 return 0;
 }
 ```
 #### Naming a Lambda (Using auto key)
 ```cpp
 int main(){
   auto mylam = [](){
     cout << "This lambda is called using the name" << '\n';
   }
   //Call the lambda funcion
   mylam();
 }
 
    auto mylam = [](int value){
     cout << "This lambda is called using the name" << '\n';
   }
   //Call the lambda funcion with parameter
   mylam(100);
   ```
 #### Naming a Lambda (Using std::fuction<>)
 ```cpp
  int main(){
    function<void(int)> mylam = [](int value){
      cout << "This lambda is called using the name" << '\n';
    }
  //Call the lambda funcion
  mylam(200);
 }
 ```
 #### Using old 'C' style function pointer
 ```cpp
 void(*cstylefp)(int) = [](int value){
   cout << "The value in this function is ->" << value << '\n';
 }
 //Call the function pointer
 cstylefp(300);
 ```
#### Using Capture List
"[]" It captures the local scope variables to be used inside the lambda function.
##### Captured by Value
```cpp
int main(){
  int val = 100;  //Local variables
  int i = 1;  
  
  [=](){ //"=" means passing all variables by value
    cout << "Value is ->" << val << '\n' << "i is ->" << i << '\n';
    // Values can be accessed inside the function without explicit passing
  }();
  
}
```
##### Captured by Reference
```cpp
int main(){
  int val = 100;  //Local variables
  int i = 1;  
  
  [&](){ //"&" means passing all variables by reference
    cout << "Value is ->" << val++ << '\n' << "i is ->" << i++ << '\n';
    // Values can be accessed inside the function without explicit passing
  }();
  
}
```
##### Captured by Value and Reference
```cpp
int main(){
  int val = 100;  //Local variables
  int i = 1;  
  
  [val,&i](){ //Passing val by value, passing i by reference
    cout << "Value is ->" << val++ << '\n' << "i is ->" << i++ << '\n';
    // Values can be accessed inside the function without explicit passing
  }();
  
}
```
## Multithreading in C++ <br><br>
### Creating & Managing Threads<br><br>
##### Creating Threads
```cpp
#include<thread>
...
thread t1();
thread t2{};// Either "()" or "{}"

t1.join();
t2.join(); // Stop the thread
```
##### Calling Function in Thread
```cpp
thread t1{threadfn}; // No "()" followed by "threadfn";
```
##### Passing Value to Function in Thread
```cpp
thread t1{threadfn, value}; // Passing by value
thread t2{threadfn, ref(value)}; // Passing by reference
```
##### Using Lambda Function in Thread
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
### Thread and Templates & STL

