 /* This is an algorithm for choosing the next 
 *  frame to be evicted.
 *  Runs on a general FIFO algorithm as
 *  described in slideset #9.
 */

#include <stdio.h>
#include <stdlib.h>
#include "vm/eviction.h"
#include "vm/frames.h"

int next_evicted = 0;
int frames = 383;


//struct frame *fifo_out(int num_frames_needed);
void evict(struct frame *toEvict, int page_cnt);



/* This function chooses the next frame in the frame table to evict.
 *  It simply goes through the frames in numerical order and selects 
 *  the next frame.  
 * ASSUMPTIONS: The frame table is full and a call to palloc() has failed.
 * @return value: A pointer to the next frame that will be evicted.
 */
struct frame *fifo_out(int num_frames_needed)
{	
	// Quick check to make sure the kernel can evict the number of frames needed.
	//  Returns NULL if there aren't that many frames in the frame table.
	if(num_frames_needed > frames)
	{
		return NULL;
	}

	// Checks if the pointer needs to be wrapped back to the front.
	//  This will happen if there is not enough contiguous frames that
	//  can be evicted.
	if(next_evicted + num_frames_needed > frames)
	{
		next_evicted = 0;
	}

	// A pointer to the frame that will be evicted
	struct frame *ret_val = &frameTable[next_evicted];

	// Advance the index of the next evicted frame by the number of pages evicted
	next_evicted = next_evicted + num_frames_needed;

	// Loops the index of the next evicted frame back to the beginning
	//next_evicted = next_evicted % numFrames;

	return ret_val;
}

void evict(struct frame *toEvict, int page_cnt){
	int i;
	for (i = 0; i < page_cnt; i++){
		// 	go into frame table, find thread owner of current frame to evict
		//	get page dir of thread owner
		//	find out if page has been written to
		//	if yes >> write to swap, need a bitmap, search for an empty spot, user block write
		//	(if no swap space, panic the kernel)
		//	else, no need, same file still in file sys
		//	update supplemental page table of the thread to reflect this change
		//	update frame table

	}
}







