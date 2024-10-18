#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<sstream>

struct PCB { // def process control block
    std::string name;
    int arrive;
    int exetime;

    bool operator<(const PCB& other) const {
        return exetime > other.exetime;
        // 按照执行时间排序，执行时间越短优先级越高
    }
};
/*
短作业优先的调度算法
 SJF算法是以作业的长短来计算优先级，作业越短，其优先级越高。
 作业的长短是以作业所要求的运行时间来衡量的。SJF算法可以分别用于作业调度和进程调度。
 在把短作业优先调度算法用于作业调度时，
 它将从外存的作业后备队列中选择若干个估计运行时间最短的作业，
 优先将它们调入内存运行。
*/
/*
* self:
        {"QQ",12,0},
        {"Wechat",13,0},
        {"Vscode",5,4},
        {"Pycharm",9,2},
        {"Python-GPU0",39,6},
        {"Chrome",3,3},
        {"System",4,9}

* demo 2:
        {"QQ",0,4},
        {"Wechat",1,3},
        {"Vscode",2,5},
        {"Pycharm",3,2},
        {"Python-GPU0",4,4}
* demo 1:
        {"QQ",0,1},
        {"Wechat",1,100},
        {"Vscode",2,1},
        {"Pycharm",3,100}
*/
int main() {
    std::cout << "初始化PCB列表\n" << std::endl;
    PCB ps[] = {
        {"A",0,4},
        {"B",1,3},
        {"C",2,5},
        {"D",3,2},
        {"E",4,4}
    };
    // 建立到达时间优先队列
    std::vector<PCB> arrival_list(std::begin(ps), std::end(ps));

    // 建立空的SJF队列
    std::priority_queue<PCB, std::vector<PCB>> sjf_queue;

    // 当前累计时间
    int accTime = 0,preacc=0 ;
    int PID = 0;

    std::cout << "PID 从1开始计算：\n";

    while (!arrival_list.empty() || !sjf_queue.empty()) {
        // 当SJF队列为空时，从非空的到达队列中取出一个进程
        if (sjf_queue.empty() && !arrival_list.empty()) {
            sjf_queue.push(*arrival_list.begin());
            arrival_list.erase(arrival_list.begin());
        }

        // 运行SJF队列中最短的作业
        PCB current = sjf_queue.top();
        sjf_queue.pop();

        PID++;

        preacc = accTime;
        accTime += current.exetime;

        std::cout << "[PID]:" << PID << std::endl;
        std::cout << "[sys]   : " << current.name << "上CPU " << std::endl;
        std::cout << "到达时间: " << current.arrive << std::endl;
        std::cout << "服务时间: " << current.exetime << std::endl;
        // 模拟运行
        std::cout << "完成时间: " << accTime << std::endl;

        // 周转时间
        int TAR = accTime - current.arrive;
        std::cout << "周转时间: " << TAR << std::endl;

        // 带权周转时间
        float wTAR = TAR*1.0f / current.exetime;
        std::cout << "带权TAR : " << wTAR << std::endl << std::endl;

        bool have = 1;
        while (have && !arrival_list.empty()) {
            auto it = *arrival_list.begin();
            if (it.arrive < accTime) {
                have = true;
                sjf_queue.push(*arrival_list.begin());
                arrival_list.erase(arrival_list.begin());
            }
            else {
                have = false;
            }
        }
    }



    return 0;
}


