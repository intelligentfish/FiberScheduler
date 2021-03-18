#include "ServiceFiber.hpp"

#include <iostream>

#include "Scheduler.hpp"

/// <summary>
/// 构造
/// </summary>
/// <param name="scheduler"></param>
/// <param name="canSchedule"></param>
ServiceFiber::ServiceFiber(Scheduler* scheduler, bool canSchedule)
    : Fiber(scheduler, canSchedule) {}

/// <summary>
/// 析构
/// </summary>
ServiceFiber::~ServiceFiber() {}

/// <summary>
/// 运行
/// </summary>
void ServiceFiber::run() {
  while (true) {
    for (auto i = 0; i < 10; i++) {
      std::cout << "fiber id: " << getId() << ", tick: " << GetTickCount64()
                << std::endl;
      Sleep(10);
    }
    // 让出调度权
    yield();
  }
}
