
#include "ostream.h"
#include "stddef.h"
#include "stdint.h"

	uint8_t ostream::GetColor(enum vga_color fg, enum vga_color bg) {
		return fg | (bg << 4);
	}

	uint16_t ostream::GetRawEntry(unsigned char uc, uint8_t color) {
		return uc | ((uint16_t)color << 8);
	}

	ostream::ostream(){
		terminal_buffer = (volatile uint16_t*)0xb8000;
		terminal_column=0;
		terminal_row=0;
		terminal_color = GetColor(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
		for (size_t y = 0; y < VGA_HEIGHT; y++) {							//make sure it's clean
			for (size_t x = 0; x < VGA_WIDTH; x++) {
				const size_t index = y * VGA_WIDTH + x;
				terminal_buffer[index] = GetRawEntry(' ', terminal_color);
			}
		}
	}

	ostream::~ostream(){
		//empty - not much to destroy
	}

	void ostream::ScrollDown()
	{
		for (int i = 0; i<(VGA_HEIGHT-1)*VGA_WIDTH;i++)
		{
			terminal_buffer[i] = terminal_buffer[i + VGA_WIDTH];
		}
		for (int j = 0;j < VGA_WIDTH;j++)
		{
			terminal_buffer[(VGA_HEIGHT - 1)*VGA_WIDTH + j] = ' ';
		}
		--terminal_row;
	}

	static size_t strlen(const char* str) //possibly move this somewhere else later
	{ 
		size_t len = 0;
		while (str[len])
			len++;
		return len;
	}

	void ostream::PutChar(char c)
	{
		if (c == '\n')
		{
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
			{
				ScrollDown();
			}
				
		}
		else 
		{
			PutCharAtLocation(c, terminal_color, terminal_column, terminal_row);
			if (++terminal_column == VGA_WIDTH) //do we need to change column?
			{
				terminal_column = 0;
				if (++terminal_row == VGA_HEIGHT)
					ScrollDown();
			}
		}

	}

	void ostream::PutCharAtLocation(char c, uint8_t color, size_t x, size_t y)
	{
		const size_t index = y * VGA_WIDTH + x;
		terminal_buffer[index] = GetRawEntry(c, color);
	}	

	void ostream::Write(const char* data, size_t size)
	{
		for (size_t i = 0;i < size;i++)
		{
			PutChar(data[i]);
		}
	}

	void ostream::WriteString(const char* string)
	{
		size_t len = 0;
		while (string[len])
		{
			PutChar(string[len]);
			len++;
		}
	}

ostream& operator<<(ostream& s, const char* str) {

	s.WriteString(str);
	return s;
}
ostream& operator<<(ostream& s, const int i) {
	return s << (char)(i + '0');
}
ostream& operator<<(ostream& s, const char c) {
	s.PutChar(c);
	return s;
}

ostream& operator<<(ostream& s, const float f) {
	return s;
}