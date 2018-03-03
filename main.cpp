#include"MainWindow.h"
#include<memory>

int main()
{
    std::unique_ptr<TSDK::TWindow> window;
    window.reset(new MainWindow());
    window->event();
    return 0;
}
