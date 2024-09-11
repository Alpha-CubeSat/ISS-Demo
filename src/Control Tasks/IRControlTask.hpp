#ifndef IR_CONTROL_TASK_HPP
#define IR_CONTROL_TASK_HPP



class IRControlTask {
public:
    IRControlTask();
    void execute();

private:
    void parse_command();
    void handle_overflow();
};

#endif