#ifndef VM_FRAMES_H
#define VM_FRAMES_H

#include "kernel/palloc.h"
#include "kernel/thread.h"

struct frame{
	void *frame;
	void *page;
	struct thread *owner;
	bool used;
};

//int numFrames = 383;
struct frame frameTable[383];

void *getFrames(enum palloc_flags flags, size_t page_cnt);
void updateFrameTable(void *virtAddr, size_t page_cnt, bool frameMapped, enum palloc_flags flags);

#endif /* vm/frames.h */
