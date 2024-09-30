#ifndef IR_CONTROL_TASK_HPP
#define IR_CONTROL_TASK_HPP



class IRControlTask {
public:
    void begin();
    void execute();

private:
    void parse_command();
    void handle_overflow();

    int button_selected = -1;
};

#endif