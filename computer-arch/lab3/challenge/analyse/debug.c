#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#define device_name "/dev/test"
#define MSG_BUFFER_LEN 3000000                 // 设备内容的最大长度

typedef struct {
    uint32_t set;
    uint32_t way;
    uint32_t flag;
    uint64_t tag;
    uint32_t data[16];
}msg_t;


msg_t msg;

uint64_t _strtoul(char* str) {
    uint64_t res = 0;
    for (int i = 0; i < 8; ++ i) {
        res += (uint64_t) str[i] << (i << 3);
    }
    return res;
}

int main () {
    int fd = open(device_name, O_RDONLY);
    if (fd < 0) {
        printf("cannot open the file\n");
        return -1;
    }
    char buf[MSG_BUFFER_LEN];
    int tot = 128 * 4;
    int byte_size = 160;
    read(fd, buf, tot * byte_size);
    uint32_t set, way, flag;
    uint64_t tag;
    uint32_t data;
    for(int i = 0; i < tot; ++ i) {
        int offset = byte_size * i;
        set = (uint32_t) _strtoul(buf + offset);
        way = (uint32_t) _strtoul(buf + offset + 8);
        flag = (uint32_t) _strtoul(buf + offset + 16);
        tag = _strtoul(buf + offset + 24);
        printf("0x%x\t0x%x\t0x%x\t0x%lx", set, way, flag, tag);
        for(int j = 0; j < 16; ++ j) {
            data = _strtoul(buf + offset + 32 + j * 8);
            printf("\t0x%x", data);
        }
        printf("\n");
    }

    return 0;
}