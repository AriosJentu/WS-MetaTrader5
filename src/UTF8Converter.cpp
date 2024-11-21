#include "UTF8Converter.h"
#include <windows.h> // For MultiByteToWideChar & WideCharToMultiByte
#include <stdexcept>

std::wstring UTF8Converter::UTF8ToUTF16(const std::string& utf8) {
    // Find size of the UTF-16 string
    int utf16_length = MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, nullptr, 0);
    if (utf16_length == 0) {
        throw std::runtime_error("Ошибка конвертации UTF-8 в UTF-16");
    }

    // Convert string to UTF-16
    std::wstring utf16(utf16_length, 0);
    MultiByteToWideChar(CP_UTF8, 0, utf8.c_str(), -1, &utf16[0], utf16_length);

    return utf16;
}

std::string UTF8Converter::UTF16ToUTF8(const std::wstring& utf16) {
    // Find size of the UTF-8 string
    int utf8_length = WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (utf8_length == 0) {
        throw std::runtime_error("Ошибка конвертации UTF-16 в UTF-8");
    }

    // Convert string to UTF-8
    std::string utf8(utf8_length, 0);
    WideCharToMultiByte(CP_UTF8, 0, utf16.c_str(), -1, &utf8[0], utf8_length, nullptr, nullptr);

    return utf8;
}