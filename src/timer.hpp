

class Timer {
public:
    Timer() : start_time(0), duration(0), active(false) {}

    void start(unsigned long interval);

    bool is_elapsed();

    void reset();

private:
    unsigned long start_time;
    unsigned long duration;
    bool active;
};
