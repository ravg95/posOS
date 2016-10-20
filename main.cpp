#include "stddef.h"
#include "stdint.h"
#include "ostream.h"


void delay(int countdown_limit) {
	volatile int w = 0;
	while (w<countdown_limit) {
		w++;
	}
}

extern "C" void kmain(const void* multiboot_struct, uint32_t magic_num) {
	ostream osout = ostream();
	for (int i = 0; i < 5000; i++) {
		i %= 127;
		osout << "We are OS noobs: " << (char)i+'a' << '\n';
		delay(100000);
	}

	//for (int i = 0;i < 10;i++) osout.WriteString("youve got some nerve coming out here\ninto the eye of the storm\nwith a noose around your neck\nobey dont think consume\n");

	while (1);
}
