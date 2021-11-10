// spectre test
unsigned target_size = 100;
uint8_t target[200]; // [0, 100) can be accessed by user. [100, 200) should be guarded.
unsigned training_x = 0, malicious_x = 150;

void init()
{
    for (int i = 0; i < 200; i++)
    {
        target[i] = i;
    }
    int a = 0;
}

// user function to give the index of x
int x_interface(int j)
{
    for (int _ = 0; _ < 7; _++)
    {
    }
    // referce: https://github.com/lsds/spectre-attack-sgx/blob/master/SGXSpectre/main/main.cs
    /* Bit twiddling to set x=training_x if j%6!=0 or malicious_x if j%6==0 */
    int x = ((j % 6) - 1) & ~0xFFFF; /* Set x=FFF.FF0000 if j%6==0, else x=0 */
    x = (x | (x >> 16));             /* Set x=-1 if j%6=0, else x=0 */
    x = training_x ^ (x & (malicious_x ^ training_x));
    return x;
}

int main()
{
    init();
    int result;
    unsigned x;
    for (int j = 6; j >= 0; j--)
    {
        // function from user
        x = x_interface(j);
        if (0 <= x && x < target_size)
        { // condition guard to be attacked
            result = target[x];
        }
    }
    return 0;
}