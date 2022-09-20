//
// Created by 10791 on 2022/9/19.
//

#ifndef MSHR_DEMO_H
#define MSHR_DEMO_H

#include <cstdio>
#include "map"
#include "vector"
#include "algorithm"

class mshr_sim {
public:
    static int max_entry;
    static int max_merge;

    bool mshr_probe(long long addr);

    bool mshr_full();

    void mshr_add(long long addr);

    void mshr_delete(long long addr, int merge);

    void mshr_print();

    mshr_sim();

    std::map<long long, std::vector<int> > mshr_table; //不需要new //table 的行是 entry, 列是merge
};

int mshr_sim::max_entry = 100005;
int mshr_sim::max_merge = 105;

mshr_sim::mshr_sim() {

}

bool mshr_sim::mshr_probe(long long addr) {
    auto it = this->mshr_table.find(addr);
    return it != this->mshr_table.end(); // true means addr exists
}

bool mshr_sim::mshr_full() {
    return max_entry == this->mshr_table.size() ? true : false;
}


void mshr_sim::mshr_add(long long addr) {
    if (this->mshr_table.find(addr) == this->mshr_table.end()) //如果没有
    {
        std::vector<int> merge_list;
        merge_list.push_back(1);
        this->mshr_table.insert({addr, merge_list}); //插入
    } else {
        if (this->mshr_table[addr].size() >= mshr_sim::max_merge) {
            printf("max merge\n");
        } else {
            this->mshr_table[addr].push_back(this->mshr_table[addr].size() + 1);
            printf("%d\n", addr);
        }
    }
}


void mshr_sim::mshr_delete(long long addr, int merge) {
    if (this->mshr_table.find(addr) == this->mshr_table.end()) //如果没有
    {
        printf("no such addr\n");
    } else {
        if (this->mshr_table[addr].size() == 0) {
            printf("no merge\n");
        } else {
            auto it = find(this->mshr_table[addr].begin(), this->mshr_table[addr].end(), merge);
            if (it == this->mshr_table[addr].end()) {
                printf("no such merge in the addr\n");
            } else {
                this->mshr_table[addr].erase(it);
                printf("erase %dth merge in the addr successfully\n");
            }
        }
    }
}


void mshr_sim::mshr_print() {
    for (auto entry: mshr_table) {
        printf("%lld:", entry.first);
        for (auto merge: entry.second) {
            printf(" %d", merge);
        }
        printf("\n");
    }
}


#endif //MSHR_DEMO_H
