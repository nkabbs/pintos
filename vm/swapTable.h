#ifndef VM_SWAPTABLE_H
#define VM_SWAPTABLE_H

struct swapTable {
        struct bitmap *table;
        size_t numSlots;
        size_t firstFree;
        size_t numFree;
        struct hash_iterator i;
}

bool checkSlot(size_t index);
bool addPage(struct frame *new);
bool getPage(size_t index);
bool free(struct thread *process);
void initializeSwapTable();
