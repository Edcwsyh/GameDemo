/*
    > File Name: Logger.cpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: Sun 28 Mar 2021 09:44:00 PM CST
*/

#include "Logger.hpp"
#include "EdcBaseException.hpp"
#include "TimeTools.hpp"
#include "EdcEnv.h"
#include <algorithm>
#include <cstdio>
#include <cwchar>
#include <iostream>
#include <cstring>
#include <mutex>
#include <new>
#include <stdexcept>
#include <cstdarg>
#include <string>
#include <string_view>

namespace Edc{

Logger::Logger(): m_writerLock( nullptr ) {  }

Logger::Logger( std::string_view logPath, bool multithreading ):
    m_logPath( logPath ), m_writerLock( nullptr )
{
    m_writer.open( m_logPath, std::ios::app );
    if ( !m_writer ) {
        throw EdcTerminationException( "File opening failure, file : %s ", m_logPath.c_str() );
    }
    //若指定线程安全，则初始化锁
    if ( multithreading ) {
        m_writerLock = new std::mutex;
    }
}

Logger::~Logger(){
    m_writer.close();
    if ( m_writerLock ) {
        delete m_writerLock;
    }
}

void Logger::write( std::string_view info ) {
    //判断是否应该加锁
    std::string output( fmt_current_time() );
    output += info;
    if ( m_writerLock ) {
        std::lock_guard<std::mutex> writerLock( *m_writerLock );
        m_writer << output << std::endl;
    } else {
        m_writer << output << std::endl;
    }
}

void Logger::write_fmt( const char* fmt, ... ) noexcept {
    char buffer[EdcEnv::BUFSIZE_TINY];
    va_list param;
    //格式化字符串
    va_start( param, fmt );
    vsnprintf( buffer, sizeof(char) * EdcEnv::BUFSIZE_TINY, fmt, param );
    va_end( param );
    //调用接口进行输出
    write( buffer );
}

void Logger::set_writer_lock( bool enable ) {
    if ( enable ) {
        if ( !m_writerLock ) {
            m_writerLock = new std::mutex;
        }
    } else if ( m_writerLock ) {
        delete m_writerLock;
        m_writerLock = nullptr;
    }
}

std::string Logger::fmt_current_time() noexcept {
   return TimeTools::strfmttime_safe( ::time(0), TIME_FMT );
}


}
