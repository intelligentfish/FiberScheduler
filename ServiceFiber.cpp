#include "ServiceFiber.hpp"

#include <iostream>

#include "Scheduler.hpp"

/// <summary>
/// ����
/// </summary>
/// <param name="scheduler"></param>
/// <param name="canSchedule"></param>
ServiceFiber::ServiceFiber(Scheduler* scheduler, bool canSchedule)
    : Fiber(scheduler, canSchedule) {}

/// <summary>
/// ����
/// </summary>
ServiceFiber::~ServiceFiber() {}

/// <summary>
/// ����
/// </summary>
void ServiceFiber::run() {
  while (true) {
    for (auto i = 0; i < 10; i++) {
      std::cout << "fiber id: " << getId() << ", tick: " << GetTickCount64()
                << std::endl;
      Sleep(10);
    }
    // �ó�����Ȩ
    yield();
  }
}
