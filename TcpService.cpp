#include "TcpService.h"

#include <iostream>

/// <summary>
/// ����
/// </summary>
TcpService::TcpService(int port, Scheduler* scheduler, bool canSchedule)
    : Fiber(scheduler, canSchedule), _port(port), _socket(), _iocp() {
  // TODO �������
  do {
    _socket = socket(AF_INET, SOCK_STREAM, IPPROTO_IP);
    if (INVALID_SOCKET == _socket) break;

    u_long v = 1;
    ioctlsocket(_socket, FIONBIO, &v);
    SOCKADDR_IN si{};
    si.sin_family = AF_INET;
    si.sin_port = ::ntohs(_port);
    si.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(_socket, reinterpret_cast<sockaddr*>(&si), sizeof(si))) break;

    if (listen(_socket, 128)) break;

    _iocp = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, 0, 0);
  } while (false);
}

/// <summary>
/// ����
/// </summary>
TcpService ::~TcpService() {}

/// <summary>
/// ����
/// </summary>
void TcpService::run() {
  SOCKADDR_IN in{};
  int addrLen = sizeof(in);
  while (true) {
    SOCKET s = accept(_socket, reinterpret_cast<sockaddr*>(&in), &addrLen);
    if (INVALID_SOCKET == s) {
      if (WSAEWOULDBLOCK == ::WSAGetLastError()) yield();
      continue;
    }
    // TODO ��������
  }
}