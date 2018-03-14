整理要点:
C/C++伪随机数
C头文件:#include<stdlib.h>
C++:#include<iostream>或者#include<cstdlib>
void srand(unsigned int)
rand()

example:
srand((unsigned int)time(NULL));
rand();//获取[0,1]范围内的数字

C++11真随机数:
C++头文件:#include<random>
std::default::random::engine随机非负数引擎类
std::uniform_int_distribution<>(min,max)特定范围的非负数

example:
std::default::random_engine random;
std::uniform_int_distribution<T> range(min,max);//生成[min,max]范围内的随机数
range(random);//生成随机数

C++11智能指针:
C++头文件:#include<memory>
std::unique_ptr<T>

example:
std::unique_ptr<T> p;
p.reset(new T);
p->function();//访问T模板的指针

C++11线程:
C++头文件:#include<thread>
std::thread

example:
void function()

std::thread th(function);//此处可用std::bind绑定函数
th.join();//or th.detach();
