#include "jdma.h"
#include <cstring>

// Constructor
jdma::jdma() : m_cmds(),
               m_dmutex()
{}

// Command queue for the DMA
void jdma::cmd(size_t length, uintptr_t src, uintptr_t dst) {
    std::unique_lock<std::mutex> lock(m_dmutex);
    m_cmds.emplace(length, src, dst);
    lock.unlock();
}

// Command queue for the DMA
void jdma::cmd(std::tuple<size_t, uintptr_t, uintptr_t>& cmd) {
    std::unique_lock<std::mutex> lock(m_dmutex);
    m_cmds.push(cmd);
    lock.unlock();
}

void jdma::process() {
    std::unique_lock<std::mutex> lock(m_dmutex);

    auto nxt = m_cmds.front();
    memcpy((uint8_t*)std::get<2>(nxt), (uint8_t*)std::get<1>(nxt), std::get<0>(nxt));
    m_cmds.pop();

    lock.unlock();
}
