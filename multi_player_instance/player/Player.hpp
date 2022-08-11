/*
    > File Name: Player.hpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2022年08月01日 星期一 21时40分39秒
*/

#ifndef __PLAYER_EDC__
#define __PLAYER_EDC__

#include <string>
#include <string_view>

namespace Demo {

class Player {
//Type
public:
    enum AIType {
        ENM_NO_AI = 0, //不是AI
        ENM_NORMAL_AI, //普通AI
    };
    
//Constant
public:
protected:
    
//Member Variables
protected:
    // 用户ID
    uint64_t m_ullUserID;
    // 用户名
    std::string m_sUsername;
    // AI类型
    AIType m_enumAI;
    // 所在副本的ID
    uint64_t m_ullCurInstanceID;
    
//Static Member Variables
protected:
    
//Member Function
public:
    Player() = default;
    Player( std::string_view username, AIType enmAItype ) : m_sUsername( username ), m_enumAI( enmAItype ) {  }
    explicit Player( const Player& ) = default;
    explicit Player( Player&& ) = default;
    ~Player() = default;
    Player& operator=( const Player& ) = default;
    Player& operator=( Player&& ) = default;

    uint64_t get_user_id() const noexcept { return m_ullUserID; }
    void set_user_id( uint64_t ullUserID ) noexcept { m_ullUserID = ullUserID; }

    const std::string& get_username() const noexcept { return m_sUsername; }
    void set_username( const std::string_view username ) noexcept { m_sUsername = username; }

    AIType get_ai_type() const noexcept { return m_enumAI; }
    bool is_ai() const noexcept { return get_ai_type() != ENM_NO_AI; }

    uint64_t get_cur_instance_id() const noexcept { return m_ullCurInstanceID; }
    void set_cur_instance_id( uint64_t ullInstanceID ) noexcept { m_ullCurInstanceID = ullInstanceID; }

    std::string debug_info() const noexcept;
    
//Static Member Function
public:
    
};

}

#endif
