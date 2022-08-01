/*
    > File Name: StringTools.cpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: Fri Mar 25 16:17:30 2022
*/

#include "StringTools.hpp"
#include <iterator>
#include <regex>

namespace Edc {

std::string StringTools::midstr( const std::string& oldStr, std::string_view beginStr, std::string endStr )
{
    std::smatch result;
    std::string resourse = ".*?";
    ( ( ( resourse += beginStr ) += "(.*?)" ) += endStr ) += ".*?";
    m_pattern.assign( resourse );
    if ( !std::regex_match( oldStr, result, m_pattern ) ) {
        throw std::runtime_error( "Regular expression error! : " + resourse + ", string : " + oldStr );
    }
    if ( result.size() >= 2 ) {
        return result[1];
    }
    return nullptr;
}


std::vector<std::string> StringTools::split( const std::string& oldStr, const char* splitStr ) {
    m_pattern.assign( splitStr );
    std::sregex_token_iterator start { oldStr.begin(), oldStr.end(), m_pattern, -1 }, end;
    return { start, end };
}

}
