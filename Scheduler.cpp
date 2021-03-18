#include "Scheduler.hpp"

/// <summary>
/// ����
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <param name="env"></param>
Scheduler::Scheduler(int argc, char** argv, char** env)
    : Fiber(nullptr, false), _argc(argc), _argv(argv), _env(env) {}

/// <summary>
/// ����
/// </summary>
Scheduler::~Scheduler() {}

/// <summary>
/// ����
/// </summary>
void Scheduler::run() {
  // ��������Э�̲���
  for (auto i = 0; i < 10; i++) {
    Fiber* ctx = new ServiceFiber(this, true);
    ctx->setHandle(CreateFiber(0, &Fiber::entry, ctx));
    if (nullptr == ctx->getHandle()) continue;
    _fiberList.push_back(ctx);
  }
  schedule();
}

/// <summary>
/// ����
/// </summary>
void Scheduler::schedule() {
  auto flag = true;
  for (auto it = _fiberList.begin();
       _fiberList.end() != it && nullptr != (*it)->getHandle();) {
    if ((*it)->_finished) {
      delete (*it);
      it = _fiberList.erase(it);
      continue;
    }
    if ((*it)->_canSchedule) {
      (*it)->resume();
      flag = false;
    }
    it++;
  }
  if (flag && 0 < _fiberList.size()) {
    // ���ѵ�һ��
    for (auto it = _fiberList.begin(); _fiberList.end() != it; it++)
      (*it)->_canSchedule = true;
    (*_fiberList.begin())->resume();
  }
}