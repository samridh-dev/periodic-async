/////////////////////////////////////////////////////////////////////////////// 
/// Template Implementations
/////////////////////////////////////////////////////////////////////////////// 

template <typename T>
pasync::scheduler::scheduler(const T& _nduration) :

  nduration(std::chrono::duration_cast<std::chrono::milliseconds>(_nduration)),
  elapsed_time(0),
  last_time(std::chrono::steady_clock::now()),
  current_time(std::chrono::steady_clock::now()),

  f_flag(f_idle),
  f_queue(),

  f_flush_array({flush_idle, flush_active}),
  f_push_array({push_idle, push_active})

{}   

///////////////////////////////////////////////////////////////////////////////
/// End
///////////////////////////////////////////////////////////////////////////////
