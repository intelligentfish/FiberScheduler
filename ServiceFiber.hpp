#pragma once

#include "Fiber.hpp"

/// <summary>
/// 服务Fiber
/// </summary>
struct Scheduler;
struct ServiceFiber : public virtual Fiber {
  /// <summary>
  /// 构造
  /// </summary>
  /// <param name="scheduler"></param>
  /// <param name="canSchedule"></param>
  ServiceFiber(Scheduler* scheduler = nullptr, bool canSchedule = false);

  /// <summary>
  /// 析构
  /// </summary>
  virtual ~ServiceFiber();

  /// <summary>
  /// 执行
  /// </summary>
  virtual void run() override;
};
