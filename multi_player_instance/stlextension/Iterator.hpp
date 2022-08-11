/*
    > File Name: Iterator.hpp
    > Author: Edcwsyh
    > Mail: const.nullPointer@gmail.com
    > Created Time: 2022年08月11日 星期四 21时23分11秒
*/

#ifndef __ITERATOR_EDC__
#define __ITERATOR_EDC__

#include "dep/LogMgr.hpp"

namespace Edc {

/**
 * @description verify_iterator 验证迭代器在容器container中是否有效
 *
 * @param container
 * @param iter
 *
 * @return 
 */
template<typename T>
bool verify_iterator( const T& oContainer, typename T::const_iterator pTarget ) {
#ifdef EDC_DEBUG
    for ( auto pIter = oContainer.cbegin(); pIter != oContainer.cend(); ++pIter ) {
        if ( pIter == pTarget )
        {
            return true;
        }
    }
    LOG_FATAL( "The iterator is invalid!, container size : %u", oContainer.size() );
    return false;
#else
    return true;
#endif
}

}

#endif
