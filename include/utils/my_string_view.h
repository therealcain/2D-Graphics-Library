#ifndef MY_STRING_VIEW_H
#define MY_STRING_VIEW_H

#include "my_inttypes.h"

typedef struct {
    const char* str;
    size_t len;
} StringView;

#ifdef __cplusplus
extern "C" {
#endif

/* Moving the string into the viewer. */
extern bool move_cstring_to_string_view(StringView* view, const char* str);

/* Moving string and a known length into the viewer. */
extern void move_length_cstring_to_string_view(StringView* view, const char* str, size_t len);

#ifdef __cplusplus
}
#endif

#endif /* MY_STRING_VIEW_H */
