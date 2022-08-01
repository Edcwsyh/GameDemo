/*
    > File Name: BaseLogger.hpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2022年07月24日 星期日 11时22分24秒
*/

#ifndef __BASELOGGER_EDC__
#define __BASELOGGER_EDC__

#include <string_view>
namespace Edc {

class BaseLogger {
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
    BaseLogger() = default;
    explicit BaseLogger( const BaseLogger& ) = default;
    explicit BaseLogger( BaseLogger&& ) = default;
    virtual ~BaseLogger() = default;
    BaseLogger& operator=( const BaseLogger& ) = default;
    BaseLogger& operator=( BaseLogger&& ) = default;

    virtual void write(std::string_view info) = 0;
//Static Member Function
public:
    
};

}

#endif
