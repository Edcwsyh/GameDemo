/*
    > File Name: EdcEnv.h
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2022年07月24日 星期日 11时30分56秒
*/

#ifndef __EDCENV_EDC__
#define __EDCENV_EDC__

#include <cstdint>
namespace Edc {

class EdcEnv {
//Type
public:
    
//Constant
public:
    // 缓冲区大小 -- 最小 64
    static constexpr uint32_t BUFSIZE_TINY = 64;
    // 缓冲区大小 -- 小 256
    static constexpr uint32_t BUFSIZE_LOW = 256;
    // 缓冲区大小 -- 512
    static constexpr uint32_t BUFSIZE = 512;
    // 缓冲区大小 -- 大 1024
    static constexpr uint32_t BUFSIZE_BIG = 1024;
    // 缓冲区大小 -- 最大 2048
    static constexpr uint32_t BUFSIZE_MAX = 2048;
protected:
    
//Member Variables
protected:
    
//Static Member Variables
protected:
    
//Member Function
public:
    EdcEnv() = delete;
    explicit EdcEnv( const EdcEnv& ) = delete;
    explicit EdcEnv( EdcEnv&& ) = delete;
    ~EdcEnv() = default;
    EdcEnv& operator=( const EdcEnv& ) = delete;
    EdcEnv& operator=( EdcEnv&& ) = delete;
//Static Member Function
public:
    
};

}

#endif
