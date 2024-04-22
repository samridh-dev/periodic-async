///////////////////////////////////////////////////////////////////////////////
/// Class Implementations
///////////////////////////////////////////////////////////////////////////////

#include <pasync.hpp>
#include <iostream>
#include <future>

/* ------------------------------------------------------------------------- */
/// Method : pasync::scheduler::update()
/* ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- */

void pasync::scheduler::update() {

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
/// Method : pasync::scheduler::push(func_t func)
/* ------------------------------------------------------------------------- */

void pasync::scheduler::push(func_t func) {
  f_push_array[f_flag](f_queue, func);
}

/* ------------------------------------------------------------------------- */

void pasync::scheduler::push_idle(std::queue<func_t>& f_queue, func_t func) {}
void pasync::scheduler::push_active(std::queue<func_t>& f_queue, func_t func) {
  f_queue.push(func); 
}

/* ------------------------------------------------------------------------- */
/// Method : pasync::scheduler::flush()
/* ------------------------------------------------------------------------- */

void pasync::scheduler::flush() {
  f_flush_array[f_flag](f_queue);
  f_flag = f_idle;
}

/* ------------------------------------------------------------------------- */

void pasync::scheduler::flush_idle(std::queue<func_t>& f_queue) {
  std::cout<<"idling."<<std::endl;
}
void pasync::scheduler::flush_active(std::queue<func_t>& f_queue) {
  std::thread remote_thread([&f_queue]() {
    while (!f_queue.empty()) {
      f_queue.front()();
      f_queue.pop();
    }
  });
  remote_thread.detach();
}

///////////////////////////////////////////////////////////////////////////////
/// End
///////////////////////////////////////////////////////////////////////////////
