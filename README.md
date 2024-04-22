# periodic-async
A library to run generic code periodically and asynchronously

## Installation
Currently only source installation is possible.
This run script will be sufficient to generate a working executable. Edit as
you see fit.

NOTE: to configure the project, refer to the /cmake/config.cmake file.

```bash
REPO_NAME="periodic-async"
git clone https://github.com/samridh-dev/periodic-async.git $REPO_NAME
pushd $REPO_NAME
git submodule update --init --recursive
mkdir -p bin/ dat/
mkdir -p cmake/build/
pushd cmake/build
cmake ../.. -Wdev
make -j $(nproc)
popd
```

## Usage

### Cmake usage

```cpp
#include <pasync.hpp>
#include <iostream>
#include <thread>

void a() { std::cout<<"function a"<<std::endl; }
void b() { std::cout<<"function b"<<std::endl; }
void c() { std::cout<<"function c"<<std::endl; }

const size_t iterations = 50;
const size_t pause = 100;

int main() {
    
  // Create Scheduler Class
  class pasync::scheduler scheduler(std::chrono::seconds(3));

  auto beg = std::chrono::high_resolution_clock::now();

  for (auto j = 0; j < iterations; j++) {
    std::this_thread::sleep_for(std::chrono::milliseconds(pause));
    
    // update scheduler timer
    scheduler.update();
    
    // push functions to scheduler
    const int i = 49;
    scheduler.push([=]() {
      std::cout << "Lambda function with parameter : " << i << std::endl;
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
    
  // Execution time should be (iterations * pause) seconds
  std::cout << "Execution Time : " 
            << dur.count() / 1000. << " seconds" 
            << std::endl;

  return 0;
}
```
