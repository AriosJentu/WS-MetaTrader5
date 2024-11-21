#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <string>

// Exported functions for MetaTrader
extern "C" {
    __declspec(dllexport) void __stdcall ConnectWebSocket(const wchar_t* server_uri);
    __declspec(dllexport) void __stdcall GetMessageFromQueue(wchar_t* buffer, int buffer_size);
    __declspec(dllexport) void __stdcall GetGreeting(wchar_t* buffer, int buffer_size);
}

#endif // WEBSOCKETCLIENT_H