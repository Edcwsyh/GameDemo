/*
    > File Name: StringTools.hpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: Fri Mar 25 16:13:08 2022
*/

#ifndef __STRINGTOOLS_EDC__
#define __STRINGTOOLS_EDC__

#include <string>
#include <regex>
#include <string_view>
#include <vector>

namespace Edc {

class StringTools {
//Type
public:
    
//Constant
public:
protected:
    
//Member Variables
protected:
    std::regex m_pattern;
    
//Static Member Variables
protected:
    
//Member Function
public:
    StringTools() = default;
    explicit StringTools( const StringTools& ) = default;
    explicit StringTools( StringTools&& ) = default;
    ~StringTools() = default;
    StringTools& operator=( const StringTools& ) = default;
    StringTools& operator=( StringTools&& ) = default;

    /**
     * @description midstr 提取某两个字符串中间的字符串
     *
     * @param oldStr 原字符串
     * @param beginStr 开始的字符串
     * @param endStr 结束的字符串
     *
     * @return 
     */
    std::string midstr( const std::string& oldStr, std::string_view beginStr, std::string endStr );
    
    /**
     * @description split 分割字符串
     *
     * @param oldStr 原字符串
     * @param splitStr 用于分割的字符串
     *
     * @return 字符串集合
     */
    std::vector<std::string> split( const std::string& oldStr, const char* splitStr );

//Static Member Function
public:
    
};

}
#endif
