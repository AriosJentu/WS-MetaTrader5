
# WebSocketClient DLL for MetaTrader 5

## Description
`WebSocketClient` is a DLL library that enables you to connect to a WebSocket server from **MetaTrader 5** and process incoming messages. It provides seamless integration with MetaTrader by handling string conversions between UTF-8 (used in the DLL) and UTF-16 (used in MetaTrader).

---

## Features
- **WebSocket Connection**: Establishes a connection to a WebSocket server using a URI.
- **Message Queue**: Stores incoming WebSocket messages in a thread-safe queue.
- **UTF-16 Support**: Converts all strings to UTF-16 for proper compatibility with MetaTrader.
- **Simple Integration**: Exported functions are easy to use directly in MetaTrader scripts.

---

## Requirements
1. **MetaTrader 5**: A version that supports external DLLs.
2. **Windows (DLL)**: MetaTrader 5 supports Windows DLLs natively.
3. **Dependencies**:
   - **Boost.Asio**: Used for asynchronous network operations.
   - **WebSocket++**: Provides WebSocket client functionality.

---

## Installation

### 1. Build the DLL
Follow these steps to compile the DLL:

#### Install Dependencies
Install Boost and WebSocket++ manually or via a package manager like `vcpkg`.

#### Build Using CMake
Run the following commands from the project root:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

#### Output File
The compiled library will be in the `build/` folder: `WebSocketClient.dll`

---

### 2. Add the DLL to MetaTrader
1. Copy the compiled DLL (`WebSocketClient.dll`) into the `Libraries` folder of your MetaTrader 5 installation directory:
   ```text
   C:\Program Files\MetaTrader 5\MQL5\Libraries
   ```

2. Restart MetaTrader if it is already running.

---

## Usage in MetaTrader

Here is an example script in MQL5 to use the WebSocketClient DLL:

```mql5
#import "WebSocketClient.dll"
void ConnectWebSocket(string server_uri);
void GetMessageFromQueue(ushort &buffer[], int buffer_size);
#import

void OnStart() {
    // Connect to WebSocket server
    string server = "wss://echo.websocket.events";
    ConnectWebSocket(server);

    // Process incoming messages
    ushort buffer[1024];
    while (true) {
        ArrayInitialize(buffer, 0); // Clear buffer
        GetMessageFromQueue(buffer, ArraySize(buffer));
        string message = CharArrayToString(buffer);

        if (message != "") {
            Print("Received message: ", message);
        }

        Sleep(1000); // Pause before checking for new messages
    }
}
```

---

## Exported Functions

### 1. `ConnectWebSocket`
Establishes a connection to a WebSocket server.

#### Parameters:
- `server_uri` (`string`): The WebSocket server URI (e.g., `wss://example.com`).

### 2. `GetMessageFromQueue`
Retrieves the next message from the WebSocket message queue.

#### Parameters:
- `buffer[]` (`ushort`): A buffer to store the message in UTF-16 format.
- `buffer_size` (`int`): The size of the buffer.

#### Notes:
- If the queue is empty, no message will be returned.
- Ensure the buffer size is large enough to store incoming messages.

---

## Known Limitations
1. The buffer size for `GetMessageFromQueue` must be sufficient to hold the largest incoming message. If the buffer is too small, the message will be skipped or truncated.
2. On macOS, the library can only be used with MetaTrader 5 running via Wine.
3. The library does not currently support outgoing WebSocket messages (only receiving is implemented).
