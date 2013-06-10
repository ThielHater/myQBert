# ifndef TEXTBOX_H
# define TEXTBOX_H

# include <windows.h>

class textbox
	{
	private:
		HWND wnd;
	public:
		textbox();
		~textbox();
		void create( int border);
		void show( int shw);
		void move( int x, int y, int b, int h);
		void write( char *fmt, ...);
	};

# endif