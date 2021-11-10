// acc_test2

#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    int a = RAND_MAX / 2;
    for(int i=0;i<100;i++) {
        if (a < rand()){int i=1;}
        if (a < rand()){int i=1;}
        if (a < rand()){int i=1;}
        if (a < rand()){int i=1;}
        if (a < rand()){int i=1;}
        if (a < rand()){int i=1;}
    }
}