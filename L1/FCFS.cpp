#include<iostream>
#include<algorithm>
#include<queue>
#include <vector>
#include<sstream>
// using namespace std;
// E12214052 赵宸宇
struct PCB { // def process control block
    std::string name;
    int arrive;
    int exetime;

    bool operator<(const PCB& other) const {
        return arrive > other.arrive ;
        // 先按到达时间排序，后按照执行时间排序
    }
};
/*
先来先服务(FCFS)调度算法
　FCFS是最简单的调度算法，该算法既可用于作业调度，也可用于进程调度。
　当在作业调度中采用该算法时，系统将按照作业到达的先后次序来进行调度，或者说它是优先考虑在系统中等待时间最长的作业，而不管该作业所需执行时间的长短，从后备作业队列中选择几个最先进入该队列的作业，将它们调入内存，为它们分配资源和创建进程，然后把它放入就绪队列。
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
        {"QQ",0,1},
        {"Wechat",1,100},
        {"Vscode",2,1},
        {"Pycharm",3,100}
    };
    // 建立到达时间优先队列
    std::priority_queue<PCB, std::vector<PCB>> mylist;
    // 逐个导入PCB到表中
    for (auto pcb : ps) {
        mylist.push(pcb);
    }

    // 运行
    int accTime = 0;
    int PID = 0;
    std::cout << "PID 从1开始计算：\n";
    while (!mylist.empty()) {
        // 模拟 就绪队列 上CPU
        PID++;
        std::cout <<"[PID]:"<< PID << std::endl;
        PCB current = mylist.top();
        mylist.pop();

        // 模拟运行
        std::cout << "[sys]   : "<< current.name <<"上CPU " << std::endl;
        std::cout << "到达时间: " << current.arrive << std::endl;
        std::cout << "服务时间: " << current.exetime << std::endl;

        // 完成时间
        accTime += current.exetime;
        std::cout << "完成时间: " << accTime << std::endl;
        // 周转时间
        int TAR = accTime - current.arrive;
        std::cout << "周转时间: " << TAR << std::endl;
        // 带权周转时间
        float wTAR = TAR*1.0f/current.exetime;
        std::cout << "带权TAR : " << wTAR << std::endl << std::endl;
      }



    return 0;
}
// E12214052 赵宸宇