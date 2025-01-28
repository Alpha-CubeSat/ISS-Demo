
#ifndef TIMER_HPP
#define TIMER_HPP

class Timer {
public:
    Timer() : start_time(0), duration(0), active(false) {}

    void start(unsigned long interval);

    bool is_elapsed();

    bool is_past(unsigned long interval);

    void reset();

private:
    unsigned long start_time;
    unsigned long duration;
    bool active;
};

#endif // TIMER_HPP