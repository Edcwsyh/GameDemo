/*
    > File Name: TimeTools.cpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2021年02月21日 星期日 18时07分31秒
*/

#include "TimeTools.hpp"
#include "EdcEnv.h"

namespace Edc {

const char* TimeTools::_strfmttime( time_t timestamp, const char* fmt ) {
    static char buffer[EdcEnv::BUFSIZE_LOW];
    ::tm oTimeTmp;
    timestamp += s_uTimeFixVal;
    ::gmtime_r( &timestamp, &oTimeTmp );
    ::strftime( buffer, EdcEnv::BUFSIZE_LOW, fmt, &oTimeTmp );
    return buffer;
}

std::string TimeTools::strfmttime_safe( time_t timestamp, const char* fmt ) {
    char buffer[EdcEnv::BUFSIZE_LOW];
    ::tm oTimeTmp;
    timestamp += s_uTimeFixVal;
    ::gmtime_r( &timestamp, &oTimeTmp );
    ::strftime( buffer, EdcEnv::BUFSIZE_LOW, fmt, &oTimeTmp );
    return buffer;
}

}

