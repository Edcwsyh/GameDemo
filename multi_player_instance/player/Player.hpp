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
    // 用户名
    std::string m_sUsername;
    // AI类型
    AIType m_enumAI;
    
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

    const std::string& get_username() const noexcept { return m_sUsername; }
    void set_username( const std::string_view username ) noexcept { m_sUsername = username; }
    
//Static Member Function
public:
    
};

}

#endif
