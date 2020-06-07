#include "LowBit.h"
using namespace std;
using namespace DogLib;

LowBit::LowBit(vector<int> nRaw)
{
    m_nC = vector<int>(nRaw.size());

    for (unsigned int i = 0; i < nRaw.size(); ++i)
    {
        Update(i, nRaw[i]);
    }
}

LowBit::~LowBit()
{
}

int DogLib::LowBit::_Lowbit(int nX)
{
    return (int)nX&(-1 * nX);
}

int LowBit::GetSum(int nIndex)
{
    int nSum = 0;

    for (unsigned int i = nIndex; i > 0; i -= _Lowbit(i))
    {
        nSum += m_nC[i];
    }

    return nSum;
}

void LowBit::Update(int nIndex, int nValue)
{
    for (unsigned int i = nIndex; i < m_nC.size(); i += _Lowbit(i))
    {
        m_nC[i] += nValue;
    }
}


