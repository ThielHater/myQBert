# ifndef VIDEO_H
# define VIDEO_H

# include <windows.h>

class video
	{
	private:
		static video *first;
		video *next;
		HWND wnd;
		void notify( WPARAM wParam, LPARAM lParam);
	public:
		static void notification( WPARAM wParam, LPARAM lParam);
		video();
		~video();
		void create( char *mediafile, int time = 0);
		void setup( int x, int y, int b, int h);
		void play( long from = -1, long to = -1);
		long getstart();
		long getpos();
		long getend();
		long getlength();
		void getsize( int *b, int *h);
		void pause( int hide = 0);
		void stop( int hide = 1);
		void resume();
		void show( int shw);
		void setpos( long pos, int go = 1);
		void destroy();
		virtual void onend();
	};

# endif