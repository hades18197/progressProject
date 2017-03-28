#ifndef FILECONTROL_H
#define FILECONTROL_H
#include <sys/stat.h>
#include <unistd.h>
#include <string>


class FileControl
{
public:
    FileControl();
    void checkAndCreate();
     inline bool fEx (char n[]) {return (access(n, F_OK) != -1);}
private:

};

#endif // FILECONTROL_H
