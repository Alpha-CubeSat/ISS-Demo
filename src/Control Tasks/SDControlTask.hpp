#ifndef SD_CONTROL_TASK_HPP
#define SD_CONTROL_TASK_HPP

#include <SD.h>

class SDControlTask {
public:
    void begin();
    void execute();

private:
    String name;
    File file;
    int file_count;
};

#endif