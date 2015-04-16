#include "bit_operations.h"

using namespace std;

void BitOP::SET_REFERENCED(PTE& page) {
	page.referenced = 1;
}
void BitOP::UNSET_REFERENCED(PTE& page) {
	page.referenced = 0;
}
unsigned int BitOP::GET_REFERENCED(PTE& page) {
	return page.referenced;
}

void BitOP::SET_MODIFIED(PTE& page) {
	page.modified = 1;
}
void BitOP::UNSET_MODIFIED(PTE& page) {
	page.modified = 0;
}
unsigned int BitOP::GET_MODIFIED(PTE& page) {
	return page.modified;
}

void BitOP::SET_PRESENT(PTE& page) {
	page.present = 1;
}
void BitOP::UNSET_PRESENT(PTE& page) {
	page.present = 0;
}
unsigned int BitOP::GET_PRESENT(PTE& page) {
	return page.present;
}

void BitOP::SET_PAGEDOUT(PTE& page) {
	page.pagedout = 1;
}
void BitOP::UNSET_PAGEDOUT(PTE& page) {
	page.pagedout = 0;
}
unsigned int BitOP::GET_PAGEDOUT(PTE& page) {
	return page.pagedout;
}
