/*
    > File Name: TimeTools.hpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2021年02月21日 星期日 14时11分13秒
*/

#ifndef __TIMETOOLS_EDC__
#define __TIMETOOLS_EDC__

#include <string>

namespace Edc {

class TimeTools {
//Constant
public:
    enum FixTimeVal {
        FIX_TIME_UNKNOW = 0, // 未知
        FIX_TIME_BEIJING = 28800,  // 北京时间
    };

    static constexpr const char* TIME_DEF_FMT = "%Y-%m-%d %H:%M:%S";

private:
    static FixTimeVal s_uTimeFixVal; //时间修正值

public:
    TimeTools() = delete;
    explicit TimeTools( const TimeTools& ) = delete;
    explicit TimeTools( TimeTools&& ) = delete;
    ~TimeTools() = default;
    TimeTools& operator=( const TimeTools& ) = delete;
    TimeTools& operator=( TimeTools&& ) = delete;

    /**
     * @description strfmttime 将时间戳转化为固定格式( 该函数保证线程安全 )
     *
     * @param timestamp 需要转化的时间戳
     *
     * @return 
     */
    static std::string strfmttime_safe( time_t timestamp = ::time(0), const char* fmt = TIME_DEF_FMT );

    //效率最高，线程不安全
    static const char* _strfmttime( time_t timestamp = ::time(0), const char* fmt = TIME_DEF_FMT );

    static std::string strfmttime( time_t timestamp = ::time(0), const char* fmt = TIME_DEF_FMT ) {
        return _strfmttime( timestamp, fmt );
    }

    void set_fix_time( FixTimeVal uTimeFixVal ) const noexcept { s_uTimeFixVal = uTimeFixVal; }

};

}
#endif
