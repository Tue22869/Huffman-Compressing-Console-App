#include <vector>
#include <map>
#include <set>
#include "HeapTree.h"

class PrefixTree {
public:
    PrefixTree(std::vector<size_t> &numbers_of_symbols);
    void CreatingNewTree(std::vector<size_t> &numbers_of_symbols);
    std::map<size_t, std::vector<bool>> symbol_to_code;

private:
    struct Cmp2 {
        bool operator()(const std::pair<std::vector<bool>, size_t> &a,
                        const std::pair<std::vector<bool>, size_t> &b) const {
            return std::make_pair(a.first.size(), a.second) < std::make_pair(b.first.size(), b.second);
        }
    };

    void GettingCodeBor(std::vector<bool> code, const Node *);
    void GettingCodeHuffman();

    size_t prior_ = 0;
    std::set<std::pair<std::vector<bool>, size_t>, Cmp2> coding_element_;
    HeapTree prefix_tree_;
};
