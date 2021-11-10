#include <iostream>
#include <ctime>

using std::cout;
using std::endl;

const int KB = 1024;
const int MB = 1024 * 1024;
const int LINE_SIZE = 64;
const int LINE_INT = LINE_SIZE / sizeof(int);
const int DATA_CAP = 64 * MB / sizeof(int);

int data[DATA_CAP];

void cacheSize() {
    const int REPEAT = 1e9;
    cout << "Measure Cache Size. Output \"KB, s\"" << endl;
    for (int size = 8 * KB; size <= 64 * MB; size *= 2) {
        const int mask = (size - 1) / (int) sizeof(int);
        clock_t start = clock();
        for (int i = 0; i < REPEAT; i++) {
            data[(i * LINE_INT) & mask] = 10;
        }
        clock_t end = clock();
        double time = (double) (end - start) / CLOCKS_PER_SEC;
        cout << size / KB << "," << time << endl;
    }
}

void cacheLineSize() {
    const int REPEAT = 1e9;
    const int MASK = DATA_CAP - 1;
    cout << "Measure Cache Size. Output \"B, s\"" << endl;
    for (int lineSize = 4; lineSize <= 256; lineSize *= 2) {
        const int stride = lineSize / (int) sizeof(int);
        clock_t start = clock();
        for (int i = 0; i < REPEAT; i++) {
            data[(i * stride) & MASK] = 10;
        }
        clock_t end = clock();
        double time = (double) (end - start) / CLOCKS_PER_SEC;
        cout << lineSize << "," << time << endl;
    }
}

void cacheAssociativity() {
    const int DATA_LEN = 2 * 32 * KB / (int) sizeof(int);
    const int MASK = DATA_LEN - 1;
    const int REPEAT = 1e9;
    cout << "Measure Cache Associativity. Output \"n, s\"" << endl;
    for (int groups = 4; groups <= 256; groups *= 2) {
        const int blockSize = DATA_LEN / groups;
        int idx = 0;
        clock_t start = clock();
        for (int i = 0; i < REPEAT; i++) {
            data[idx] = 10;
            idx = (idx + 2 * blockSize) & MASK;
        }
        clock_t end = clock();
        double time = (double) (end - start) / CLOCKS_PER_SEC;
        cout << groups << "," << time << endl;
    }
}

void cacheReplacementPolicy() {
    const int DATA_LEN = 32 * KB / (int) sizeof(int);
    const int HALF_LEN = DATA_LEN / 2;
    const int REPEAT = 1e6;
    cout << "Measure cache replacement policy. Output \"s\"" << endl;

    cout << "Revisit frequently used" << endl;
    clock_t start = clock();
    for (int i = 0; i < REPEAT; i++) {
        for (int frequency = 0; frequency < 3; frequency++) {
            for (int idx = 0; idx < HALF_LEN; idx += 16) {
                data[idx] = 10;
            }
        }
        for (int idx = HALF_LEN; idx < DATA_LEN; idx += 16) {
            data[idx] = 10;
        }
        for (int idx = DATA_LEN; idx < DATA_LEN + HALF_LEN; idx += 16) {
            data[idx] = 10;
        }
        for (int idx = 0; idx < HALF_LEN; idx += 16) {
            data[idx] = 10;
        }
    }
    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    cout << time << endl;

    cout << "Revisit recently used" << endl;
    start = clock();
    for (int i = 0; i < REPEAT; i++) {
        for (int frequency = 0; frequency < 3; frequency++) {
            for (int idx = 0; idx < HALF_LEN; idx += 16) {
                data[idx] = 10;
            }
        }
        for (int idx = HALF_LEN; idx < DATA_LEN; idx += 16) {
            data[idx] = 10;
        }
        for (int idx = DATA_LEN; idx < DATA_LEN + HALF_LEN; idx += 16) {
            data[idx] = 10;
        }
        for (int idx = HALF_LEN; idx < DATA_LEN; idx += 16) {
            data[idx] = 10;
        }

    }

    end = clock();
    time = (double) (end - start) / CLOCKS_PER_SEC;
    cout << time << endl;
}

void cacheMemoryPolicy() {
    const int REPEAT = 1e5;
    const int DATA_LEN = 32 * KB / (int) sizeof(int);
    cout << "Measure cache memory interaction policy. Output \"s\"" << endl;

    cout << "Many write misses." << endl;
    clock_t start = clock();
    for (int i = 0; i < REPEAT; i++) {
        for (int idx = 0; idx < DATA_CAP; idx += 16 * (DATA_CAP / DATA_LEN)) {
            data[idx] = 10;
        }
    }
    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    cout << time << endl;

    cout << "No write misses." << endl;
    start = clock();
    for (int i = 0; i < REPEAT; i++) {
        for (int idx = 0; idx < DATA_LEN; idx += 16) {
            data[idx] = 10;
        }
    }
    end = clock();
    time = (double) (end - start) / CLOCKS_PER_SEC;
    cout << time << endl;
}