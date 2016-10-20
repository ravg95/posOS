#ifndef __OSTREAM_H
#define __OSTREAM_H
#include "stddef.h"
#include "stdint.h"

enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;


class ostream{

public:
	ostream();
	~ostream();
	void PutChar(char c);
	void PutCharAtLocation(char c, uint8_t color, size_t x, size_t y);
	void Write(const char* data, size_t size);
	void WriteString(const char* string);
	friend ostream& operator<<(ostream& s,const char* str);
	friend ostream& operator<<(ostream& s,const int i);
	friend ostream& operator<<(ostream& s,const char c);
	friend ostream& operator<<(ostream& s,const float f);
	
private:
	uint8_t GetColor(enum vga_color fg, enum vga_color bg);
	uint16_t GetRawEntry(unsigned char uc, uint8_t color);
	void ScrollDown();
	volatile uint16_t* terminal_buffer;
	size_t terminal_column;
	size_t terminal_row;
	uint8_t terminal_color;
};
#endif
