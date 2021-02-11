
#include "test_case_factory.h"
#include "str/xfast_str.hpp"

BEG_NSP_DDM
TEST(test_xfast_str, trim)
{
    xfast_str fast_str1("f   ");
    fast_str1.trim();
    DD_ASSERT(fast_str1.length() == 1);

    xfast_str fast_str2("   f");
    fast_str2.trim();
    DD_ASSERT(fast_str2.length() == 1);

    xfast_str fast_str3("");
    fast_str3.trim();
    DD_ASSERT(fast_str3.length() == 0);

    xfast_str fast_str4(" f ");
    fast_str4.trim();
    DD_ASSERT(fast_str4.length() == 1);

    xfast_str fast_str5("  ");
    fast_str5.trim();
    DD_ASSERT(fast_str5.length() == 0);
}

TEST(test_xfast_str, beg_with)
{
    xfast_str fast_str("abc_def_ghi_jkl_mn");
    DD_ASSERT(fast_str.beg_with(""));
    DD_ASSERT(fast_str.beg_with("abc_"));
    DD_ASSERT(!fast_str.beg_with("abcd"));

    xfast_str fast_str1("");
    DD_ASSERT(!fast_str1.beg_with("abc_"));
    DD_ASSERT(fast_str1.beg_with(""));
}

TEST(test_xfast_str, end_with)
{
    xfast_str fast_str("abc_def_ghi_jkl_mn");
    DD_ASSERT(fast_str.end_with(""));
    DD_ASSERT(fast_str.end_with("mn"));
    DD_ASSERT(!fast_str.end_with("abcd"));

    xfast_str fast_str1("");
    DD_ASSERT(!fast_str1.end_with("abc_"));
    DD_ASSERT(fast_str1.end_with(""));
}

TEST(test_xfast_str, sub_str)
{
    {
        xfast_str fast_str("abc_def_ghi_jkl_mn");
        xfast_str sub = fast_str.sub_str(0, fast_str.length());
        DD_ASSERT(sub == fast_str);
    }

    {
        xfast_str fast_str("abc_def_ghi_jkl_mn");
        xfast_str sub = fast_str.sub_str(0);
        DD_ASSERT(sub == fast_str);
    }

    {
        xfast_str fast_str("abc_def_ghi_jkl_mn");
        xfast_str sub = fast_str.sub_str(fast_str.find("d"));
        DD_ASSERT(sub == "def_ghi_jkl_mn");
    }

    {
        xfast_str fast_str("abc_def_ghi_jkl_mn");
        xfast_str sub = fast_str.sub_str(fast_str.find("d"), 3);
        DD_ASSERT(sub == "def");
    }

    {
        xfast_str fast_str1("");
        xfast_str sub1 = fast_str1.sub_str(0, fast_str1.length());
        DD_ASSERT(sub1 == fast_str1);
    }
}

TEST(test_xfast_str, to_sub_str)
{
    {
        xfast_str fast_str("abc_def_ghi_jkl_mn");
        fast_str.to_sub_str(0, fast_str.length());
        xfast_str sub(fast_str);
        DD_ASSERT(sub == fast_str);
    }

    {
        xfast_str fast_str("abc_def_ghi_jkl_mn");
        fast_str.to_sub_str(0);
        xfast_str sub(fast_str);
        DD_ASSERT(sub == fast_str);
    }

    {
        xfast_str fast_str("abc_def_ghi_jkl_mn");
        fast_str.to_sub_str(fast_str.find("d"));
        xfast_str sub(fast_str);
        DD_ASSERT(sub == "def_ghi_jkl_mn");
    }

    {
        xfast_str fast_str("abc_def_ghi_jkl_mn");
        fast_str.to_sub_str(fast_str.find("d"), 3);
        xfast_str sub(fast_str);
        DD_ASSERT(sub == "def");
    }

    {
        xfast_str fast_str1("");
        fast_str1.to_sub_str(0, fast_str1.length());
        xfast_str sub1(fast_str1);
        DD_ASSERT(sub1 == fast_str1);
    }
}

TEST(test_xfast_str, find)
{
    {
        xfast_str fast_str("abc_def_ghi_jkl_mn");
        DD_ASSERT(fast_str.find('a') == 0);
        DD_ASSERT(fast_str.find("a") == 0);
        DD_ASSERT(fast_str.find('n') == fast_str.length() - 1);
        DD_ASSERT(fast_str.find("n") == fast_str.length() - 1);
        DD_ASSERT(fast_str.find("abc") == 0);
        DD_ASSERT(fast_str.find("mn") == fast_str.length() - 2);
        DD_ASSERT(fast_str.find("abc_def_ghi_jkl_mn") == 0);
        DD_ASSERT(fast_str.find("") == 0);
        DD_ASSERT(fast_str.find("ff") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find("abc_def_ghi_jkl_mnff") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find('x') == xfast_str::xnpos);
    }

    {
        xfast_str fast_str("");
        DD_ASSERT(fast_str.find('a') == xfast_str::xnpos);
        DD_ASSERT(fast_str.find("a") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find('n') == xfast_str::xnpos);
        DD_ASSERT(fast_str.find("n") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find("abc") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find("mn") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find("abc_def_ghi_jkl_mn") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find("") == 0);
        DD_ASSERT(fast_str.find("ff") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find("abc_def_ghi_jkl_mnff") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find('x') == xfast_str::xnpos);
    }
}

TEST(test_xfast_str, find_last_of)
{
    {
        xfast_str fast_str("abc_def_ghi_jkl_mn");
        DD_ASSERT(fast_str.find_last_of('a') == 0);
        DD_ASSERT(fast_str.find_last_of("a") == 0);
        DD_ASSERT(fast_str.find_last_of('n') == fast_str.length() - 1);
        DD_ASSERT(fast_str.find_last_of("n") == fast_str.length() - 1);
        DD_ASSERT(fast_str.find_last_of("abc") == 0);
        DD_ASSERT(fast_str.find_last_of("mn") == fast_str.length() - 2);
        DD_ASSERT(fast_str.find_last_of("abc_def_ghi_jkl_mn") == 0);
        DD_ASSERT(fast_str.find_last_of("") == 0);
        DD_ASSERT(fast_str.find_last_of("ff") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find_last_of("abc_def_ghi_jkl_mnff") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find_last_of('x') == xfast_str::xnpos);
    }

    {
        xfast_str fast_str("");
        DD_ASSERT(fast_str.find_last_of('a') == xfast_str::xnpos);
        DD_ASSERT(fast_str.find_last_of("a") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find_last_of('n') == xfast_str::xnpos);
        DD_ASSERT(fast_str.find_last_of("n") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find_last_of("abc") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find_last_of("mn") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find_last_of("abc_def_ghi_jkl_mn") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find_last_of("") == 0);
        DD_ASSERT(fast_str.find_last_of("ff") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find_last_of("abc_def_ghi_jkl_mnff") == xfast_str::xnpos);
        DD_ASSERT(fast_str.find_last_of('x') == xfast_str::xnpos);
    }
}

TEST(test_xfast_str, split)
{
    {
        std::vector<xfast_str> out;
        xfast_str fast_str("abc_def_ghi_jkl_mn");
        fast_str.split("_", out);
        DD_ASSERT(out.size() == 5);

        out.clear();
        fast_str.split("__", out);
        DD_ASSERT(out.size() == 1);

        out.clear();
        fast_str.split("abc_def_ghi_jkl_mn", out);
        DD_ASSERT(out.size() == 2);

        out.clear();
        fast_str.split("abc_def_ghi_jkl_mnd", out);
        DD_ASSERT(out.size() == 1);
    }

    {
        std::vector<xfast_str> out;
        xfast_str fast_str("");
        fast_str.split("_", out);
        DD_ASSERT(out.size() == 1);

        out.clear();
        fast_str.split("__", out);
        DD_ASSERT(out.size() == 1);

        out.clear();
        fast_str.split("abc_def_ghi_jkl_mn", out);
        DD_ASSERT(out.size() == 1);

        out.clear();
        fast_str.split("abc_def_ghi_jkl_mnd", out);
        DD_ASSERT(out.size() == 1);
    }
}

END_NSP_DDM
