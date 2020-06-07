#pragma once
#include <vector>

using namespace std;

/* 
    ��״���飬������������������������
    �ο� : https://blog.csdn.net/qq_40938077/article/details/80424318
*/

namespace DogLib
{
    class LowBit
    {
    public:
        LowBit(vector<int> nRaw);
        ~LowBit();

    public:
        int GetSum(int nIndex);
        void Update(int nIndex, int nValue);

    private:
        int _Lowbit(int x);

    private:
        vector<int>        m_nC;
    };
}

