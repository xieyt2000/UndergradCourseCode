#include "tools.h"

void ultostr(char* str, uint64_t val) {
    int i;
    for (i = 0; i < 8; ++ i) {
        str[i] = val & 0xff;
        val = val >> 8;
    }
}

void msg_encode(char* buf, msg_t* msg) {
    int i;
    ultostr(buf, msg->set);
    ultostr(buf + 8, msg->way);
    ultostr(buf + 16, msg->flag);
    ultostr(buf + 24, msg->tag);

    for(i = 0; i < 16; i++) {
        ultostr(buf + 32 + i*8, msg->data[i]);
    }
    // total: 160B
}

uint64_t signed_extern(uint64_t input, int highest_pos) {
    int sbit = (input >> highest_pos) & 1;
    if(sbit == 0)  // positive
        return input;
    else {  // nagetive
        uint64_t x = -1;
        return input + (x << (highest_pos + 1));
    }
}