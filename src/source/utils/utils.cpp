#include "../../include/utils/utils.hpp"

START_NAMESPACE

void abort_null(void* ptr, const std::string& str)
{
    if(ptr == nullptr)
    {
        std::cout << str << std::endl;
        abort();
    }
}

END_NAMESPACE