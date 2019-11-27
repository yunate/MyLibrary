
#ifndef __DOGREGEX_H_
#define __DOGREGEX_H_

//////////////////////////////////////////////////////////////////////////
//                         一些常用的正则表达式                             //
//                         仅供参考！！！                                  //
//////////////////////////////////////////////////////////////////////////

#include "typedef/DogString.h"

/** 数字：
*/
static const DogChar* s_regex_number = _DogT(R"([0-9]*)");

/** n位的数字
*/
static const DogChar* s_regex_n_number = _DogT(R"(\d{n})");

/** 至少n位的数字
*/
static const DogChar* s_regex_np_number = _DogT(R"(\d{n,})");

/** m-n位的数字：
*/
static const DogChar* s_regex_nm_number = _DogT(R"(\d{n,m})");

/** 零开头的数字
*/
static const DogChar* s_regex_0_number = _DogT(R"((0[0-9]*))");

/** 非零开头的数字
*/
static const DogChar* s_regex_n0_number = _DogT(R"(([1-9][0-9]*))");

/** 非零开头的最多带m位小数的数字
*/
static const DogChar* s_regex_n0_mdcml_number = _DogT(R"(([1-9][0-9]*)+(\.[0-9]{1,m})?)");

/** 最多带m位小数的负数
*/
static const DogChar* s_regex_nativ_mdcml_number = _DogT(R"((\-)?\d+(\.\d{1,m})?)");

/** 有理数
*/
static const DogChar* s_regex_q_number = _DogT(R"((\-|\+)?\d+(\.\d+)?)");

/** 汉字
*/
static const DogChar* s_regex_chinese = _DogT(R"([\u4e00-\u9fa5]+)");

/** 英文和数字
*/
static const DogChar* s_regex_comm_char = _DogT(R"([A-Za-z0-9]+)");

/** Email地址：?
*/
static const DogChar* s_regex_email = _DogT(R"([a-zA-Z0-9_-]+@[a-zA-Z0-9_-]+(\.[a-zA-Z0-9_-]+)+)");

/** 域名：?
*/
static const DogChar* s_regex_domain_name = _DogT(R"(\w+(\.\w)+)";

#endif //__DOGREGEX_H_
