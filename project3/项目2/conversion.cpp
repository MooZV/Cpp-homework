//
// Created by MooZV on 2022/5/31.
//
#include "conversion.h"

std::shared_ptr<Map> Map::map_ = nullptr; // ¿¡∫∫ Ω

bool Map::setMap(const bool & flag,const std::string & codefile ){
    if(map_ == nullptr)
        map_ = std::shared_ptr<Map>(new Map);

    std::ifstream code;
    code.open(codefile,std::ios::binary);
    if(code.is_open()){
        std::string key;
        int i = 0;
        while(!code.eof()){
            code >> key;
            std::string value = decode(i++);
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



