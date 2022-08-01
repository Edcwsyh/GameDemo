/*
    > File Name: LogMgr.hpp 日志管理类
    > 可选编译 : 定义宏 __EDC_LOG_SECURITY__ 开启安全日志
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2021年12月26日 星期日 11时39分49秒
*/

#ifndef __LOGMGR_EDC__
#define __LOGMGR_EDC__

#include "EdcBaseException.hpp"
#include "BaseLogger.hpp"
#include "Singleton.hpp"
#include <array>
#include <memory>
#include <string_view>
#include <unordered_set>

namespace Edc {

class LogMgr : public Edc::Singleton<LogMgr> {
//Type
public:
    //日志等级
    enum LogLevel {
        ENM_LOG_LVEL_FATAL = 0, //严重信息
        ENM_LOG_LEVEL_ERROR,    //错误信息
        ENM_LOG_LEVEL_WARNING,  //警告信息
        ENM_LOG_LEVEL_DEBUG,    //调试信息
        ENM_LOG_LEVEL_INFO,     //常规信息
        __ENM_LOG_LEVEL_NUM, 
        ENM_LOG_LEVEL_UNKNOW,   // 未知的日志
    };

    constexpr static std::array<const char*, __ENM_LOG_LEVEL_NUM> m_oLogLevelMap = {
        "[FATAL]   : ", 
        "[ERROR]   : ", 
        "[WARNING] : ", 
        "[DEBUG]   : ", 
        "[INFO]    : ", 
    };
    
//Constant
public:
protected:
    
//Member Variables
protected:
    //日志对象集合
    std::array<std::shared_ptr<BaseLogger>, __ENM_LOG_LEVEL_NUM> m_oLoggerList;
    // 开启的日志等级
    LogLevel m_enmLogLevel;
    // 开启的堆栈信息等级
    LogLevel m_enmBacktraceLevel;
    //地址验证器，辅助验证某个日志对象是否重复注册
    //定义日志安全宏时生效
//#ifdef __EDC_LOG_SECURITY__
//    std::unordered_set<Logger*> m_oValidator;
//#endif
    
//Static Member Variables
protected:
    
//Member Function
public:
    LogMgr() : m_enmLogLevel( ENM_LOG_LEVEL_INFO ), m_enmBacktraceLevel( ENM_LOG_LEVEL_ERROR ) {  }
    virtual ~LogMgr() = default;
    /**
     * @description register_level 注册一个日志等级
     *
     * @param logLevel 日志等级，应取Logger::LogLevel的值
     * @param pLogger 日志对象
     */
    void register_level( LogLevel logLevel, std::shared_ptr<BaseLogger> pLogger);

    void write( LogLevel logLevel, const char* fmt, ... ) noexcept;
    void set_log_level( LogLevel uLogLevel ) noexcept { m_enmLogLevel = uLogLevel; };
    LogLevel get_log_level() const noexcept{ return m_enmLogLevel; };
    void set_backtrace_level( LogLevel enmLogLevel ) noexcept { m_enmBacktraceLevel = enmLogLevel; }
    LogLevel get_backtrace_level() const noexcept{ return m_enmBacktraceLevel; };
//Static Member Function
public:
    static LogLevel get_log_level( const char* level ) noexcept;
    
};

inline void LogMgr::register_level( LogLevel logLevel, std::shared_ptr<BaseLogger> pLogger) {
    if ( !pLogger ) {
        throw EdcTerminationException( "The registered log object cannot be empty! log level : %u", logLevel );
    }
    m_oLoggerList[logLevel] = std::move( pLogger );
}

}

#define __BASE_LOG( _level, _fmt, _args... ) {                      \
    if ( Edc::LogMgr::instance().get_log_level() >= _level ) {      \
        Edc::LogMgr::instance().write( _level, _fmt,  ##_args  );   \
    }                                                               \
}

#define LOG_FATAL( _fmt, _args... ) __LOG_FATAL( _fmt, __FILE__, __func__, __LINE__, ##_args )
#define LOG_ERR( _fmt, _args... ) __LOG_ERR( _fmt, __FILE__, __func__, __LINE__, ##_args )
#define LOG_WAR( _fmt, _args... ) __LOG_WAR( _fmt, __FILE__, __func__, __LINE__, ##_args )
#define LOG_DBG( _fmt, _args... ) __LOG_DBG( _fmt, __FILE__, __func__, __LINE__, ##_args )
#define LOG_INFO( _fmt, _args... ) __LOG_INFO( _fmt, __FILE__, __func__, __LINE__, ##_args )

#define __LOG_FATAL( _fmt, _file, _func, _line, _args... ) __BASE_LOG( Edc::LogMgr::ENM_LOG_LVEL_FATAL, "%s:%u::%s : " _fmt, _file, _line, _func, ##_args )
#define __LOG_ERR( _fmt, _file, _func, _line, _args... ) __BASE_LOG( Edc::LogMgr::ENM_LOG_LEVEL_ERROR, "%s:%u::%s : " _fmt, _file, _line, _func, ##_args )
#define __LOG_WAR( _fmt, _file, _func, _line, _args... ) __BASE_LOG( Edc::LogMgr::ENM_LOG_LEVEL_WARNING, "%s:%u::%s : " _fmt, _file, _line, _func, ##_args )
#define __LOG_DBG( _fmt, _file, _func, _line, _args... ) __BASE_LOG( Edc::LogMgr::ENM_LOG_LEVEL_DEBUG, "%s:%u::%s : " _fmt, _file, _line, _func, ##_args )
#define __LOG_INFO( _fmt, _file, _func, _line, _args... ) __BASE_LOG( Edc::LogMgr::ENM_LOG_LEVEL_INFO, "%s:%u::%s : " _fmt, _file, _line, _func, ##_args )

// 以下接口不带文件名等信息
#define BASE_LOG_FATAL( _fmt, _args... ) __BASE_LOG( Edc::LogMgr::ENM_LOG_LEVEL_FATAL,  _fmt, ##_args )
#define BASE_LOG_ERR( _fmt, _args... ) __BASE_LOG( Edc::LogMgr::ENM_LOG_LEVEL_ERROR,  _fmt, ##_args )
#define BASE_LOG_WAR( _fmt, _args... ) __BASE_LOG( Edc::LogMgr::ENM_LOG_LEVEL_WARNING,  _fmt, ##_args )
#define BASE_LOG_DBG( _fmt, _args... ) __BASE_LOG( Edc::LogMgr::ENM_LOG_LEVEL_DEBUG,  _fmt, ##_args )
#define BASE_LOG_INFO( _fmt, _args... ) __BASE_LOG( Edc::LogMgr::ENM_LOG_LEVEL_INFO,  _fmt, ##_args )

#endif
