#include "frames.h"
#include "kernel/thread.h"
#include "hash.h"
#include "spt.h"

struct sptEntry{
	bool isStackPage;
	enum pageType;
	void *vaddr;
	int sectorOffset;
	struct hash_elem hash_elem;
}


enum pageType{
	swap,
	fileSys,
	physMem
};

/*enum updateType{
	physMemToSwap;
	physMemToFileSys;
	fileSysToPhysMem;
}*/

void setUp();
void update(void *vaddr, enum updateType type);
void *resourceToFree();
bool lessFunction(const struct hash_elem *one, const struct hash_elem *two, void *aux);
unsigned hashFunction(const struct hash_elem *e, void *aux);

void updateSPT(void *vaddr, enum updateType type){
	struct thread *currThread = thread_current();
	bool uninitialized = currThread->sptUninitialized; //ADD TO THREAD STRUCT
	if (uninitialized){
		setUp();
		currThread->sptUninitialized = 0;
	}
	update(vaddr, type);
}

// First time called, we need to setup a hash table for the thread
void setUp(){
	struct thread *currThread = thread_current();
	struct hash *threadSPT;
	hash_init(threadSPT, &hashFunction, &lessFunction, NULL);
	currThread->spt = threadSPT;
}

void update(void *vaddr, enum updateType type){
	//spt entry = hash find vaddr
//	struct hash_elem *e = hash_entry(      )
//	if (type == physMemToSwap){
//		
//	}
}

void *resourceToFree(){
	return NULL;
}

// Define a hash function for this data type:
// The virtual address member of an sptEntry struct, hashed
// with PintOS's int hash function.
unsigned hashFunction(const struct hash_elem *e, void *aux){
	struct sptEntry *spt = hash_entry(e, struct sptEntry, hash_elem);
	return hash_int(spt->vaddr);
}

// Define a less function to initilize the hash table.
// Return outcome of one sptEntry's virtual addr is greater than another's
bool lessFunction(const struct hash_elem *one, const struct hash_elem *two, void *aux){
	struct sptEntry *entryOne = hash_entry(one, struct sptEntry, hash_elem);
	struct sptEntry *entryTwo = hash_entry(two, struct sptEntry, hash_elem);
	return (entryOne->vaddr) < (entryTwo->vaddr);
}
