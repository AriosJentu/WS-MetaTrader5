#ifndef UTF8CONVERTER_H
#define UTF8CONVERTER_H

#include <string>

class UTF8Converter {
public:
    // Convert UTF-8 -> UTF-16
    static std::wstring UTF8ToUTF16(const std::string& utf8);

    // Convert UTF-16 -> UTF-8
    static std::string UTF16ToUTF8(const std::wstring& utf16);
};

#endif // UTF8CONVERTER_H