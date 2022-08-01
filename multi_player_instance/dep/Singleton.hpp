/*
    > File Name: Singleton.hpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2021年12月21日 星期二 11时42分54秒
*/

#ifndef __SINGLETON_EDC__
#define __SINGLETON_EDC__

namespace Edc{

template <typename T>
class Singleton {
//Type
public:
    
//Constant
public:
protected:
    
//Member Variables
protected:
    
//Static Member Variables
protected:
    
//Member Function
public:
    Singleton() = default;
public:
    Singleton( const Singleton& ) = delete;
    Singleton( Singleton&& ) = delete;
    ~Singleton() = default;
    Singleton& operator=( const Singleton& ) = default;
    Singleton& operator=( Singleton&& ) = delete;
    
    static T& instance() {
        static T entry;
        return entry;
    }

    static T& Instance() {
        return instance();
    }
//Static Member Function
public:
    
};

}
#endif
