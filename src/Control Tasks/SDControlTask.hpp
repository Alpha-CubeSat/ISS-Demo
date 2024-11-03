#ifndef SD_CONTROL_TASK_HPP
#define SD_CONTROL_TASK_HPP

#include <Adafruit_ZeroDMA.h>
#include <SdFat.h>

class SDControlTask {
public:
    void begin();
    void execute();

private:
    Adafruit_ZeroDMA dma;
    DmacDescriptor* desc;
    SdFat SD;
    File file;
};

#endif