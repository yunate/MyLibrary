
#ifndef __CONSUMER_H_
#define __CONSUMER_H_
#include "IGoods.h"

/** 消费者接口
*/
class IConsumer
{
public:
    /** 消费一个商品，消费完以后负责释放这个商品
    @param [in] goods 商品指针
    @return 是否成功
    */
    virtual bool Consumer(IGoods* goods) = 0;
    virtual ~IConsumer() {}
};

#endif // __CONSUMER_H_



