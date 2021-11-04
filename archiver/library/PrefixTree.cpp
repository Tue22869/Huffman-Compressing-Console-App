#include "PrefixTree.h"
#include <iostream>

PrefixTree::PrefixTree(std::vector<size_t> &numbers_of_symbols) {
    CreatingNewTree(numbers_of_symbols);
}

void PrefixTree::CreatingNewTree(std::vector<size_t> &numbers_of_symbols) {
    prefix_tree_.Clean();
    coding_element_.clear();
    prior_ = 0;

    for (size_t i = 0; i < numbers_of_symbols.size(); ++i) {
        if (numbers_of_symbols[i] > 0) {
            Node *element = new Node;
            element->symbol = i;
            element->prior = ++prior_;
            prefix_tree_.Add(std::make_pair(numbers_of_symbols[i], element));
        }
    }

    std::pair<size_t, Node *> current;
    while (prefix_tree_.heap_size_ > 1) {
        Node *element = new Node;
        current = prefix_tree_.GetMin();
        element->left_node = current.second;
        element->amount = current.first;

        current = prefix_tree_.GetMin();
        element->right_node = current.second;
        element->amount += current.first;

        element->prior = prior_;
        ++prior_;
        prefix_tree_.Add(std::make_pair(element->amount, element));
    }

    std::vector<bool> code;
    GettingCodeBor(code, prefix_tree_.GetMin().second);
    GettingCodeHuffman();
}

void PrefixTree::GettingCodeBor(std::vector<bool> code, const Node *node) {
    if (node->symbol != NOTHING) {
        coding_element_.insert(std::make_pair(code, node->symbol));
    }
    code.push_back(0);
    if (node->left_node != nullptr) {
        GettingCodeBor(code, node->left_node);
    }
    if (node->right_node != nullptr) {
        code.back() = 1;
        GettingCodeBor(code, node->right_node);
    }
}

void PrefixTree::GettingCodeHuffman() {
    std::vector<bool> code;
    size_t previous_size = 0;
    while (!coding_element_.empty()) {
        while (coding_element_.begin()->first.size() > previous_size) {
            ++previous_size;
            code.push_back(0);
        }
        symbol_to_code[coding_element_.begin()->second] = code;
        coding_element_.erase(coding_element_.begin());
        size_t j = code.size();
        while (j > 0 && code[j - 1] == 1) {
            code[j - 1] = 0;
            --j;
        }
        if (j == 0) {
            j = 1;
            code.push_back(0);
        }
        code[j - 1] = 1;
    }
}
