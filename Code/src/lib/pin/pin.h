
#ifndef Pin_H
#define Pin_H

class Mcp23s17;

enum class Parent_type {
    MCP23S17,
    RP2040,
    PCA9635,
    MCP3008,
    MTCH105
};

enum class Pin_mode {
    INPUT,      // 1
    OUTPUT      // 0
};

enum class Interrupt_mode { // mcp23s17 interrups only
    DISABLED,
    CHANGE_LAST,
    CHANGE_DEFAULT
};


class Pin {
    private:
        const int index;
        const Parent_type parent_type;
        Mcp23s17 *parent = nullptr;

        bool value = 0;
        bool default_value = 0;

        Interrupt_mode interrupt_mode = Interrupt_mode::DISABLED;

    public:
        Pin(int index = 0, Parent_type parent_type = Parent_type::MCP23S17, Mcp23s17 *parent = nullptr);
        bool set(bool value);
        bool get();
        
        bool set_default_value(bool value);

        Interrupt_mode get_interrupt_mode();
        Interrupt_mode set_interrupt_mode(Interrupt_mode interrupt_mode);
};


#endif // Pin_H