#ifndef JDMA_H_
#define JDMA_H_

#include <deque>
#include <mutex>
#include <queue>
#include <tuple>
#include <iostream>
#include <condition_variable>

class jdma {

public:

    ////////////////////////////////////////////////////
    /// Constructor
    ////////////////////////////////////////////////////
    jdma();

    ////////////////////////////////////////////////////
    /// Command queue for the DMA
    /// @param length - length of the transaction in bytes
    /// @param src - source pointer for the data
    /// @param dst - destination pointer for the data
    ////////////////////////////////////////////////////
    void cmd(size_t length, uintptr_t src, uintptr_t dst);

    ////////////////////////////////////////////////////
    /// Command queue for the DMA
    /// @param cmd - command to process
    ////////////////////////////////////////////////////
    void cmd(std::tuple<size_t, uintptr_t, uintptr_t>& cmd);

    ////////////////////////////////////////////////////
    /// Process the commands in the queue
    ////////////////////////////////////////////////////
    void process();

private:

    std::queue<std::tuple<size_t, uintptr_t, uintptr_t>> m_cmds;
    std::condition_variable m_avail;
    std::condition_variable m_proc;
    std::mutex m_dmutex;
};

#endif // JDMA_H_
