/*
  Пример за логващи функции и клас.
  Припомня условна компилация и демонстрира RAII
  Част от курса ООП, ФМИ, 2024.
*/

#ifndef __LOGER_HEADER_INCLUDED_
#define __LOGER_HEADER_INCLUDED_

#if defined(_DEBUG) || defined(LOG_ENABLED)

#   include <cstdio>

#   define AutoLog AutoLogger __al(__FUNCTION__);
#   define LogIn(TEXT) printf(">> In >> %s. %s\n", __FUNCTION__, TEXT);
#   define LogOut(TEXT) printf("<< Out << %s. %s\n", __FUNCTION__, TEXT);
#   define Log(S, ...) {printf(S, __VA_ARGS__); puts("");}

#else

#   define AutoLog
#   define LogIn(TEXT)
#   define LogOut(TEXT)
#   define Log(...)

#endif  //defined(_DEBUG) || defined(LOG_ENABLED)

#if defined(_DEBUG) || defined(LOG_ENABLED)

class AutoLogger
{
public:
    AutoLogger(const char* fun):fun(fun) { LogIn(fun); }
    ~AutoLogger(){ LogOut(fun); }
protected:
    const char* fun;
};

#endif //defined(_DEBUG) || defined(LOG_ENABLED)

#endif //__LOGER_HEADER_INCLUDED_


