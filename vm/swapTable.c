#include "lib/kernel/bitmap.h"
#include <stdio.h>
#include "vm/spt.h"
#include "lib/kernel/hash.h"

struct swapTable {
	struct bitmap *table;
	size_t numSlots;
	size_t firstFree;
	size_t numFree;
	struct hash_iterator i;
}

size_t sectors_per_page = 8;

bool checkSlot(size_t index) {
	bool used = bitmap_test(table, index);
	return used;	
}
blahhhh
//need to add lock to addPage and getPage
bool addPage(struct frame *new) {
	//check if swap table is full
	if (bitmap_all(table, 0, numSlots)) {
		return false; //throw exception?
	}
	bitmap_set(table, firstFree, true); //maps frame to first free slot
	numFree--;
	if (numFree) {
		firstFree = bitmap_scan(table, firstFree, 1, false); //finds first free slot after the set bit
	}
	return true;	
} 


//addLock
bool getPage(size_t index) {
	if (bitmap_test(table, index)) {
		bitmap_flip(table, index);
		numFree++;
		if (index < firstFree) 
			firstFree = index;
		return true;
	}
	return false;
}

bool free(struct thread *process) {
	struct hash_iterator i;
	hash_first(i, process->spt); 
	while (hash_cur(i) != NULL) {
		if (hash_cur(i)->isSwapped) {
			getPage(hash_cur(i));
		}
		hash_next(i);
	}
}

void initializeSwapTable() {
	struct block *swapSpace = block_get_role(BLOCK_SWAP);
	block_sector_t bitmap_size = block_size(swapSpace)/sectors_per_page;
	table = bitmap_create(bitmap_size);
	numSlots = numBits;
	numFree = numSlots;
	firstFree = 0;
}
