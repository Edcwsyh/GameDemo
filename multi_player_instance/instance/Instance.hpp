/*
    > File Name: Instance.hpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2022年08月01日 星期一 21时43分37秒
*/

#ifndef __INSTANCE_EDC__
#define __INSTANCE_EDC__

#include <cstdint>
#include <memory>
#include <unordered_set>
#include <vector>
#include "BaseInstance.hpp"
namespace Demo {

class Player;

class Instance : public BaseInstance {
//Type
public:
    
//Constant
public:
protected:
    
//Member Variables
protected:
    // 副本内的真实玩家
    std::unordered_set<Player*> m_oAllPlayer;
    // 副本内的AI玩家
    std::vector<std::shared_ptr<Player>> m_oAIPlayer;
    // 副本剩余时间(秒)
    time_t m_countdown;
    // 副本玩家数量上限
    uint32_t m_ullPlayerNumLimit;
    
//Static Member Variables
protected:
    
//Member Function
public:
    Instance() = default;
    explicit Instance( const Instance& ) = default;
    explicit Instance( Instance&& ) = default;
    ~Instance() = default;
    Instance& operator=( const Instance& ) = default;
    Instance& operator=( Instance&& ) = default;

    // 进入副本
    virtual void enter( Player& oPlayer ) override;
    // 离开副本
    virtual void leave( Player& oPlayer ) override;

    // 获得副本内的真实玩家数量
    uint32_t get_real_player_num() const noexcept { return m_oAllPlayer.size(); }
    // 获得副本内的AI玩家数量
    uint32_t get_ai_player_num() const noexcept { return m_oAIPlayer.size(); }
    // 副本是否爆满
    bool is_full() const noexcept { return get_real_player_num() == m_ullPlayerNumLimit; }
    // 获取副本玩家数量限制  
    uint32_t get_player_num_limit() const noexcept { return m_ullPlayerNumLimit; }
//Static Member Function
public:
    
};

}

#endif
