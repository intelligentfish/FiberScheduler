#include "Fiber.hpp"

#include <atomic>
#include <iostream>

#include "Scheduler.hpp"

/// <summary>
/// Fiber入口
/// </summary>
void WINAPI Fiber::entry(LPVOID param) {
  auto self = static_cast<Fiber*>(param);
  self->run();
  // 设置完成标志并调度
  self->_canSchedule = false;
  self->_finished = true;
  self->_scheduler->schedule();
}

/// <summary>
/// 构造
/// </summary>
/// <param name="scheduler"></param>
/// <param name="canSchedule"></param>
Fiber::Fiber(Scheduler* scheduler, bool canSchedule)
    : _handle(),
      _scheduler(scheduler),
      _canSchedule(canSchedule),
      _finished(),
      _id() {
  static std::atomic_int _nextId;
  _id = std::atomic_fetch_add(&_nextId, 1);
}

/// <summary>
/// 析构
/// </summary>
Fiber ::~Fiber() {
  //if (_handle) DeleteFiber(_handle);
}

/// <summary>
/// 设置句柄
/// </summary>
/// <param name="handle">句柄</param>
/// <returns>Fiber引用</returns>
Fiber& Fiber::setHandle(LPVOID handle) {
  _handle = handle;
  return *this;
}

/// <summary>
/// 获取句柄
/// </summary>
/// <returns>句柄</returns>
LPVOID Fiber::getHandle() const { return _handle; }

/// <summary>
/// 获取ID
/// </summary>
/// <returns></returns>
int Fiber::getId() const { return _id; }

/// <summary>
/// 让出执行权
/// </summary>
void Fiber::yield() {
  _canSchedule = false;
  _scheduler->schedule();
}

/// <summary>
/// 恢复
/// </summary>
void Fiber::resume() {
  _canSchedule = true;
  SwitchToFiber(_handle);
}