
#include "misc/single_limted.h"

#include "test_case_factory.h"

#include <iostream>

BEG_NSP_DDM

TEST(test_single_limted, auto_limted)
{
    {
        auto_limted limted;

        if (limted.hold_mutex(L"limted")) {
            std::cout << "holded" << std::endl;
        }

        if (!limted.hold_mutex(L"limted")) {
            std::cout << "not holded" << std::endl;
        }
    }

    {
        auto_limted limted;

        if (limted.hold_mutex(L"limted")) {
            std::cout << "holded" << std::endl;
        }

        if (!limted.hold_mutex(L"limted")) {
            std::cout << "not holded" << std::endl;
        }
    }
}
END_NSP_DDM
