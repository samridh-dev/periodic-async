#include <iostream>

#include <thread>

// class dependencies
#include <chrono>
#include <array>
#include <queue>
#include <functional>

///////////////////////////////////////////////////////////////////////////////
/// Asynchronous Periods
///////////////////////////////////////////////////////////////////////////////

template <typename... Args>
void f(Args... args) {
  std::cout<<"args"<<std::endl;
}

namespace async {

typedef std::function<void()> function_t;

///////////////////////////////////////////////////////////////////////////////
/// Internals
///////////////////////////////////////////////////////////////////////////////

namespace internal {

/* ------------------------------------------------------------------------- */
/// Periodic Push Funcitons
/* ------------------------------------------------------------------------- */

namespace push {

/* ------------------------------------------------------------------------- */

static void idle(std::queue<function_t>& f_queue, function_t func) {}

/* ------------------------------------------------------------------------- */

static void active(std::queue<function_t>& f_queue, function_t func) {
  f_queue.push(func); 
}

/* ------------------------------------------------------------------------- */
} // namespace push

/* ------------------------------------------------------------------------- */
/// Periodic Flush Funcitons
/* ------------------------------------------------------------------------- */

namespace flush {

/* ------------------------------------------------------------------------- */

static void idle(std::queue<function_t>& f_queue) {
  std::cout<<"idling."<<std::endl;
}

/* ------------------------------------------------------------------------- */

static void active(std::queue<function_t>& f_queue) {
  std::cout<<"active."<<std::endl;
  while (!f_queue.empty()) {
    f_queue.front()();
    f_queue.pop();
  }
}

/* ------------------------------------------------------------------------- */
} // namespace flush

} // namespace internal

///////////////////////////////////////////////////////////////////////////////
/// Class Period
///////////////////////////////////////////////////////////////////////////////

class period {

public:
  
  // constructors
  period(const double _nseconds);

  /// update clock
  void update();
  
  // push functions to queue per nseconds
  void push(function_t func);

  // run enqueued functions per nseconds
  void flush();
  
private:
  
  // time Variables
  double nseconds; 
  double elapsed_time;
  std::chrono::steady_clock::time_point last_time;
  std::chrono::steady_clock::time_point current_time;

  // Periodic Function Variables
  enum { f_idle = 0, f_active = 1 } f_flag;
  std::queue<function_t> f_queue;
  
  // Switch Arrays (to prevent polling)
  const std::array<std::function<void (
    std::queue<function_t>&
  )>, 2> f_flush_array;

  const std::array<std::function< void (
    std::queue<function_t>&, 
    function_t
  )>, 2> f_push_array;
    
};

///////////////////////////////////////////////////////////////////////////////
/// Period Implementations
///////////////////////////////////////////////////////////////////////////////

/* ------------------------------------------------------------------------- */

void period::push(function_t func) {
  f_push_array[f_flag](f_queue, func);
}

/* ------------------------------------------------------------------------- */

void period::flush() {
  f_flush_array[f_flag](f_queue);
  f_flag = f_idle;
}

/* ------------------------------------------------------------------------- */

period::period(const double _nseconds) : 

  nseconds(_nseconds),
  elapsed_time(0),
  last_time(std::chrono::steady_clock::now()),
  current_time(std::chrono::steady_clock::now()),

  f_flag(f_idle),
  f_queue(),

  f_flush_array({internal::flush::idle, internal::flush::active}),
  f_push_array({internal::push::idle, internal::push::active})

{}   

/* ------------------------------------------------------------------------- */

void period::update() {

  current_time  = std::chrono::steady_clock::now();
  elapsed_time += std::chrono::duration_cast<std::chrono::milliseconds>
                  (current_time - last_time).count();
  last_time = current_time;

  if (elapsed_time > (nseconds * 1000)) {
    elapsed_time = 0.00;
    f_flag = f_active;
  }

}

/* ------------------------------------------------------------------------- */
} // namespace async

///////////////////////////////////////////////////////////////////////////////
/// Example
///////////////////////////////////////////////////////////////////////////////

void a() { std::cout<<"function a"<<std::endl; }
void b() { std::cout<<"function b"<<std::endl; }
void c() { std::cout<<"function c"<<std::endl; }

int main() {

  class async::period period(2);

  while (true) {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    
    // update period counter
    period.update();
    
    // push functions to period
    period.push(a);
    period.push(c);
    period.push(b);
    
    // run functions only after nseconds since last run
    period.flush();
  }

  return 0;
}

///////////////////////////////////////////////////////////////////////////////
/// End
///////////////////////////////////////////////////////////////////////////////
