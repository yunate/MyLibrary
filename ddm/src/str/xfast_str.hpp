
#ifndef xfast_str_basic_h__
#define xfast_str_basic_h__

#include "base/g_def.h"

BEG_NSP_DDM

template <class t>
class xfast_str_basic {
public:
    using t_str = std::basic_string<t>;
    using t_size = typename t_str::size_type;
    static constexpr auto xnpos = t_str::npos;

public:
    xfast_str_basic(const t* buff) : m_buff(buff), m_l_pos(0)
    {
        DD_ASSERT(buff != nullptr);
        t_str tmp(m_buff);
        m_r_pos = tmp.length();
    }

    xfast_str_basic(const t_str& str) :
        m_buff(str.c_str()), m_l_pos(0), m_r_pos(str.length()) { }

    xfast_str_basic(const t* buff, t_size len) :
        m_buff(buff), m_l_pos(0), m_r_pos(len) 
    {
        DD_ASSERT(buff != nullptr);
    }

    xfast_str_basic(const t* buff, t_size l, t_size r) :
        m_buff(buff), m_l_pos(l), m_r_pos(r)
    {
        DD_ASSERT(buff != nullptr);
        DD_ASSERT(l <= r);
    }

    inline const t* data() const
    {
        return m_buff;
    }

    inline t_size length() const
    {
        return m_r_pos - m_l_pos;
    }

    inline t operator[](t_size index) const
    {
        DD_ASSERT(index < length());
        return m_buff[m_l_pos + index];
    }

    inline bool operator==(const xfast_str_basic& r) const
    {
        if (length() != r.length()) {
            return false;
        }

        for (t_size i = 0; i < length(); ++i) {
            if ((*this)[i] != r[i]) {
                return false;
            }
        }

        return true;
    }

    inline bool operator==(const t_str& r) const
    {
        if (length() != r.length()) {
            return false;
        }

        for (t_size i = 0; i < length(); ++i) {
            if ((*this)[i] != r[i]) {
                return false;
            }
        }

        return true;
    }

public:
    t_str to_str() const
    {
        return t_str(m_buff + m_l_pos, m_buff + m_r_pos);
    }

    const t* c_str() const
    {
        return m_buff + m_l_pos;
    }

    bool beg_with(const xfast_str_basic& cmp) const
    {
        if (length() < cmp.length()) {
            return false;
        }

        for (t_size i = 0; i < cmp.length(); ++i) {
            if ((*this)[i] != cmp[i]) {
                return false;
            }
        }

        return true;
    }

    bool end_with(const xfast_str_basic& cmp) const
    {
        if (length() < cmp.length()) {
            return false;
        }

        for (t_size i = 0; i < cmp.length(); ++i) {
            if (m_buff[i + length() - cmp.length()] != cmp[i]) {
                return false;
            }
        }

        return true;
    }

    xfast_str_basic sub_str(t_size l, t_size len = xnpos) const
    {
        DD_ASSERT(l < length());
        if (len == xnpos) {
            return xfast_str_basic(m_buff, m_l_pos + l, m_r_pos);
        } else {
            DD_ASSERT(l + len < m_r_pos);
            return xfast_str_basic(m_buff, m_l_pos + l, m_l_pos + l + len);
        }
    }

    void to_sub_str(t_size l, t_size len = xnpos)
    {
        DD_ASSERT(l < length());
        m_l_pos += l;
        if (len != xnpos) {
            DD_ASSERT(l + len < m_r_pos);
            m_r_pos = m_l_pos + len;
        }
    }

    t_size find(t c) const
    {
        for (t_size i = 0; i < length(); ++i) {
            if ((*this)[i] == c) {
                return i;
            }
        }

        return xnpos;
    }

    t_size find(const xfast_str_basic& cmp) const
    {
        if (cmp.length() == 0) {
            return 0;
        }

        if (cmp.length() > length()) {
            return xnpos;
        }

        for (t_size i = 0; i < length(); ++i) {
            if ((*this)[i] != cmp[0]) {
                continue;
            }

            if (sub_str(i).beg_with(cmp)) {
                return i;
            }
        }

        return xnpos;
    }

    t_size find_last_of(t c) const
    {
        for (t_size i = length(); i > 0; --i) {
            if ((*this)[i - 1] == c) {
                return i - 1;
            }
        }

        return xnpos;
    }

    t_size find_last_of(const xfast_str_basic& cmp) const
    {
        if (cmp.length() == 0) {
            return 0;
        }

        if (cmp.length() > length()) {
            return xnpos;
        }

        for (t_size i = length() - cmp.length() + 1; i > 0; --i) {
            if ((*this)[i - 1] != cmp[0]) {
                continue;
            }

            if (sub_str(i - 1).beg_with(cmp)) {
                return i - 1;
            }
        }

        return xnpos;
    }

    void trim()
    {
        for (t_size i = m_l_pos; i < m_r_pos; ++i) {
            if (m_buff[i] != ' ') {
                break;
            }

            ++m_l_pos;
        }

        for (t_size i = m_r_pos - 1; i > m_l_pos; --i) {
            if (m_buff[i] != ' ') {
                break;
            }
            --m_r_pos;
        }
    }

    void split(const xfast_str_basic& cmp, std::vector<xfast_str_basic>& out) const
    {
        DD_ASSERT(cmp.length() > 0);
        xfast_str_basic src(*this);
        t_size pos = src.find(cmp);
        while (pos != xnpos)
        {
            out.emplace_back(src.sub_str(0, pos));
            src.to_sub_str(pos + cmp.length());
            pos = src.find(cmp);
        }

        out.emplace_back(src);
    }

private:
    const t* m_buff;
    t_size m_l_pos = 0; // °üº¬
    t_size m_r_pos = 0; // ²»°üº¬
};

using xfast_str = xfast_str_basic<char>;
using wxfast_str = xfast_str_basic<wchar_t>;
END_NSP_DDM
#endif
