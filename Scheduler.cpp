#include "Scheduler.hpp"

/// <summary>
/// 构造
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <param name="env"></param>
Scheduler::Scheduler(int argc, char** argv, char** env)
    : Fiber(nullptr, false), _argc(argc), _argv(argv), _env(env) {}

/// <summary>
/// 析构
/// </summary>
Scheduler::~Scheduler() {}

/// <summary>
/// 运行
/// </summary>
void Scheduler::run() {
  // 创建两个协程测试
  for (auto i = 0; i < 10; i++) {
    Fiber* ctx = new ServiceFiber(this, true);
    ctx->setHandle(CreateFiber(0, &Fiber::entry, ctx));
    if (nullptr == ctx->getHandle()) continue;
    _fiberList.push_back(ctx);
  }
  schedule();
}

/// <summary>
/// 调度
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
    // 唤醒第一个
    for (auto it = _fiberList.begin(); _fiberList.end() != it; it++)
      (*it)->_canSchedule = true;
    (*_fiberList.begin())->resume();
  }
}