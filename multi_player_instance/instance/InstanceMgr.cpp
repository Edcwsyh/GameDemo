/*
    > File Name: InstanceMgr.cpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2022年08月10日 星期三 21时52分45秒
*/

#include "InstanceMgr.hpp"
#include "instance/Instance.hpp"
#include "player/Player.hpp"
#include "dep/LogMgr.hpp"
#include "stlextension/Iterator.hpp"
#include <utility>

namespace Demo {

void InstanceMgr::enter_map(Player& oPlayer) {
    // 先判断玩家能否进入副本
    if ( can_enter( oPlayer ) ) {
        return;
    }
    // 检测并创建副本
    check_and_create_instance();
    // 直接取数量列表的第一个副本, 该副本人数一定最多
    auto pInstance = m_oUserNumMap.begin();
    if ( pInstance == m_oUserNumMap.end() || !pInstance->second ) {
        LOG_ERR( "System exception!" );
        return;
    }
    Demo::Instance& oInstance = *(pInstance->second);
    // 玩家进入副本
    oInstance.enter( oPlayer );
    // 关联玩家与副本对象
    m_oUserInstanceMap[oPlayer.get_user_id()] = &oInstance;
    LOG_DBG( "Player enter instance | %s", oPlayer.debug_info().c_str() );

    if ( oPlayer.is_ai() ) {
        return;
    }
    // 先验证迭代器是否还有效
    if ( !Edc::verify_iterator( m_oUserNumMap, pInstance ) ) {
        return;
    }
    // 以下逻辑仅对真实玩家生效
    // 玩家没满时建立数量映射
    if ( !oInstance.is_full() ) {
        m_oUserNumMap.insert( pInstance, std::make_pair( oInstance.get_real_player_num(), &oInstance ) );
    }
    // 删除旧的数量映射
    m_oUserNumMap.erase( pInstance );
}

void InstanceMgr::leave_map(Player& oPlayer) {
    // 先找到副本对象
    auto pInstance = m_oUserInstanceMap.find( oPlayer.get_user_id() );
    if ( pInstance == m_oUserInstanceMap.end() ) {
        LOG_ERR( "Player no in instance ! | %s", oPlayer.debug_info().c_str() );
        return;
    }
    Demo::Instance& oInstance = *(pInstance->second);
    // 玩家离开副本
    oInstance.leave( oPlayer );
    LOG_DBG( "Player leave instance | %s", oPlayer.debug_info().c_str() );
    if ( oPlayer.is_ai() ) {
        return;
    }
    // 玩家离开前的真实玩家数量
    uint32_t uPreRealPlayerNum = oInstance.get_real_player_num() + 1;
    // 之前没有达到最大数量, 那么一定建立了NumMap
    if ( uPreRealPlayerNum != oInstance.get_player_num_limit() ) {
        auto pTarget = get_instance_from_num_map( uPreRealPlayerNum, oInstance.get_room_id() );
        if ( pTarget == m_oUserNumMap.end() ) {
            LOG_FATAL( "System exception! No nummap was created! | %s", oPlayer.debug_info().c_str() );
        } else {
            m_oUserNumMap.erase( pTarget );
        }
    }
    m_oUserNumMap.insert( std::make_pair( oInstance.get_real_player_num(), &oInstance ) );
}

InstanceMgr::NumMap::iterator 
InstanceMgr::get_instance_from_num_map(uint32_t uNum, uint64_t ullInstanceID) noexcept 
{
    auto pTarget = m_oUserNumMap.find( uNum );
    if ( pTarget == m_oUserNumMap.end() ) {
        return pTarget;
    }
    for ( ; pTarget != m_oUserNumMap.end() && pTarget->first == uNum; ++pTarget ) {
        if ( ullInstanceID == pTarget->second->get_room_id() ) {
            return pTarget;
        }
    }
    return pTarget;
}

}
