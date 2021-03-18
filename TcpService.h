#pragma once

#include <winsock2.h>

#include "Fiber.hpp"

/// <summary>
/// TCP服务
/// </summary>
struct TcpService : public virtual Fiber {
  /// <summary>
  /// 端口
  /// </summary>
  int _port;

  /// <summary>
  /// 套接字
  /// </summary>
  SOCKET _socket;

  /// <summary>
  /// 完成端口
  /// </summary>
  HANDLE _iocp;

  /// <summary>
  /// 构造
  /// </summary>
  /// <param name="port">端口</param>
  /// <param name="scheduler">调度器</param>
  /// <param name="canSchedule">是否可调度</param>
  TcpService(int port, Scheduler* scheduler = nullptr,
             bool canSchedule = false);

  /// <summary>
  /// 析构
  /// </summary>
  virtual ~TcpService();

  /// <summary>
  /// 运行
  /// </summary>
  virtual void run();
};
