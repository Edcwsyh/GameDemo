/*
    > File Name: EdcBaseException.hpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2021年11月28日 星期日 18时28分15秒
*/

#ifndef __EXCEPTION_EDC__
#define __EXCEPTION_EDC__

#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <sstream>
#include <string>
#include <string_view>
#include <cstring>
#include <functional>
#include <iostream>
#include <utility>

namespace Edc{

class BaseException : public std::exception{
//Constant
public:
    static constexpr size_t BUF_SIZE = 512;
//Member Variables
protected:
    std::string m_file; //发生错误的文件
    uint32_t    m_line; //发生错误的代码行数
    std::string m_func; //发生错误的函数
    std::string m_error; //错误消息
    int m_illErrorCode; //错误码
    
//Static Member Variables
private:
    
//Member Function
public:
    BaseException() = delete;
    BaseException( std::string_view error, std::string_view file, 
                   uint32_t line, std::string_view func ) : 
                   m_file( file ), m_line(line), m_func(func), m_error( error ) {  };
    virtual ~BaseException() = default;

    const std::string& get_file() const noexcept { return m_file; } 
    uint32_t get_line() const noexcept { return m_line; }
    const std::string& get_func() const noexcept { return m_func; }
    const std::string& get_error() const noexcept { return m_error; }
    
    //执行异常处理
    virtual void exec() {  };
    virtual const char* what() const noexcept { return m_error.c_str(); };
    int get_error_code() const noexcept { return m_illErrorCode; };
//Static Member Function
public:
    static std::string build_error( const char* fmt, ... ); 
};

inline std::string BaseException::build_error( const char* fmt, ... ) {
    char buffer[BUF_SIZE];
    va_list vaList;
    va_start( vaList, fmt );
    vsnprintf( buffer, BUF_SIZE, fmt, vaList );
    va_end( vaList );
    return buffer;
}

/**
 * @description 终止异常，抛出此异常时终止进程
 */
class TerminationException : public BaseException {
private:
public:
    TerminationException() = delete;
    virtual ~TerminationException() = default;
    explicit TerminationException( std::string_view error, std::string_view file, 
        uint32_t line, std::string_view func ) : 
        BaseException( error, file, line, func ) {  }

    virtual void exec() override { 
        std::string output = m_file + ":" + std::to_string( m_line ) + ":" + m_func + ":" + m_error;
        std::cerr << output << std::endl;
        exit(EXIT_FAILURE);
    };

};

#define EdcException( _exception, _error, args... ) \
    Edc::_exception( Edc::BaseException::build_error( _error, ##args ), __FILE__, __LINE__, __func__ ) 

#define EdcTerminationException( _error, args... ) EdcException( TerminationException, _error, ##args )

}
#endif
