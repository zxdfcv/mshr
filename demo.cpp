//
// Created by 10791 on 2022/9/19.
//

#include "demo.h"
#include <cstdio>
#include "string"
#include "map"
#include "iostream"


int main() {
    freopen("ans.txt", "r", stdin); //后期可增加string类型
    //char line[105]; 可以整行读入, 再进行识别
    mshr_sim *mshr_test = new mshr_sim(); //指针类型
    int type;
    while (fscanf(stdin, "%d", &type) != EOF) {
        long long addr;
        int merge;
        //fscanf(stdin, "%d", &type); //不能重复读入
        switch (type) {
            case 1:
                fscanf(stdin, "%lld", &addr);
                std::cout << mshr_test->mshr_probe(addr) << std::endl;
                break;
            case 2:
                std::cout << mshr_test->mshr_full() << std::endl;
                break;
            case 3:
                fscanf(stdin, "%lld", &addr);
                mshr_test->mshr_add(addr);
                break;
            case 4:
                fscanf(stdin, "%lld%d", &addr, &merge);
                mshr_test->mshr_delete(addr, merge);
                break;
            case 5:
                mshr_test->mshr_print();
                break; //mf可以像流水线一样增加
            default:
                break;
        }
    }

    //printf("Hello world!");

    fclose(stdin);
    return 0; //test
}
