#include "branch_predictor.h"

/* ************** */
/* TASK3: 2018011359, 2018011334 */
/* ************** */

#define PHT_ROW_BIT 3
#define PHT_COL_BIT 8
// #define PHT_SIZE_BYTE (1<<(PHT_ROW_BIT + PHT_COL_BIT - 2)
// #define BTB_SIZE_BYTE (PREDICTOR_SIZE - PHT_SIZE_BYTE)
// #define BTB_SIZE_ENTRY (BTB_SIZE_BYTE >> 2)
#define PHT_SIZE_BYTE 512
#define BTB_SIZE_BYTE 512
#define BTB_SIZE_ENTRY 128

typedef struct {
    uint16_t pc;
    uint16_t target;
}BTBEntry;
BTBEntry* BTB;
uint16_t BTB_CNT, BTB_INC;
uint8_t BHR;
uint16_t* PHT; //PHT stored column-first
char predictor_space[PREDICTOR_SIZE];

va_t search_BTB(reg64_t pc) {
    int i;
    uint16_t pc_low = (uint16_t) pc;
    va_t target = pc + 4;
    for (i = 0; i < BTB_CNT; i++) {
        if (BTB[i].pc == pc_low) {
            target = (pc & ~0xFFFF) + BTB[i].target;
            break;
        }
    }
    return target;
}

void update_BTB(reg64_t pc, va_t target) {
    int i;
    uint16_t pc_low = (uint16_t) pc;
    for (i = 0; i < BTB_CNT; i++) {
        if (BTB[i].pc == pc_low) {
            BTB[i].target = (uint16_t) target;
            return;
        }
    }

    // FIFO
    BTB[BTB_INC % BTB_SIZE_ENTRY].pc = pc_low;
    BTB[BTB_INC % BTB_SIZE_ENTRY].target = (uint16_t) target;
    BTB_INC += 1;
    if (BTB_CNT < BTB_SIZE_ENTRY) {
        BTB_CNT += 1;
    }
}

uint16_t get_pht_entry(reg64_t pc) {
    // use BHR as column idnex
    uint16_t pht_col = PHT[BHR];
    // use PC[4:2] as row index
    uint16_t row_idx = ((pc & 0x1C) >> 2); //11100
    uint16_t mask = (0x3 << (row_idx * 2));
    return ((pht_col & mask) >> (row_idx * 2));
}

void update_pht_entry(reg64_t pc, int jump) {
    // use BHR as column idnex
    uint16_t pht_col = PHT[BHR];
    // use PC[4:2] as row index
    uint16_t row_idx = ((pc & 0x1C) >> 2); //11100
    uint16_t mask = (0x3 << (row_idx * 2));
    uint16_t pht_entry = ((pht_col & mask) >> (row_idx * 2));
    
    // update new pht entry
    uint16_t new_pht_entry = pht_entry;
    if (jump && pht_entry != 0x3) {
        new_pht_entry = pht_entry + 1;
    }
    if (!jump && pht_entry != 0x0) {
        new_pht_entry = pht_entry - 1;
    }
    uint16_t new_pht_col = (pht_col & ~mask) + (new_pht_entry <<(row_idx * 2));
    PHT[BHR] = new_pht_col;
}

void branch_predictor_init(void) {
    int i;
    // Init PHT
    for(i = 0; i < PHT_SIZE_BYTE; i++) {
        predictor_space[i] = 0xAA; //10101010
    }
    BTB_CNT = 0;
    BTB_INC = 0;
    BHR = 0;
    PHT = (uint16_t*) predictor_space;
    BTB = (BTBEntry*) (predictor_space + PHT_SIZE_BYTE);
}

va_t get_from_branch_predictor(reg64_t pc) {
    // DONE: once your branch predictor get an instruction address, it should give a predicted target address
    uint16_t pht_entry = get_pht_entry(pc); // 2 bit branch predictor
    if (pht_entry & 0x2) {
        //jump
        return search_BTB(pc);
    }
    else {
        return pc + 4;
    }
}

void branch_predictor_update(reg64_t pc, va_t target) {
    // DONE: the debugger will give the correct target address once a branch instrucion executed, and you need to update the branch predictor
    int jump = (target != pc + 4);
    update_pht_entry(pc, jump);
    BHR = (BHR<<1) + jump;
    if(jump) {
        update_BTB(pc, target);
    }
}

void branch_predictor_release(void) {
    // TODO: other code if necessary
}