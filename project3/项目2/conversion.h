//
// Created by MooZV on 2022/5/31.
//

#ifndef ALGORITHM_CONVERSION_H
#define ALGORITHM_CONVERSION_H

#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <fstream> // 读取文件
#include <queue>    // 队列
#include <unordered_map>
#include <memory> // 智能指针

#include <mutex>
#include <atomic>
#include <condition_variable>
#include <thread>
#include <functional>
#include "unistd.h"

std::string decode(const int & c);
// 构建hashmap，用于存储码本，单例模式
class Map{
    static std::shared_ptr<Map> map_; // 智能指针私有，只允许类访问
    std::unordered_map<std::string ,std::string> order;  // 私有，不许写
    Map(){}     // 不许外部实例化
public:
    ~Map() = default;
    // 设置映射关系
    static bool setMap(const bool & flag,const std::string & codefile );
    // 获取键对应的值
    static std::string get(const std::string & key){
        if(Map::map_->order.find(key) != Map::map_->order.end())
            return Map::map_->order[key] + " ";
        return key;
    }
};

#endif //ALGORITHM_CONVERSION_H
