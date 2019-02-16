//
// Created by qwertysun on 18-12-26.
//

#pragma once

//#define synchronized(m) \
//    for(std::unique_lock<std::recursive_mutex> lk(m); lk; lk.unlock())

static int __mutex_index__ = 0;
#define synchronized static std::recursive_mutex _m_##__mutex_index__;\
    ++__mutex_index__;\
    for (std::unique_lock<std::recursive_mutex> lk(_m_##__mutex_index__); lk; lk.unlock())
