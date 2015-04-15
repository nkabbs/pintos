#ifndef VM_EVICTION_H
#define VM_EVICTION_H

//#include "vm/frames.h"

struct frame *fifo_out(int num_frames_needed);
//void evict(struct frame *toEvict, int page_cnt);


#endif
