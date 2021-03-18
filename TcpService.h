#pragma once

#include <winsock2.h>

#include "Fiber.hpp"

/// <summary>
/// TCP����
/// </summary>
struct TcpService : public virtual Fiber {
  /// <summary>
  /// �˿�
  /// </summary>
  int _port;

  /// <summary>
  /// �׽���
  /// </summary>
  SOCKET _socket;

  /// <summary>
  /// ��ɶ˿�
  /// </summary>
  HANDLE _iocp;

  /// <summary>
  /// ����
  /// </summary>
  /// <param name="port">�˿�</param>
  /// <param name="scheduler">������</param>
  /// <param name="canSchedule">�Ƿ�ɵ���</param>
  TcpService(int port, Scheduler* scheduler = nullptr,
             bool canSchedule = false);

  /// <summary>
  /// ����
  /// </summary>
  virtual ~TcpService();

  /// <summary>
  /// ����
  /// </summary>
  virtual void run();
};
