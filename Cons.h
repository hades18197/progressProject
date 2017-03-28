#ifndef CONS_H
#define CONS_H
#include <string.h>
#include <iostream>
using namespace std;

class Cons {
public:

// Files And Directories
    static char* DATA();
    static char* DICS();
    static char* UGLIST();
    static char* LGLIST();
    static char* CLIST();
    static char* LOGS();
    static char* UGLOGS();
    static char* LGLOGS();
    static char* CLOGS();
    static char* EXEC_LOG();
    static char* TMP_FILE();

// Numerical Values
    static int TYPE_UNLIMITED();
    static int TYPE_LIMITED();
    static int TYPE_COURSE();
    static int SCOPE_DAY();
    static int SCOPE_WEEK();
    static int COUNT_OFFLINE();
    static int COUNT_ONLINE();
    static int EVENT_INFO();
    static int EVENT_ERROR();
    static int OPTION_UPDATE();
    static int OPTION_DELETE();

};
#endif // CONS_H

