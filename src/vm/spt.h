#ifndef VM_SPT_H
#define VM_SPT_H

enum udpateType{
	physMemToSwap,
	physMemToFileSys,
	fileSysToPhysMem
};

void updateSPT(void *vaddr, enum updateType type);


#endif 
