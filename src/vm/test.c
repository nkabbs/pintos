#include "../lib/kernel/hash.c"

struct a{
	int a;
	int b;
	struct hash_elem hash_elem;
};

unsigned hashFunction(const struct hash_elem *e, void *aux){
	const struct a *outerStruct = hash_entry(e, struct a, hash_elem);
	return hash_int(outerStruct->a);
}

bool lessFunction(const struct hash_elem *one, const struct hash_elem *two, void *aux){
	const struct a *outerOne = hash_entry(one, struct a, hash_elem);
	const struct a *outerTwo = hash_entry(two, struct a, hash_elem);
	return outerOne->a < outerTwo->a;
}

int main(){
	struct a test = {1, 2};
	struct hash *h;
	hash_init(h, &hashFunction, &lessFunction, NULL);
}

