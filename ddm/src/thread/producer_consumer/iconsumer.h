
#ifndef iconsumer_h_
#define iconsumer_h_ 1
#include "base/g_def.h"
#include "igoods.h"
BEG_NSP_DDM
/** �����߽ӿ�
*/
class iconsumer
{
public:
    /** ����һ����Ʒ���������Ժ����ͷ������Ʒ
    @param [in] goods ��Ʒָ��
    @return �Ƿ�ɹ�
    */
    virtual bool consumer(igoods* goods) = 0;
    virtual ~iconsumer() {}
};

END_NSP_DDM
#endif // iconsumer_h_



