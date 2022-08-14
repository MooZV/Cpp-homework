//
// Created by MooZV on 2022/5/31.
//
#include "conversion.h"
#include <string>
#include <sstream>
#include <thread>

std::string decode(const int & c){
    return std::to_string(c);
}

std::queue<std::string> que;
std::mutex mut;
std::condition_variable cv;
std::atomic_bool ato(false);

// 生产者
void producer(const std::string &file) {
    // std::cout << "producer=" << std::this_thread::get_id() << std::endl;
    std::ifstream f;
    f.open(file, std::ios::binary);
    if (f.is_open()) {
        ato = true;
        std::string c;
        while(!f.eof()) {
            f >> c;
            if(f.eof()) break;
            usleep(1000);
            std::lock_guard<std::mutex> locker(mut);
            que.push(c);
            cv.notify_one();
//            f >> c;
        }
    } else
        std::cout << file << "open fail" << std::endl;
    f.close();
    ato = false;
    // std::cout << "thread 1 over"<< std::endl;
    return;
}
// 消费者
void comsumer(const std::string &file) {
    // std::cout << "consumer=" << std::this_thread::get_id() << std::endl;
    std::ofstream f;
    f.open(file, std::ios::binary);
    if (f.is_open()) {
        while (ato) {
            std::unique_lock<std::mutex> cn(mut);
            cv.wait_for(cn, std::chrono::seconds(1), [] {
                return !que.empty();
            });
            std::string temp = que.front();
            f << Map::get(temp);
            std::cout << Map::get(temp);
            que.pop();
        }
        printf("\n");
    } else
        std::cout << file << "open fail" << std::endl;
    f.close();
    // std::cout << "thread 2 over" << std::endl;
    return;
}
int main(int argc, char *argv[]) {
    //project3 encrypt 码本文件名 输入文件名 输出文件名

    if(argc != 5){
        std::cerr <<  std::endl << "Usage: ./main ../code.txt ../encrypt.txt ../decrypt.txt"<< std::endl;
        return -1;
    }

    bool flag =  std::string(argv[1]) == "encrypt" ? true : false;

    if( ! Map::setMap(flag, argv[2]))
        printf("hashMap build failed\n");


    std::string inputfile(argv[3]);
    std::string outputfile(argv[4]);
    if(!flag)
        inputfile.swap(outputfile);

    std::thread t1 = std::thread(std::bind(producer, inputfile));
    std::thread t2 = std::thread(std::bind(comsumer, outputfile));

    t1.join();
    t2.join();
    // std::cout << "main=" << std::this_thread::get_id() << std::endl;

    return 0;
}
