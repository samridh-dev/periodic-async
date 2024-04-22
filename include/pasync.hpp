#ifndef ASYNC_CLASS_HPP
#define ASYNC_CLASS_HPP

#include <chrono>
#include <array>
#include <queue>
#include <functional>

namespace pasync {

///////////////////////////////////////////////////////////////////////////////
/// Class Scheduler
///////////////////////////////////////////////////////////////////////////////

class scheduler {

  using func_t = std::function<void()>;

public:

  template <typename T>
  scheduler(const T& _nduration);
  
  /// update clock
  void update();
  
  // push functions to queue per nseconds
  void push(func_t func);

  // run enqueued functions per nseconds
  void flush();
  
private:

  // time Variables
  double elapsed_time;
  std::chrono::milliseconds nduration;
  std::chrono::steady_clock::time_point last_time;
  std::chrono::steady_clock::time_point current_time;

  // scheduleric Function Variables
  enum { f_idle = 0, f_active = 1 } f_flag;
  std::queue<func_t> f_queue;
  
  // Push Method Internals
  static void flush_idle(std::queue<func_t>& f_queue);
  static void flush_active(std::queue<func_t>& f_queue);
  const std::array<std::function<void (
    std::queue<func_t>&
  )>, 2> f_flush_array;

  // Flush Method Internals
  static void push_idle(std::queue<func_t>& f_queue, func_t func);
  static void push_active(std::queue<func_t>& f_queue, func_t func);
  const std::array<std::function< void (
    std::queue<func_t>&, func_t
  )>, 2> f_push_array;
    
};

///////////////////////////////////////////////////////////////////////////////
/// End
///////////////////////////////////////////////////////////////////////////////
} // namespace async
#include "impl.ipp"
#endif
