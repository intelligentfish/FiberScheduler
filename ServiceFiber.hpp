#pragma once

#include "Fiber.hpp"

/// <summary>
/// ����Fiber
/// </summary>
struct Scheduler;
struct ServiceFiber : public virtual Fiber {
  /// <summary>
  /// ����
  /// </summary>
  /// <param name="scheduler"></param>
  /// <param name="canSchedule"></param>
  ServiceFiber(Scheduler* scheduler = nullptr, bool canSchedule = false);

  /// <summary>
  /// ����
  /// </summary>
  virtual ~ServiceFiber();

  /// <summary>
  /// ִ��
  /// </summary>
  virtual void run() override;
};
