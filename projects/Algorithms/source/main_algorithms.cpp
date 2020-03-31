#include "KMP/KMPStrCmp.h"

#include "BinaryTree/BinaryTreeTraversal.h"


// 内存泄露检测器
// 没有64位的
// #ifndef NDEBUG
// #pragma comment(lib, "vld//release//vld.lib")
// #include "vld//head//vld.h"
// #endif

int main()
{
    int i = 0;
    //while (i < 10000)
    {
        Test1();
        Test2();
        Test3();
        Test4();
        Test5();
        ++i;
    }

    TestBinaryTreeTraversal();
    return 1;
}