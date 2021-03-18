#pragma once

#include <Windows.h>

#include <atomic>

/// <summary>
/// Fiber
/// </summary>
struct Scheduler;
/// <summary>
/// 协程
/// </summary>
struct Fiber {
  /// <summary>
  /// 句柄
  /// </summary>
  LPVOID _handle;
  /// <summary>
  /// 调度器
  /// </summary>
  Scheduler* _scheduler;
  /// <summary>
  /// 可调度
  /// </summary>
  bool _canSchedule;
  /// <summary>
  /// 已完成
  /// </summary>
  bool _finished;
  /// <summary>
  /// Fiber ID
  /// </summary>
  int _id;

  /// <summary>
  /// 入口
  /// </summary>
  /// <param name="param">参数</param>
  /// <returns></returns>
  static void WINAPI entry(LPVOID param);

  /// <summary>
  /// 构造
  /// </summary>
  /// <param name="scheduler">调度器</param>
  /// <param name="canSchedule">是否可调度</param>
  Fiber(Scheduler* scheduler = nullptr, bool canSchedule = false);

  /// <summary>
  /// 析构
  /// </summary>
  virtual ~Fiber();

  /// <summary>
  /// 设置句柄
  /// </summary>
  /// <param name="handle">句柄</param>
  /// <returns>Fiber引用</returns>
  Fiber& setHandle(LPVOID handle);

  /// <summary>
  /// 获取句柄
  /// </summary>
  /// <returns>句柄</returns>
  LPVOID getHandle() const;

  /// <summary>
  /// 获取标识
  /// </summary>
  /// <returns></returns>
  int getId() const;

  /// <summary>
  /// 让出执行权
  /// </summary>
  void yield();

  /// <summary>
  /// 恢复
  /// </summary>
  void resume();

  /// <summary>
  /// 运行
  /// </summary>
  virtual void run() = 0;
};