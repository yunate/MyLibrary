
#ifndef iproducer_h_
#define iproducer_h_ 1
#include "base/g_def.h"
#include "igoods.h"
#include <functional>
BEG_NSP_DDM
/** �����߽ӿ�
*/
class iproducer
{
public:
    /** ����һ����Ʒ
    @param [in] functional 
    */
    virtual void product(std::function<void(igoods*)>) = 0;
    virtual ~iproducer() {}
};
END_NSP_DDM
#endif // iproducer_h_
