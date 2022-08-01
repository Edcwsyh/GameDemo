/*
    > File Name: BaseInstance.hpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2022年08月01日 星期一 21时54分35秒
*/

#ifndef __BASEINSTANCE_EDC__
#define __BASEINSTANCE_EDC__

#include <cstdint>
namespace Demo {

class Player;

class BaseInstance {
//Type
public:
    
//Constant
public:
protected:
    
//Member Variables
protected:
    // 房间ID
    uint64_t m_ullRoomID;
    
//Static Member Variables
protected:
    
//Member Function
public:
    BaseInstance() = default;
    explicit BaseInstance( const BaseInstance& ) = default;
    explicit BaseInstance( BaseInstance&& ) = default;
    ~BaseInstance() = default;
    BaseInstance& operator=( const BaseInstance& ) = default;
    BaseInstance& operator=( BaseInstance&& ) = default;

    // 获取房间ID
    uint64_t get_room_id() const noexcept { return m_ullRoomID; }
    // 设置房间ID
    void set_room_id( uint64_t ullRoomID ) noexcept { m_ullRoomID = ullRoomID; }

    // 进入副本
    virtual void enter( Player& oPlayer ) = 0;
    // 离开副本
    virtual void leave( Player& oPlayer ) = 0;
//Static Member Function
public:
    
};

}

#endif
