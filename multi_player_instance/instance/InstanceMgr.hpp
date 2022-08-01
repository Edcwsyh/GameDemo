/*
    > File Name: InstanceMgr.hpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2022年08月01日 星期一 22时07分10秒
*/

#ifndef __INSTANCEMGR_EDC__
#define __INSTANCEMGR_EDC__

#include "dep/Singleton.hpp"
#include "Instance.hpp"
#include <memory>
#include <unordered_set>
#include <vector>
#include <list>
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
    // 副本列表
    std::unordered_set<Instance> m_oAllInstance;

    
//Static Member Variables
protected:
    
//Member Function
private:
    InstanceMgr() = default;
    friend Edc::Singleton<InstanceMgr>;
public:
    explicit InstanceMgr( const InstanceMgr& ) = delete;
    explicit InstanceMgr( InstanceMgr&& ) = delete;
    ~InstanceMgr() = default;
    InstanceMgr& operator=( const InstanceMgr& ) = delete;
    InstanceMgr& operator=( InstanceMgr&& ) = delete;
//Static Member Function
public:
    
};

}

#endif
