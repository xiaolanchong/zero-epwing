#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <locale.h>
#include <Windows.h>

/*
 * Exported functions
 */

char* eucjp_to_utf8(const char src[]) {
    const unsigned int EUC_JP_CP = 20932;
    int strLen = (int)strlen(src);
    const int allocCharsForWideCharStr = MultiByteToWideChar(EUC_JP_CP, MB_ERR_INVALID_CHARS, src, strLen,
       NULL, 0);
    wchar_t* wideStr = (wchar_t*)malloc(sizeof(wchar_t) * (allocCharsForWideCharStr + 1));
    if (wideStr == NULL)
       return NULL;
    int result = MultiByteToWideChar(EUC_JP_CP, MB_ERR_INVALID_CHARS, src, strLen, 
       wideStr, allocCharsForWideCharStr);
    assert(result > 0);
    if (result <= 0)
       return NULL;
    assert(result == allocCharsForWideCharStr);

    const int allocateForUtf8 = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, wideStr, allocCharsForWideCharStr,
       NULL, 0, NULL, NULL);

    char* utf8Str = (char*)malloc(allocateForUtf8 + 1);
    if (utf8Str == NULL)
    {
       free(wideStr);
       return NULL;
    }
    result = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, wideStr, result,
       utf8Str, allocateForUtf8, NULL, NULL);
    assert(result > 0);
    free(wideStr);
    if (result <= 0)
       return NULL;
    assert(result == allocateForUtf8);
    utf8Str[allocateForUtf8] = '\0';
    return utf8Str;
}
