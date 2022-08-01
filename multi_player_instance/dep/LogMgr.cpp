/*
    > File Name: LogMgr.cpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2021年12月26日 星期日 11时52分14秒
*/

#include "LogMgr.hpp"
#include "StringTools.hpp"
#include "Backtrace.hpp"
#include "EdcEnv.h"
#include <iostream>
#include <string_view>
#include <cstdarg>
#include <utility>

namespace Edc {

void LogMgr::write( LogLevel logLevel, const char* fmt, ... ) noexcept {
//若定义日志安全宏，则进行判断
#ifdef __EDC_LOG_SECURITY__
    if ( logLevel >= __ENM_LOG_LEVEL_NUM ) {
        std::cerr << "Log level error, level : " << logLevel << std::endl;
        return;
    }
#endif

    auto& pLogger = m_oLoggerList[logLevel];
    char buffer[EdcEnv::BUFSIZE_BIG];
    va_list param;
    //格式化字符串
    va_start( param, fmt );
    vsnprintf( buffer, sizeof(char) * EdcEnv::BUFSIZE_BIG, fmt, param );
    va_end( param );
    std::string sLogInfo = m_oLogLevelMap[logLevel];
    sLogInfo += buffer;

    if ( logLevel <= m_enmBacktraceLevel ) {
        sLogInfo += Backtrace("", 2).debug_info();
    } 
    // 未注册日志等级时输出到标准错误
    if ( pLogger.get() ) {
        pLogger->write( sLogInfo );
    } else {
        std::cerr << sLogInfo << std::endl;
    }
}

LogMgr::LogLevel LogMgr::get_log_level( const char* level) noexcept {
    uint32_t logLevel = ENM_LOG_LEVEL_UNKNOW;
    std::string tmp;
    for ( ;logLevel < __ENM_LOG_LEVEL_NUM; ++logLevel ) {
        tmp = m_oLogLevelMap[logLevel];
        tmp = Edc::Singleton<StringTools>::instance().midstr( tmp, "\\[", "]" );
        if ( tmp == level ) {
            break;
        }
    }
    return static_cast<LogLevel>( logLevel );
}


}
