/*serves 2 purposes: most importantly, on a page fault, the kernel looks up the virtual page that 
faulted in the supplemental page table to find out what data should be there. Second, the kernel 
consults the supp-page table when a process terminates, to decide what resources to free.
*/

