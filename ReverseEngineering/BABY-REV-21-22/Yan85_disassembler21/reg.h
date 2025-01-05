struct reg {
    unsigned char a, b, c, d, s, i, f;
};

// Declare the variable as extern
extern struct reg registers;
int set_register(unsigned char reg, unsigned char value);
unsigned char describe_register(unsigned char);
unsigned char define_register(unsigned char reg);
int interpret_imm(unsigned char arg1, unsigned char arg2);
