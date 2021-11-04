#pragma once

#include <utility>
#include <vector>

const size_t NOTHING = 260;

struct Node {
    Node() {
    }
    Node *left_node = nullptr;
    Node *right_node = nullptr;
    size_t symbol = NOTHING;
    size_t amount = 0;
    size_t prior = 0;
};

class HeapTree {
    static const size_t SIZE = 300;

public:
    HeapTree();
    void Add(std::pair<size_t, Node *>);
    std::pair<size_t, Node *> GetMin();
    void Heapify(size_t);
    void Clean();

    size_t heap_size_ = 0;

private:
    std::vector<std::pair<size_t, Node *>> h_;
};
