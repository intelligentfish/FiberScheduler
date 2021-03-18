#pragma once

#include <Windows.h>

#include <atomic>

/// <summary>
/// Fiber
/// </summary>
struct Scheduler;
/// <summary>
/// Э��
/// </summary>
struct Fiber {
  /// <summary>
  /// ���
  /// </summary>
  LPVOID _handle;
  /// <summary>
  /// ������
  /// </summary>
  Scheduler* _scheduler;
  /// <summary>
  /// �ɵ���
  /// </summary>
  bool _canSchedule;
  /// <summary>
  /// �����
  /// </summary>
  bool _finished;
  /// <summary>
  /// Fiber ID
  /// </summary>
  int _id;

  /// <summary>
  /// ���
  /// </summary>
  /// <param name="param">����</param>
  /// <returns></returns>
  static void WINAPI entry(LPVOID param);

  /// <summary>
  /// ����
  /// </summary>
  /// <param name="scheduler">������</param>
  /// <param name="canSchedule">�Ƿ�ɵ���</param>
  Fiber(Scheduler* scheduler = nullptr, bool canSchedule = false);

  /// <summary>
  /// ����
  /// </summary>
  virtual ~Fiber();

  /// <summary>
  /// ���þ��
  /// </summary>
  /// <param name="handle">���</param>
  /// <returns>Fiber����</returns>
  Fiber& setHandle(LPVOID handle);

  /// <summary>
  /// ��ȡ���
  /// </summary>
  /// <returns>���</returns>
  LPVOID getHandle() const;

  /// <summary>
  /// ��ȡ��ʶ
  /// </summary>
  /// <returns></returns>
  int getId() const;

  /// <summary>
  /// �ó�ִ��Ȩ
  /// </summary>
  void yield();

  /// <summary>
  /// �ָ�
  /// </summary>
  void resume();

  /// <summary>
  /// ����
  /// </summary>
  virtual void run() = 0;
};