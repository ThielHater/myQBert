# ifndef SPLASHSCREEN_H
# define SPLASHSCREEN_H

# include <windows.h>

class splashscreen
	{
	private:
		HWND wnd;
		HWND pro;
		HBITMAP bmp;
	public:
		splashscreen();
		~splashscreen();
		void create( char *picture, int border, int fortschritt = 0);
		void progress( int percent);
		void release();
	};

# endif