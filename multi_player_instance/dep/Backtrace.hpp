/*
    > File Name: Backtrace.hpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2022年07月04日 星期一 14时20分37秒
*/

#ifndef __BACKTRACE_EDC__
#define __BACKTRACE_EDC__

#include <ostream>
#include <string>
#include <string_view>

namespace std {
}

namespace Edc {

class Backtrace {
//Type
public:
    
//Constant
public:
protected:
    constexpr static size_t BUFF_SIZE = 256;
    
//Member Variables
protected:
    std::string m_oBacktraceInfo;
    
//Static Member Variables
protected:
    
//Member Function
public:
    /**
     * @description Backtrace 
     *
     * @param uSkipLevel Skip back trace num, default 1, no Backtrace object info
     */
    Backtrace( std::string_view sPrefix = "", uint32_t uSkipLevel = 1 );
    explicit Backtrace( const Backtrace& ) = default;
    explicit Backtrace( Backtrace&& ) = default;
    ~Backtrace() = default;
    Backtrace& operator=( const Backtrace& ) = delete;
    Backtrace& operator=( Backtrace&& ) = delete;

    const std::string& debug_info() const noexcept { return m_oBacktraceInfo; }
//Static Member Function
public:
    friend std::ostream& operator<<( std::ostream& out, Backtrace& oBacktrace  );
    friend std::ostream& operator<<( std::ostream& out, Backtrace&& oBacktrace  );
    
};


}

#endif
