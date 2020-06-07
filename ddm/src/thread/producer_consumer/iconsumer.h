
#ifndef iconsumer_h_
#define iconsumer_h_ 1
#include "base/g_def.h"
#include "igoods.h"
BEG_NSP_DDM
/** 消费者接口
*/
class iconsumer
{
public:
    /** 消费一个商品，消费完以后负责释放这个商品
    @param [in] goods 商品指针
    @return 是否成功
    */
    virtual bool consumer(igoods* goods) = 0;
    virtual ~iconsumer() {}
};

END_NSP_DDM
#endif // iconsumer_h_



