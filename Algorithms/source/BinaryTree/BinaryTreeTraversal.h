
#ifndef __BinaryTreeTraversal_H_
#define __BinaryTreeTraversal_H_

#include <stack>
#include <queue>
#include <vector>

template<class ty>
struct BinaryTreeNode
{
    BinaryTreeNode<ty>* m_l = nullptr;
    BinaryTreeNode<ty>* m_r = nullptr;
    ty m_v {};
};

/** ����������
*/
class BinaryTreeTraversal
{
private:
    /** ���ɶ��������ݹ飬�ú�����һ�����⣬��Ҫ�����в������ظ������ǿ�������һ����
    @param [in] mTraversal ����������
    @param [in] bTraversal ǰ��������
    @return ����ָ�룬ʧ�ܷ��ؿ�
    */
    template<class ty>
    static BinaryTreeNode<ty>* NewTree_Core(const std::vector<ty>& mTraversal, int lIndex,
                                 const std::vector<ty>& bTraversal, int mIndex,
                                 int len)
    {
        for (int i = 0; i < len; ++i)
        {
            if (mTraversal[i + lIndex] == bTraversal[mIndex])
            {
                BinaryTreeNode<ty>* pRoot = new BinaryTreeNode<ty>();
                pRoot->m_v = bTraversal[mIndex];
                pRoot->m_l = NewTree_Core(mTraversal, lIndex, bTraversal, mIndex + 1, i);
                pRoot->m_r = NewTree_Core(mTraversal, lIndex + i + 1, bTraversal, mIndex + i + 1, len - i - 1);
                return pRoot;
            }
        }

        return nullptr;
    }

    /** ���ɶ����������õݹ飬�ú�����һ�����⣬��Ҫ�����в������ظ������ǿ�������һ����
    @param [in] mTraversal ����������
    @param [in] bTraversal ǰ��������
    @return ����ָ�룬ʧ�ܷ��ؿ�
    */
    template<class ty>
    static BinaryTreeNode<ty>* NewTree_Core_Stack(const std::vector<ty>& mTraversal,
                                       const std::vector<ty>& bTraversal)
    {
        struct BinaryTreeNodeTmp
        {
            BinaryTreeNode<ty>* m_root;
            int m_lIndex;
            int m_mIndex;
            int m_len;
        };

        BinaryTreeNode<ty>* pRoot = new BinaryTreeNode<ty>();
        pRoot->m_v = bTraversal[0];
        std::stack<BinaryTreeNodeTmp*> stack;
        stack.push(new BinaryTreeNodeTmp{ pRoot, 0, 0, (int)mTraversal.size() });

        while (!stack.empty())
        {
            BinaryTreeNodeTmp* tmp = stack.top();
            stack.pop();

            for (int i = 0; i < tmp->m_len; ++i)
            {
                if (bTraversal[tmp->m_mIndex] == mTraversal[(size_t)i + tmp->m_lIndex])
                {
                    if (tmp->m_len - i - 1 != 0)
                    {
                        tmp->m_root->m_r = new BinaryTreeNode<ty>();
                        stack.push(new BinaryTreeNodeTmp{ tmp->m_root->m_r, tmp->m_lIndex + i + 1, tmp->m_mIndex + i + 1, tmp->m_len - i - 1 });
                        tmp->m_root->m_r->m_v = bTraversal[(size_t)tmp->m_mIndex + i + 1];
                    }

                    if (i != 0)
                    {
                        tmp->m_root->m_l = new BinaryTreeNode<ty>();
                        stack.push(new BinaryTreeNodeTmp{ tmp->m_root->m_l, tmp->m_lIndex, tmp->m_mIndex + 1, i });
                        tmp->m_root->m_l->m_v = bTraversal[(size_t)tmp->m_mIndex + 1];
                    }

                    break;
                }
            }

            delete tmp;
        }

        return pRoot;
    }

public:
    /** ���ɶ��������ú�����һ�����⣬��Ҫ�����в������ظ������ǿ�������һ����
    @param [in] mTraversal ����������
    @param [in] bTraversal ǰ��������
    @return ����ָ�룬ʧ�ܷ��ؿ�
    */
    template<class ty>
    static BinaryTreeNode<ty>* NewTree(const std::vector<ty>& mTraversal, const std::vector<ty>& bTraversal)
    {
        if (mTraversal.size() == 0 || mTraversal.size() != bTraversal.size())
        {
            return nullptr;
        }

        return NewTree_Core_Stack(mTraversal, bTraversal);
        //return NewTree_Core(leftTraversal, 0, midTraversal, 0, leftTraversal.size());
    }

    /** ɾ����������������
    @param [in] root ����
    */
    template<class ty>
    static void DeleteTree(BinaryTreeNode<ty>* root)
    {
        std::queue<BinaryTreeNode<ty>*> que;
        que.push(root);

        while (!que.empty())
        {
            BinaryTreeNode<ty>* tmp = que.front();
            que.pop();

            if (tmp == nullptr)
            {
                continue;
            }

            que.push(tmp->m_l);
            que.push(tmp->m_r);
            delete tmp;
        }
    }

    /** ��ȱ��������������õݹ�
    @param [in] root ����
    @return ����ǰ���������
    */
    template<class ty>
    static std::vector<ty> DeapFirstTraversal_b(BinaryTreeNode<ty>* root)
    {
        std::vector<ty> rtn;
        std::stack<BinaryTreeNode<ty>*> stack;
        stack.push(root);

        while (!stack.empty())
        {
            BinaryTreeNode<ty>* tmp = stack.top();
            stack.pop();

            if (tmp == nullptr)
            {
                continue;
            }

            rtn.push_back(tmp->m_v);
            stack.push(tmp->m_r);
            stack.push(tmp->m_l);
        }
        return rtn;
    }

    /** ��ȱ��������������õݹ�
    @param [in] root ����
    @return ���������������
    */
    template<class ty>
    static std::vector<ty> DeapFirstTraversal_m(BinaryTreeNode<ty>* root)
    {
        std::vector<ty> rtn;
        std::stack<BinaryTreeNode<ty>*> stack;
        BinaryTreeNode<ty>* tmp = root;

        while (!stack.empty() || tmp != nullptr)
        {
            if (tmp != nullptr)
            {
                stack.push(tmp);
                tmp = tmp->m_l;
            }
            else
            {
                tmp = stack.top();
                stack.pop();
                rtn.push_back(tmp->m_v);

                if (tmp->m_r != nullptr)
                {
                    tmp = tmp->m_r;
                }
                else
                {
                    tmp = nullptr;
                }
            }
        }
        return rtn;
    }

    /** ��ȱ��������������õݹ�
    @param [in] root ����
    @return ���غ����������
    */
    template<class ty>
    static std::vector<ty> DeapFirstTraversal_a(BinaryTreeNode<ty>* root)
    {
        std::vector<ty> rtn;
        BinaryTreeNode<ty>* preRtn = nullptr;
        std::stack<BinaryTreeNode<ty>*> stack;
        BinaryTreeNode<ty>* tmp = root;

        while (!stack.empty() || tmp != nullptr)
        {
            if (tmp != nullptr)
            {
                stack.push(tmp);
                tmp = tmp->m_l;
            }
            else
            {
                tmp = stack.top();

                if (tmp->m_r != nullptr && preRtn != tmp->m_r)
                {
                    tmp = tmp->m_r;
                }
                else
                {
                    stack.pop();
                    rtn.push_back(tmp->m_v);
                    preRtn = tmp;
                    tmp = nullptr;
                }
            }
        }
        return rtn;
    }

    /** ��ȶȱ��������������õݹ�
    @param [in] root ����
    @return ���ع�ȱ������
    */
    template<class ty>
    static std::vector<ty> BreadFirstTraversal(BinaryTreeNode<ty>* root)
    {
        std::vector<ty> rtn;
        std::queue<BinaryTreeNode<ty>*> que;
        que.push(root);

        while (!que.empty())
        {
            BinaryTreeNode<ty>* tmp = que.front();
            que.pop();

            if (tmp == nullptr)
            {
                continue;
            }

            rtn.push_back(tmp->m_v);
            que.push(tmp->m_l);
            que.push(tmp->m_r);
        }

        return rtn;
    }
};

void TestBinaryTreeTraversal()
{
    std::vector<int> mT{ 4,2,5,1,6,3,7 };
    std::vector<int> bT{ 1,2,4,5,3,6,7 };
    BinaryTreeNode<int>* pRoot = BinaryTreeTraversal::NewTree<int>(mT, bT);
    std::vector<int> breadFirst = BinaryTreeTraversal::BreadFirstTraversal<int>(pRoot);
    std::vector<int> mFirst = BinaryTreeTraversal::DeapFirstTraversal_m<int>(pRoot);
    std::vector<int> bFirst = BinaryTreeTraversal::DeapFirstTraversal_b<int>(pRoot);
    std::vector<int> aFirst = BinaryTreeTraversal::DeapFirstTraversal_a<int>(pRoot);
    BinaryTreeTraversal::DeleteTree<int>(pRoot);
}

#endif //__BinaryTreeTraversal_H_
