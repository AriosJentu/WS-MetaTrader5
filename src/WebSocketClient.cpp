#include "WebSocketClient.h"
#include "UTF8Converter.h"
#include <websocketpp/config/asio_no_tls_client.hpp>
#include <websocketpp/client.hpp>
#include <queue>
#include <mutex>
#include <string>
#include <windows.h>

using websocketpp::connection_hdl;
typedef websocketpp::client<websocketpp::config::asio_client> client;

// Thread-safe queue for messages
std::queue<std::string> message_queue;
std::mutex queue_mutex;

// Message handler for WebSocket
void on_message(client* c, connection_hdl hdl, websocketpp::config::asio_client::message_type::ptr msg) {
    std::lock_guard<std::mutex> lock(queue_mutex);
    message_queue.push(msg->get_payload());
}

// Connect to WebSocket server
extern "C" __declspec(dllexport) void __stdcall ConnectWebSocket(const wchar_t* server_uri) {
    try {
        std::wstring ws_uri(server_uri);
        std::string uri = UTF8Converter::UTF16ToUTF8(ws_uri);

        client ws_client;
        ws_client.init_asio();

        ws_client.set_message_handler(std::bind(&on_message, &ws_client, std::placeholders::_1, std::placeholders::_2));

        websocketpp::lib::error_code ec;
        client::connection_ptr con = ws_client.get_connection(uri, ec);
        if (ec) {
            return; // Handle connection error
        }

        ws_client.connect(con);
        ws_client.run();
    } catch (const std::exception& e) {
        return; // Add logging here if necessary
    }
}

// Get message from queue
extern "C" __declspec(dllexport) void __stdcall GetMessageFromQueue(wchar_t* buffer, int buffer_size) {
    std::lock_guard<std::mutex> lock(queue_mutex);

    if (!message_queue.empty()) {
        std::string utf8_message = message_queue.front();
        message_queue.pop();

        // Convert UTF-8 to UTF-16
        std::wstring utf16_message = UTF8Converter::UTF8ToUTF16(utf8_message);

        if (utf16_message.size() >= static_cast<size_t>(buffer_size)) {
            return; // Insufficient buffer size
        }

        wcscpy_s(buffer, buffer_size, utf16_message.c_str());
    }
}

// Add a greeting message
extern "C" __declspec(dllexport) void __stdcall GetGreeting(wchar_t* buffer, int buffer_size) {
    std::wstring greeting = L"Hello from DLL";

    if (greeting.size() >= static_cast<size_t>(buffer_size)) {
        return; // Insufficient buffer size
    }

    wcscpy_s(buffer, buffer_size, greeting.c_str());
}