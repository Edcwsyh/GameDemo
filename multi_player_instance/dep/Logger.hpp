/*
    > File Name: Logger.hpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: Sun 28 Mar 2021 05:16:51 PM CST
*/

#ifndef __LOGGER_EDC__
#define __LOGGER_EDC__

#include <array>
#include <fstream>
#include <string>
#include <string_view>
#include <ctime>
#include <mutex>
#include <initializer_list>
#include "BaseLogger.hpp"

namespace Edc{

class Logger : public BaseLogger {
//Type
public:

//Static Member Variables
public :
    // 时间格式
    static constexpr const char* TIME_FMT = "[%Y-%m-%d %H:%M:%S] | ";

//Member Variables
private:
    std::ofstream m_writer; //输出文件
    std::string m_logPath;   //文件路径
    //std::array<char, SIZE_BUF> m_buf;  //缓冲区

    std::mutex *m_writerLock; //文件锁

//Member Function
public:
    /**
     * @description Logger 构造一个日志对象
     *
     * @param logPath 文件路径
     * @param multithreading 是否使用线程安全
     */
    Logger();
    Logger( std::string_view logPath, bool multithreading = false );
    explicit Logger ( const Logger& ) = delete;
    explicit Logger ( Logger&& ) = delete;
    Logger& operator=( const Logger& ) = delete;

    ~Logger();
    /**
     * @descript 清空日志文件
     */
    void clear() noexcept;
    /**
     * @descript 按格式写入日志文件
     */
    void write_fmt( const char* fmt, ... ) noexcept ;
    /**
     * @descripe 格式化当前时间, 并把结果保存为字符串s_buf
     */
    std::string fmt_current_time() noexcept;
    
    /**
     * @description 启用或禁用文件锁
     * @param enable : true表示启用，false表示禁用
     */
    void set_writer_lock( bool enable = true );


    //获取日志文件路径
    const std::string& get_file_path() const noexcept { return m_logPath; }
    /**
     * @descript 向文件写入日志信息
     */
    virtual void write( std::string_view info ) override;
     //@descripe 格式化当前时间, 并把结果保存为字符串s_buf
    //const char* _fmt_current_time() noexcept;
//Static Member Function
public:
};

inline void Logger::clear() noexcept {
    m_writer.close();
    m_writer.open( m_logPath, std::ios::out | std::ios::trunc );
}

}
#endif
