#include <experimental/loop_scheduler>
#include <experimental/timer>
#include <experimental/yield>
#include <iostream>

using std::experimental::dispatch;
using std::experimental::dispatch_after;
using std::experimental::loop_scheduler;
using std::experimental::yield_context;

int main()
{
  loop_scheduler scheduler;
  auto executor = scheduler.get_executor();

  dispatch(
    wrap(executor,
      [](yield_context yield)
      {
        for (int i = 0; i < 10; ++i)
        {
          dispatch_after(std::chrono::seconds(1), yield);
          std::cout << i << std::endl;
        }
      }
    ));

  scheduler.run();
}
