 /* This is an algorithm for choosing the next 
 *  frame to be evicted.
 *  Runs on a general FIFO algorithm as
 *  described in slideset #9.
 */


#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define NUM_FRAMES 10
typedef unsigned char boolean;

struct frame {
	int id;
};

struct frame *frame_table[NUM_FRAMES];

int next_evicted;

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
	if(num_frames_needed > NUM_FRAMES)
	{
		return NULL;
	}

	// Checks if the pointer needs to be wrapped back to the front.
	//  This will happen if there is not enough contiguous frames that
	//  can be evicted.
	if(next_evicted + num_frames_needed > NUM_FRAMES)
	{
		next_evicted = 0;
	}

	// A pointer to the frame that will be evicted
	struct frame *ret_val = frame_table[next_evicted];

	// Advance the index of the next evicted frame by the number of pages evicted
	next_evicted = next_evicted + num_frames_needed;

	// Loops the index of the next evicted frame back to the beginning
	next_evicted = next_evicted % NUM_FRAMES;

	return ret_val;
}


