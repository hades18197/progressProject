#include "Cons.h"
char* Cons::DATA() {return "data";}
char* Cons::DICS() {return "data\\dictionaries";}
char* Cons::UGLIST() {return "data\\dictionaries\\unLimitedGoalsList.ulgpf";}
char* Cons::LGLIST() {return "data\\dictionaries\\limitedGoalsList.lgpf";}
char* Cons::CLIST() {return "data\\dictionaries\\coursesList.cpf";}
char* Cons::LOGS() {return "data\\logs";}
char* Cons::UGLOGS() {return "data\\logs\\UG";}
char* Cons::LGLOGS() {return "data\\logs\\LG";}
char* Cons::CLOGS() {return "data\\logs\\C";}
char* Cons::EXEC_LOG() {return "data\\logs\\execution.logpf";}
char* Cons::TMP_FILE() {return "data\\~tmpfile";}


int Cons::TYPE_UNLIMITED() {return 0;}
int Cons::TYPE_LIMITED() {return 1;}
int Cons::TYPE_COURSE() {return 2;}
int Cons::SCOPE_DAY() {return 1;}
int Cons::SCOPE_WEEK() {return 7;}
int Cons::COUNT_OFFLINE() {return 1;}
int Cons::COUNT_ONLINE() {return 0;}
int Cons::EVENT_INFO() {return 0;}
int Cons::EVENT_ERROR() {return 1;}
int Cons::OPTION_UPDATE() {return 0;}
int Cons::OPTION_DELETE() {return 1;}
