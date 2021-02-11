
#include "test_case_factory.h"
#include "str/xfast_str.hpp"

BEG_NSP_DDM

TEST(test_xfast_str, xfast_str)
{
    xfast_str fast_str("abc_def_ghi_jkl_mn");
    xfast_str fast_str1("abc_def_ghi_jkl_mn_o");
    size_t len = fast_str.length(); // 18
    ddstra str = fast_str.to_str();
    bool b = fast_str == fast_str1; // false
    b = fast_str == str; // true
    b = fast_str.beg_with("abc"); // true
    b = fast_str.beg_with("abcd"); // false
    b = fast_str.end_with("mn"); // true
    b = fast_str.end_with("mno"); // false
    size_t pos = fast_str.find("defd"); // xnpos
    pos = fast_str.find("def_"); // 4
    pos = fast_str.find_last_of("def_"); // 4
    xfast_str fast_str2 = fast_str.sub_str(pos);
    str = fast_str2.to_str(); // def_ghi_jkl_mn
    std::vector<xfast_str> split_out;
    fast_str.split("_", split_out);// abc def ghi jkl mn
    xfast_str fast_str3("  abc  _def_ghi_jkl_mn  ");
    fast_str3.trim();
    str = fast_str3.to_str(); //
    xfast_str fast_str4("");
    fast_str4.trim();
    str = fast_str4.to_str(); //

}

END_NSP_DDM
