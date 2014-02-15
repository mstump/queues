// This is free and unencumbered software released into the public domain.

// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.

// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.

// For more information, please refer to <http://unlicense.org/>


// non-intrusive lock free unbounded SPSC queue
// the algorithm was taken from the blog post below, and converted to C++11
// http://cbloomrants.blogspot.com/2009/02/02-26-09-low-level-threading-part-51.html

#ifndef __SPSC_QUEUE_INCLUDED__
#define __SPSC_QUEUE_INCLUDED__

#include <atomic>

template<typename T>
class spsc_queue_t
{
public:

    spsc_queue_t() :
        _head(reinterpret_cast<buffer_node_t*>(new buffer_node_aligned_t)),
        _tail(_head.load(std::memory_order_relaxed))
    {
        buffer_node_t* front = _head.load(std::memory_order_relaxed);
        front->next.store(NULL, std::memory_order_relaxed);
    }

    ~spsc_queue_t()
    {
        T output;
        while (this->dequeue(output)) {}
        buffer_node_t* front = _head.load(std::memory_order_relaxed);
        delete front;
    }

    void
    enqueue(
        const T& input)
    {
        buffer_node_t* node = reinterpret_cast<buffer_node_t*>(new buffer_node_aligned_t);
        node->data = input;
        node->next.store(NULL, std::memory_order_relaxed);

        buffer_node_t* back = _tail.load(std::memory_order_relaxed);
        back->next.store(node, std::memory_order_release);
        _tail.store(node, std::memory_order_relaxed);
    }

    bool
    dequeue(
        T& output)
    {
        buffer_node_t* front = _head.load(std::memory_order_relaxed);
        buffer_node_t* next = front->next.load(std::memory_order_acquire);
        if (next == NULL) {
            // buffer is empty
            return false;
        }
        output = next->data;
        _head.store(next, std::memory_order_release);
        delete front;
        return true;
    }


private:

    struct buffer_node_t
    {
        std::atomic<buffer_node_t*> next;
        T                           data;
    };

    typedef typename std::aligned_storage<sizeof(buffer_node_t), std::alignment_of<buffer_node_t>::value>::type buffer_node_aligned_t;

    std::atomic<buffer_node_t*> _head;
    std::atomic<buffer_node_t*> _tail;

    spsc_queue_t(const spsc_queue_t&) {}
    void operator=(const spsc_queue_t&) {}
};

#endif
