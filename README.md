# MultiThread
## Learning C++11 Lambda
---
 ### Valid Lambda Syntax: <br>
 ```cpp
 [](){};//[Capture List](Function Arguments){Function Body}:
 ```
 ### Defining and Calling a Lambda
 ```cpp
 int main(){
   [](){
     cout << "I'm inside a lambda function" <<'\n';
   }(); // This "()" will invoke the lambda function
  
 return 0;
 }
 ```
 ### Lambda with a function argument
  ```cpp
 int main(){
   [](int value){ // Lambda taking arguments like normal funcions
     cout << "I'm inside a lambda function, value = " << value <<'\n';
   }(100); // Passing argument to lambda like normal functions
  
 return 0;
 }
 ```
 ### Naming a Lambda (Using auto key)
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
 ### Naming a Lambda (Using std::fuction<>)
 ```cpp
  int main(){
    function<void(int)> mylam = [](int value){
      cout << "This lambda is called using the name" << '\n';
    }
  //Call the lambda funcion
  mylam(200);
 }
 ```
 ### Using old 'C' style function pointer
 ```cpp
 void(*cstylefp)(int) = [](int value){
   cout << "The value in this function is ->" << value << '\n';
 }
 //Call the function pointer
 cstylefp(300);
 ```
