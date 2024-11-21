#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

#include <string>

// Export functions for MetaTrader
extern "C" {
    // Connect to WebSocket server
    __declspec(dllexport) void __stdcall ConnectWebSocket(const wchar_t* server_uri);

    // Get message from queue
    __declspec(dllexport) void __stdcall GetMessageFromQueue(wchar_t* buffer, int buffer_size);
}

#endif // WEBSOCKETCLIENT_H