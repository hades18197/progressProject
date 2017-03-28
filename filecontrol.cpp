#include "filecontrol.h"
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <direct.h>
#include <string.h>
#include <string>
#include "lav.h"
#include "Cons.h"
using namespace std;

FileControl::FileControl()
{

}

void FileControl::checkAndCreate() {
    LAV lav;
    char *all [] = {Cons::DATA(),Cons::DICS(),Cons::UGLIST(),Cons::LGLIST(),
                    Cons::CLIST(),Cons::LOGS(),Cons::UGLOGS(),Cons::LGLOGS(),Cons::CLOGS(),
                    Cons::EXEC_LOG()}; // 0 - 9
    ofstream f;
    DIR* dir = opendir(all[0]);
    for(int i = 0; i < 10; i++) {
        char* ptr = strchr(all[i],'.');
        if((ptr - all[i]) < strlen(all[i]) && (ptr - all[i]) >= 0 ) {
            if(!fEx(all[i])) {
                f.open(all[i]);
                f.close();
                string stat = "created ";
                stat += all[i];
                lav.logEvent(stat,Cons::EVENT_INFO());
            }
        }
        else {
            dir = opendir(all[i]);
            if(dir){}
            else {
                mkdir(all[i]);
                string stat = "created ";
                stat += all[i];
                lav.logEvent(stat,Cons::EVENT_INFO());
            }
        }
    }

}
