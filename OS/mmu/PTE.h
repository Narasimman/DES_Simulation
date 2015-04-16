#ifndef __PTE__
#define __PTE__

struct PTE {
	unsigned int present : 1;
	unsigned int referenced : 1;
	unsigned int modified : 1;
	unsigned int pagedout :1;
	unsigned int framenumber : 24;
};

#endif