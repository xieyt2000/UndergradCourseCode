#ifndef TOOLS_H
#define TOOLS_H

#include <linux/io.h>

typedef struct {
    uint32_t set;
    uint32_t way;
    uint32_t flag;
    uint64_t tag;
    uint32_t data[16];
}msg_t;

/* Store 64bit value val to an address str
 * @str: the address to contain the value
 * @val: the 64bit value
 */
void ultostr(char* str, uint64_t val);

/* Store a msg_t struct to an address buf
 * @buf: the address to contain the value
 * @msg: the struct msg_t
 */
void msg_encode(char* buf, msg_t* msg);

/* Signed extern a data to 64bit
 * @input: the value
 * @highest_pos: the highest position of the input, for example, input = 0b1100, then hithest_pos = 3
 * @return: 64bit value that has been signed externed.
 */
uint64_t signed_extern(uint64_t input, int highest_pos);

#endif