#pragma once

#include <list>
#include <memory>

#include "ServiceFiber.hpp"

/// <summary>
/// Fiber������
/// </summary>
struct Scheduler : public virtual Fiber {
  /// <summary>
  /// ��������
  /// </summary>
  int _argc;
  /// <summary>
  /// ��������
  /// </summary>
  char** _argv;
  /// <summary>
  /// ������������
  /// </summary>
  char** _env;
  /// <summary>
  /// Fiber�б�
  /// </summary>
  std::list<Fiber*> _fiberList;

  /// <summary>
  /// ����
  /// </summary>
  /// <param name="argc">��������</param>
  /// <param name="argv">��������</param>
  /// <param name="env">������������</param>
  Scheduler(int argc, char** argv, char** env);

  /// <summary>
  /// ����
  /// </summary>
  virtual ~Scheduler();

  /// <summary>
  /// ����
  /// </summary>
  void run();

  /// <summary>
  /// ����
  /// </summary>
  void schedule();
};
