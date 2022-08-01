/*
    > File Name: Backtrace.cpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2022年07月04日 星期一 14时21分16秒
*/

#include <cstddef>
#include <execinfo.h>
#include <cxxabi.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <sstream>
#include <string_view>
#include <vector>
#include "Backtrace.hpp"

namespace Edc {

// copy from https://stackoverflow.com/questions/27440953/stdunique-ptr-for-c-functions-that-need-free
struct free_deleter{
    template <typename T>
    void operator()(T *p) const {
        std::free(const_cast<std::remove_const_t<T>*>(p));
    }
};

Backtrace::Backtrace( std::string_view sPrefix, uint32_t uSkipLevel ) : m_oBacktraceInfo( sPrefix ) {
    int nptrs = 0; //符号数量
    void *buffer[BUFF_SIZE] = { nullptr };

    // 获取符号地址 
    nptrs = backtrace( buffer, BUFF_SIZE );
    if ( !nptrs ) {
        m_oBacktraceInfo = "Backtrace::backtrace return 0!";
        return;
    }
    // RAII 避免内存泄漏
    std::unique_ptr<char*, free_deleter> strings( backtrace_symbols( buffer, nptrs ) );

    if ( !strings ) {
        m_oBacktraceInfo = "Backtrace::backtrace_symbols return nullptr!";
        return;
    }
    
    size_t uFuncNameSize = BUFF_SIZE;
    std::vector<char> oFuncName( uFuncNameSize );
    if ( oFuncName.size() != uFuncNameSize ) {
        m_oBacktraceInfo = "Backtrace::Create sFuncName fail!";
        return;
    }
    m_oBacktraceInfo += "\nbacktrace info : \n";

    std::stringstream ss;
    // jump local function
    for ( uint32_t uIdx = uSkipLevel; uIdx < nptrs; ++uIdx ) {
        // modify from : https://panthema.net/2008/0901-stacktrace-demangled
        char *begin_name = nullptr,  *begin_offset = nullptr,  *end_offset = nullptr, *address_offset = nullptr;

        for( char *p = strings.get()[uIdx]; *p; ++p ) {
            if( *p == '(' ) {
                begin_name = p;
            } else if ( *p == '+' ) {
                begin_offset = p;
            } else if ( *p == ')' && begin_offset ) {
                end_offset = p;
            } else if ( *p == '[' ) {
                address_offset = p;
            }
        }

        if ( address_offset ) {
            ss << "    " << address_offset << " : "; 
        }

        if (begin_name && begin_offset && end_offset && begin_name < begin_offset) {
            *begin_name++ = '\0';
            *begin_offset++ = '\0';
            *end_offset = '\0';

            ss << strings.get()[uIdx] << " : ";

            int status;
            char* ret = abi::__cxa_demangle( begin_name, oFuncName.data(), &uFuncNameSize, &status );
            if ( !status ) {
                ss << ret << " + " << begin_offset;
            } else {
                ss << begin_name << "() + " << begin_offset;
            }
        } else {
            ss << '\t' << strings.get()[uIdx];
        }
        ss << '\n';
    }
    m_oBacktraceInfo += ss.str();
}

std::ostream& operator<<( std::ostream& out, Backtrace& oBacktrace ) {
    return out << oBacktrace.m_oBacktraceInfo;
}

std::ostream& operator<<( std::ostream& out, Backtrace&& oBacktrace ) {
    return out << oBacktrace.m_oBacktraceInfo;
}

}
