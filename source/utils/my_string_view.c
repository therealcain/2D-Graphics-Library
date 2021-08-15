#include "utils/my_string_view.h"

#include <assert.h>

bool move_cstring_to_string_view(StringView* view, const char* str)
{
    assert(str);
    assert(view);

    view->len = strlen(str);
    view->str = str;
}

void move_length_cstring_to_string_view(StringView* view, const char* str, size_t len)
{
    assert(str);
    assert(view);

    view->str = str;
    view->len = len;
}
