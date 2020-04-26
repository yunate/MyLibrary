#include "KMP/KMPStrCmp.h"

#include "BinaryTree/BinaryTreeTraversal.h"


// 内存泄露检测器
// 没有64位的
// #ifndef NDEBUG
// #pragma comment(lib, "vld//release//vld.lib")
// #include "vld//head//vld.h"
// #endif

#include <vector>
#include <string>
using namespace std;
int findMinDifference(vector<string> timePoints) {
    int max = 12 * 60;
    vector<int> nt;
    for (auto& it : timePoints)
    {
        int tmp = (it[0] - '0') * 600 + (it[1] - '0') * 60 + (it[3] - '0') * 10 + (it[4] - '0');
        nt.push_back(tmp);
    }

    sort(nt.begin(), nt.end());

    int pre = nt[0];
    int min = 24 * 60;
    for (int i = 1; i < nt.size(); ++i)
    {
        int tmp = nt[i] - pre;

        if (tmp > max)
        {
            tmp -= max;
        }
        if (tmp < min)
        {
            min = tmp;
        }

        pre = nt[i];
    }

    int tmp = nt[nt.size() - 1] - nt[0];
    if (tmp > max)
    {
        tmp -= max;
    }
    if (tmp < min)
    {
        min = tmp;
    }

    return min;
}

void threeSumClosest(vector<int>& nums, int target) 
{
    for (int i = 0; i < nums.size(); ++i)
    {
        nums[i] -= target;
    }

    sort(nums.begin(), nums.end());

    int index = 0;
    for (int i =0; i < nums.size(); ++i)
    {
        if (nums[i] >= 0)
        {
            index = i;
            break;
        }
    }

    int min = 0;

}

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

    findMinDifference({ "23:59","00:00" });
    TestBinaryTreeTraversal();
    return 1;
}