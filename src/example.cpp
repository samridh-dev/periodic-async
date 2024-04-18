#include "class.hpp"
#include <iostream>
#include <thread>

void a() { std::cout<<"function a"<<std::endl; }
void b() { std::cout<<"function b"<<std::endl; }
void c() { std::cout<<"function c"<<std::endl; }

int main() {

  class async::period period(std::chrono::seconds(3));

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    // update period counter
    period.update();
    
    // push functions to period
    const int i = 49;
    period.push([=]() {
      std::cout << "lambda function with parameter : " << i << std::endl;
    });
    period.push(a);
    period.push(c);
    period.push(b);
    
    // run functions only after nseconds since last run
    period.flush();
  }

  return 0;
}

