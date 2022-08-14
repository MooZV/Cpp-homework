//
// Created by MooZV on 2022/5/31.
//
#include "conversion.h"

std::shared_ptr<Map> Map::map_ = nullptr; // 懒汉式  任意文件的加密解密

bool Map::setMap(const bool & flag,const std::string & codefile ){
    if(map_ == nullptr)
        map_ = std::shared_ptr<Map>(new Map);

    std::ifstream code;
    code.open(codefile,std::ios::binary);
    if(code.is_open()){
        char c;
        int i = 0;
        while(!code.eof()){
            code.get(c);
            if(code.eof()) break;
            std::string key(1,c);
            std::string value(1,decode(i++));
            if(flag){
                key.swap(value);
            }
            Map::map_->order[key] = value;
        }
    } else{
        std::cerr << "codebook open fail"<<std::endl;
    }
    code.close();
    if(map_->order.empty()){
        std::cerr << "codebook loading error" <<std::endl;
        return false;
    }
    return true;
}



