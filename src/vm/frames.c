#include "kernel/palloc.h"
#include "kernel/pagedir.h"
#include "kernel/thread.h"
#include <stdio.h>

/* Wrapper for page allocator, calls palloc to hand out memory,
while updating a global frame table and implementing an 
eviction strategy if there are no frames to give out */


struct frame{
	void *frame;
	void *page;
	bool used;
	//need more info?
};

struct frame *clockPtr;
struct frame *evicted;
struct frame frameTable[383];

const int numFrames = 383;
int mappedFrames = 0;
int neverCalled = 1;
const int frameSize = 4096;


//malloc frame table?
//handle PAL_ZERO flag
void *getFrames(enum palloc_flags flags, size_t page_cnt){
	if (page_cnt > numFrames){
		printf("Frames requested greated than total available frames");		
		return NULL;
	}
	if (neverCalled){	
		initializeFrameTable();
		neverCalled = 0;
	}
	void *virtAddr = palloc_get_multiple(flags, page_cnt);
	if (!virtAddr){	//null was returned from palloc, handle eviction
		//eviction here
//		evicted = evict();

		virtAddr = palloc_get_multiple(flags, page_cnt);
		if (!virtAddr){
			printf("Eviction failed");
			return NULL;
		} else {
			updateFrameTable(virtAddr, page_cnt, true);
		}
	} else {
		updateFrameTable(virtAddr, page_cnt, false);
	}
	return virtAddr;
}

void initializeFrameTable(){
	//INITIALIZE ALL PAGES TO ZERO
	unsigned int i;
	for (i = 0; i < numFrames; i++){
		frameTable[i].page = (void *)0;
		frameTable[i].frame = (void *)0;
		frameTable[i].used = false;
	}
	clockPtr = &frameTable[0];
}

//frameMapped=true >>> this frame is already mapped, we much search and update it
//frameMapped=false >>> not already mapped, index to an empty one
void updateFrameTable(void *virtAddr, size_t page_cnt, bool frameMapped){
	//lock while updating frame table
	struct thread *currThread = thread_current();
	uint32_t *pd = currThread->pagedir;
	unsigned int i;
	for (i = 0; i < page_cnt; i++){
		void *physAddr = pagedir_get_page(pd, virtAddr);
		if (frameMapped){
			evicted->page = virtAddr;
		} else {
			frameTable[mappedFrames].frame = physAddr;
			frameTable[mappedFrames].page = virtAddr;
			frameTable[mappedFrames].used = 1;
		}
		//move vitual address forward one page size in case we are mapping more than
		//one frame
		virtAddr += frameSize;
	}
	if (mappedFrames < numFrames){
		mappedFrames += page_cnt;
	}
}




