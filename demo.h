//
// Created by 10791 on 2022/9/19.
//

#ifndef MSHR_DEMO_H
#define MSHR_DEMO_H

#include <cstdio>
#include <string>
#include "map"
#include "vector"
#include "algorithm"

class mshr_sim {
public:
    static int max_entry;
    static int max_merge;

    std::string mshr_probe(long long addr);

    std::string mshr_full();

    void mshr_add(long long addr, std::string mf_s);

    void mshr_delete(long long addr, std::string merge);

    void mshr_print();

    mshr_sim();

    std::map<long long, std::vector<std::string> > mshr_table; //不需要new //table 的行是 entry, 列是merge
};

int mshr_sim::max_entry = 2;
int mshr_sim::max_merge = 3;

mshr_sim::mshr_sim() {

}

std::string mshr_sim::mshr_probe(long long addr) {
    auto it = this->mshr_table.find(addr);
    return it != this->mshr_table.end() ? "true" : "false"; // true means addr exists
}

std::string mshr_sim::mshr_full() {
    return max_entry == this->mshr_table.size() ? "true" : "false";
}


void mshr_sim::mshr_add(long long addr, std::string mf_s) {
    if (this->mshr_table.find(addr) == this->mshr_table.end()) //如果没有
    {
        std::vector<std::string> merge_list;
        merge_list.push_back(mf_s);
        this->mshr_table.insert({addr, merge_list}); //插入pair(容器为map)
    } else {
        if (this->mshr_table[addr].size() >= mshr_sim::max_merge) {
            printf("max merge\n");
        } else {
            this->mshr_table[addr].push_back(mf_s);
            printf("%d\n", addr);
        }
    }
}


void mshr_sim::mshr_delete(long long addr, std::string merge) {
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
                printf("erase merge %s in the addr successfully\n", merge.c_str());
            }
        }
    }
}


void mshr_sim::mshr_print() {
    printf("address      ");
    printf("member fetch\n");
    for (auto entry: mshr_table) {
        printf("0x%.-8x", entry.first); //以十六进制输出
        for (auto merge: entry.second) {
            printf(" %s", merge.c_str()); //再转换成C字符串
        }
        printf("\n");
    }
}


#endif //MSHR_DEMO_H
