///////////////////////////////////////////////////////////////////////////////
/// Class Implementations
///////////////////////////////////////////////////////////////////////////////

#include "class.hpp"
#include <iostream>
#include <future>

/* ------------------------------------------------------------------------- */
/// Method : async::period::update()
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */

void async::period::update() {

  current_time  = std::chrono::steady_clock::now();
  elapsed_time += std::chrono::duration_cast<std::chrono::milliseconds>
                  (current_time - last_time).count();
  last_time = current_time;

  if (elapsed_time > nduration.count()) {
    elapsed_time = 0.00;
    f_flag = f_active;
  }

}

/* ------------------------------------------------------------------------- */
/// Method : async::period::push(func_t func)
/* ------------------------------------------------------------------------- */

void async::period::push(func_t func) {
  f_push_array[f_flag](f_queue, func);
}

/* ------------------------------------------------------------------------- */

void async::period::push_idle(std::queue<func_t>& f_queue, func_t func) {}
void async::period::push_active(std::queue<func_t>& f_queue, func_t func) {
  f_queue.push(func); 
}

/* ------------------------------------------------------------------------- */
/// Method : async::period::flush()
/* ------------------------------------------------------------------------- */

void async::period::flush() {
  f_flush_array[f_flag](f_queue);
  f_flag = f_idle;
}

/* ------------------------------------------------------------------------- */

void async::period::flush_idle(std::queue<func_t>& f_queue) {
  std::cout<<"idling."<<std::endl;
}
void async::period::flush_active(std::queue<func_t>& f_queue) {
  auto async_task = std::async(std::launch::async, [&f_queue]() {
    while (!f_queue.empty()) {
      f_queue.front()();
      f_queue.pop();
    }
  });
}

///////////////////////////////////////////////////////////////////////////////
/// End
///////////////////////////////////////////////////////////////////////////////
