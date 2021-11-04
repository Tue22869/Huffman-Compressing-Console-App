#include "HeapTree.h"

HeapTree::HeapTree() {
    Clean();
}

void HeapTree::Add(std::pair<size_t, Node *> new_v) {
    size_t current_v;
    size_t parent;
    current_v = heap_size_;
    h_[current_v] = new_v;
    parent = (current_v - 1) / 2;
    while (parent >= 0 && current_v > 0) {
        if (std::make_pair(h_[current_v].first, h_[current_v].second->prior) <
            std::make_pair(h_[parent].first, h_[parent].second->prior)) {
            std::swap(h_[current_v], h_[parent]);
        }
        current_v = parent;
        parent = (current_v - 1) / 2;
    }
    heap_size_++;
}

void HeapTree::Heapify(size_t current_v) {
    size_t left = 2 * current_v + 1;
    size_t right = 2 * current_v + 2;
    if (left < heap_size_) {
        if (std::make_pair(h_[current_v].first, h_[current_v].second->prior) >
            std::make_pair(h_[left].first, h_[left].second->prior)) {
            std::swap(h_[current_v], h_[left]);
            Heapify(left);
        }
    }
    if (right < heap_size_) {
        if (std::make_pair(h_[current_v].first, h_[current_v].second->prior) >
            std::make_pair(h_[left].first, h_[left].second->prior)) {
            std::swap(h_[current_v], h_[right]);
            Heapify(right);
        }
    }
}

std::pair<size_t, Node *> HeapTree::GetMin() {
    std::pair<size_t, Node *> min_v = h_[0];
    h_[0] = h_[heap_size_ - 1];
    --heap_size_;
    Heapify(0);

    return min_v;
}

void HeapTree::Clean() {
    h_.clear();
    heap_size_ = 0;
    Node *node;
    h_.assign(SIZE, std::make_pair(0, node));
}
