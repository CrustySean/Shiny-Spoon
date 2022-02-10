#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <memory>
#include <string>
#include <stdexcept>

/* Prepare variables. */
std::string itemstr;
uint32_t giftkind;
uint32_t kind;
uint32_t id;
uint32_t fieldc;

namespace Blitz {

    constexpr uint32_t BZGN_MAGIC = 1313299010;

    struct GiftGear {
        uint32_t m_GiftKind;
        uint32_t m_Kind;
        uint32_t m_Id;
        uint32_t field_C;
    };

    struct Header {
        uint32_t m_Magic;
        uint8_t padding1[0xC];
        uint32_t m_Count;
        uint8_t padding2[0xC];
    };

    std::string parseGearKind(int value) {
        switch (value) {
            case 0:
                return "cShoes";
            case 1:
                return "cClothes";
            case 2:
                return "cHead";
            case 3:
                return "cNone";
        }

        return "cNone";
    }

    /* https://stackoverflow.com/a/26221725 */
    template<typename ... Args>
    std::string formatString(const std::string& format, Args ... args)
    {
        int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
        if (size_s <= 0) { 
            throw std::runtime_error("Error during formatting."); 
        }
        
        auto size = static_cast<size_t>(size_s);
        auto buf = std::make_unique<char[]>(size);
        std::snprintf(buf.get(), size, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
    }

    enum LogType {
        LogType_Info,
        LogType_Warning,
        LogType_Error  
    };

    std::string logFormat(const std::string& string, LogType type) {
        switch (type) {
            case LogType_Info:
                return formatString("\033[1;32m%s\033[0m\n", string.c_str());
            case LogType_Warning:
                return formatString("\033[1;33m%s\033[0m\n", string.c_str());
            case LogType_Error:
                return formatString("\033[1;31m%s\033[0m\n", string.c_str());;
        }

        return string;
    }
};