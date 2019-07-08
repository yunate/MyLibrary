
#include "string_utils_s.h"

namespace stringutils_s
{
    bool StrSplit(const TString& raw, TChar& spliter, std::vector<TString>& out)
    {
        TChar c = T('\0');
        TString line = T("");

        for (size_t i = 0; i < raw.length(); ++i)
        {
            c = raw[i];

            if (c == spliter)
            {
                out.push_back(line);
                line = T("");
            }
            else
            {
                line.append(1, c);
            }
        }

        out.push_back(line);
        return true;
    }
}
