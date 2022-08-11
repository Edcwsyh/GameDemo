/*
    > File Name: InstanceMgr.hpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2022年08月01日 星期一 22时07分10秒
*/

#ifndef __INSTANCEMGR_EDC__
#define __INSTANCEMGR_EDC__

#include <algorithm>
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include "dep/Singleton.hpp"
#include "instance/Instance.hpp"
namespace Demo {

class Player;

class InstanceMgr : public Edc::Singleton<InstanceMgr> {
//Type
public:
    
//Constant
public:
protected:
    
//Member Variables
protected:
    // AI缓存池
    std::vector<std::unique_ptr<Player>> m_oAIPool;
    // 副本列表 <副本ID, 副本实体>
    std::unordered_map<uint64_t, Demo::Instance> m_oAllInstanceMap;
    // 玩所在的副本 <玩家ID, 副本指针>
    std::unordered_map<uint64_t, Demo::Instance*> m_oUserInstanceMap;
    typedef std::multimap<uint32_t, Demo::Instance*, std::greater<uint32_t>> NumMap;
    // 真实玩家副本映射<玩家数量, 副本指针>
    NumMap m_oUserNumMap;

    
//Static Member Variables
protected:
    
//Member Function
private:
    InstanceMgr() = default;
    friend Edc::Singleton<InstanceMgr>;

    // 副本创建
    void create_instance();
    // 副本销毁
    void destroy_instance();
    // 检测并创建副本
    // 当存在可用副本时, 啥都不做
    // 不存在可用副本, 直接创建一个
    void check_and_create_instance();
    // 该玩家能否进入副本
    bool can_enter( Player& oPlayer );
    NumMap::iterator get_instance_from_num_map( uint32_t uNum, uint64_t ullInstanceID ) noexcept;
public:
    explicit InstanceMgr( const InstanceMgr& ) = delete;
    explicit InstanceMgr( InstanceMgr&& ) = delete;
    ~InstanceMgr() = default;
    InstanceMgr& operator=( const InstanceMgr& ) = delete;
    InstanceMgr& operator=( InstanceMgr&& ) = delete;

    // 玩家请求进入副本
    void enter_map( Player& oPlayer );

    // 玩家请求离开副本
    void leave_map( Player& oPlayer );


//Static Member Function
public:
    
};

}

#endif
