#ifndef SD_CONTROL_TASK_HPP
#define SD_CONTROL_TASK_HPP

#include <SD.h>

class SDControlTask {
public:
    void begin();
    void execute();
private:
    File file;
};

#endif