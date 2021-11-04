//
// Created by Nguyen Phuc Tue on 04.10.2021.
//
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "Reader.h"
#include "Statistics.h"
#include "PrefixTree.h"
#include "Encoder.h"
#include "Decoder.h"
#include "HeapTree.h"
#include <iostream>

TEST_CASE("Archiver1") {
    std::vector<std::string> files = {"input1.txt", "input2.txt"};
    std::vector<std::string> contents = {"tue", "22869"};
    std::string archive_name = "archive.zz";
    std::ofstream fout;
    for (size_t i = 0; i < files.size(); ++i) {
        fout.open(files[i]);
        fout << contents[i];
        fout.close();
    }

    Encoder encode(archive_name);
    encode.DoEncode(files);
    for (size_t i = 0; i < files.size(); ++i) {
        fout.open(files[i]);
        fout << "trash";
        fout.close();
    }
    Decoder decode(archive_name);
    decode.DoDecode();
    std::ifstream fin;
    for (size_t i = 0; i < files.size(); ++i) {
        fin.open(files[i]);
        std::string content;
        fin >> content;
        fin.close();
        REQUIRE(content == contents[i]);
    }
}

TEST_CASE("CanonisationCheck") {
    std::vector<size_t> numbers_of_symbols;
    numbers_of_symbols.assign(260, 0);
    numbers_of_symbols[97] = 2;
    numbers_of_symbols[98] = 1;
    numbers_of_symbols[99] = 5;
    PrefixTree test_tree(numbers_of_symbols);
    std::vector<bool> a_check = {1, 0};
    std::vector<bool> b_check = {1, 1};
    std::vector<bool> c_check = {0};
    for (auto i : test_tree.symbol_to_code) {
        if (i.first == 97) {
            REQUIRE(a_check == i.second);
        } else if (i.first == 98) {
            REQUIRE(b_check == i.second);
        } else if (i.first == 99) {
            REQUIRE(c_check == i.second);
        }
    }
}

TEST_CASE("HeapTreeCheck") {
    HeapTree test_tree;

    Node *node1 = new Node;
    node1->prior = 2;
    test_tree.Add(std::make_pair(1, node1));

    Node *node2 = new Node;
    node2->prior = 1;
    test_tree.Add(std::make_pair(1, node2));

    REQUIRE(test_tree.GetMin().second->prior == node2->prior);

    Node *node3 = new Node;
    node3->prior = 0;
    test_tree.Add(std::make_pair(0, node3));

    REQUIRE(test_tree.GetMin().second->prior == node3->prior);
}