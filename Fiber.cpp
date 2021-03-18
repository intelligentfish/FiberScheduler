#include "Fiber.hpp"

#include <atomic>
#include <iostream>

#include "Scheduler.hpp"

/// <summary>
/// Fiber���
/// </summary>
void WINAPI Fiber::entry(LPVOID param) {
  auto self = static_cast<Fiber*>(param);
  self->run();
  // ������ɱ�־������
  self->_canSchedule = false;
  self->_finished = true;
  self->_scheduler->schedule();
}

/// <summary>
/// ����
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
/// ����
/// </summary>
Fiber ::~Fiber() {
  //if (_handle) DeleteFiber(_handle);
}

/// <summary>
/// ���þ��
/// </summary>
/// <param name="handle">���</param>
/// <returns>Fiber����</returns>
Fiber& Fiber::setHandle(LPVOID handle) {
  _handle = handle;
  return *this;
}

/// <summary>
/// ��ȡ���
/// </summary>
/// <returns>���</returns>
LPVOID Fiber::getHandle() const { return _handle; }

/// <summary>
/// ��ȡID
/// </summary>
/// <returns></returns>
int Fiber::getId() const { return _id; }

/// <summary>
/// �ó�ִ��Ȩ
/// </summary>
void Fiber::yield() {
  _canSchedule = false;
  _scheduler->schedule();
}

/// <summary>
/// �ָ�
/// </summary>
void Fiber::resume() {
  _canSchedule = true;
  SwitchToFiber(_handle);
}