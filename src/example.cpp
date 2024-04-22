#include <pasync.hpp>
#include <iostream>
#include <thread>

void a() { std::cout<<"function a"<<std::endl; }
void b() { std::cout<<"function b"<<std::endl; }
void c() { std::cout<<"function c"<<std::endl; }

int main() {

  class pasync::scheduler scheduler(std::chrono::seconds(3));

  auto beg = std::chrono::high_resolution_clock::now();

  for (auto j = 0; j < 50; j++) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    
    // update scheduler counter
    scheduler.update();
    
    // push functions to scheduler
    const int i = 49;
    scheduler.push([=]() {
      std::cout << "lambda function with parameter : " << i << std::endl;
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    });
    scheduler.push(a);
    scheduler.push(c);
    scheduler.push(b);
    
    // run functions only after nseconds since last run
    scheduler.flush();
  }

  auto end = std::chrono::high_resolution_clock::now();
  auto dur = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg);

  std::cout << "Execution Time : " 
            << dur.count() / 1000. << " seconds" 
            << std::endl;

  return 0;
}
