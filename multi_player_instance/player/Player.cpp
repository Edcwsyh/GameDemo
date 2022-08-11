/*
    > File Name: Player.cpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2022年08月11日 星期四 21时08分32秒
*/

#include "Player.hpp"
#include <sstream>

namespace Demo {

std::string Player::debug_info() const noexcept {
    std::stringstream ss;
    ss << "Player : { id : "  << m_ullUserID
       << ", name : " << m_sUsername
       << ", AIType : " << m_enumAI
       << ", instance id : " << m_ullCurInstanceID;
    return ss.str();
}

}

