#include <WinSock2.h>

#include "Scheduler.hpp"

#pragma comment(lib, "ws2_32")

/// <summary>
/// 入口方法
/// </summary>
/// <param name="argc">参数个数</param>
/// <param name="argv">参数字符串数组</param>
/// <param name="env">环境变量字符串数组</param>
/// <returns></returns>
int main(int argc, char** argv, char** env) {
  auto startupFiber = ConvertThreadToFiber(NULL);
  if (nullptr == startupFiber) return -1;

  WSADATA wsaData{};
  if (WSAStartup(MAKEWORD(2, 2), &wsaData)) return -2;

  Fiber* ctx = new Scheduler(argc, argv, env);
  auto mainFiber = CreateFiber(0, &Fiber::entry, ctx);
  if (nullptr != mainFiber) {
    SwitchToFiber(mainFiber);
    DeleteFiber(mainFiber);
  }
  DeleteFiber(startupFiber);
  return 0;
}