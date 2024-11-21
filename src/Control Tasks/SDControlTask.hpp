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
    uint8_t file_count = 0;
};

#endif