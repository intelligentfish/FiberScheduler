#pragma once

#include <list>
#include <memory>

#include "ServiceFiber.hpp"

/// <summary>
/// Fiber上下文
/// </summary>
struct Scheduler : public virtual Fiber {
  /// <summary>
  /// 参数个数
  /// </summary>
  int _argc;
  /// <summary>
  /// 参数数组
  /// </summary>
  char** _argv;
  /// <summary>
  /// 环境变量数组
  /// </summary>
  char** _env;
  /// <summary>
  /// Fiber列表
  /// </summary>
  std::list<Fiber*> _fiberList;

  /// <summary>
  /// 构造
  /// </summary>
  /// <param name="argc">参数个数</param>
  /// <param name="argv">参数数组</param>
  /// <param name="env">环境变量数组</param>
  Scheduler(int argc, char** argv, char** env);

  /// <summary>
  /// 析构
  /// </summary>
  virtual ~Scheduler();

  /// <summary>
  /// 运行
  /// </summary>
  void run();

  /// <summary>
  /// 调度
  /// </summary>
  void schedule();
};
