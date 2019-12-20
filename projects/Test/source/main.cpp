
#include "LogDog\TestLogDog.h"
#include "Graphics\TestGraphics.h"

#include <memory>
#include <iostream>
using namespace std;

void input(std::shared_ptr<int>& ptr)
{
    printf("%d\n", ptr.use_count());
    std::shared_ptr<int> ptrT(new int(6), [](int* ptr)
    {
        printf("ptrT:%p delete\n", ptr);
        delete ptr;
        ptr = nullptr;
    }
    );

    printf("ptrT: %d %p %d\n", ptrT.use_count(), ptrT);
    printf("ptrT:%p %d\n", &ptrT, ptrT.use_count());

    cout << ptrT.use_count();
}
int main()
{
    std::shared_ptr<int> ptr(new int(5), [](int* ptr)
    {
        printf("ptr delete\n"); delete ptr; ptr = nullptr;
    });

    printf("%d\n", ptr.use_count());

    input(ptr);

    return 0;
}

// int main()
// {
//     char *p = "abcedfg";
//     char *substr = "ed";
//     while (p = ::strstr(p, substr));
// 
//     MyConsoleWnd Console;
//     Console.Loop();
// 
//     ::system("pause");
//     return 1;
// }



