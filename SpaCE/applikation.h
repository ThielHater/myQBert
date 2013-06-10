# ifndef APPLIKATION_H
# define APPLIKATION_H

# include <stdio.h>
# include <windows.h>
# include <commctrl.h>
# include <d3dx9.h>
# include "directx.h"
# include "objekt.h"
# include "sprite.h"
# include "video.h"
# include "skybox.h"
# include "billboard.h"
# include "beam.h"
# include "textbox.h"
# include "splashscreen.h"
# include "partikelsystem.h"

class applikation
	{
	friend int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);
	private:
		HWND console;
		int timer_on;
		int durchschnittszeit;
		directx dx;
		input in;
		sounds sound;
		char *help;
		static LRESULT CALLBACK windowhandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static applikation *theapp;
		static BOOL WINAPI consolehandler( DWORD event);
		int init( HINSTANCE hInst);
		int run();
		int play();
	public:
		// Konstruktor/Destruktor ...
		applikation();
		~applikation();

		// Fensterfunktionen
		void set_title( char *txt);
		void set_bkcolor( int r, int g, int b){ dx.set_bkcolor(r,g,b);}
		void get_windowsize( int *x, int *y, int *b, int *h, int netto = 0);
		void set_window( int x, int y, int b, int h, int netto = 0);
		void max_window();
		void screenshot( char *prefix){ dx.screenshot( prefix);}
		
		// Kamerafuehrung
		D3DXVECTOR3 standort;
		D3DXVECTOR3 blickrichtung;
		D3DXVECTOR3 oben;
		void set_perspektive( float bf, float nr, float fr){ dx.set_perspektive( bf, nr, fr);}

		// Beleuchtung und visuelle Effekte
		void set_ambilight( unsigned char intensity){ dx.set_ambilight( intensity);}
		int get_maxlights() {return dx.get_maxlights();}
		void set_sunlight( int index, D3DXVECTOR3 *dir, float ambient, float diffuse, float specular)
			                                   { dx.set_sunlight( index, dir, ambient, diffuse, specular);}
		void set_spotlight( int index, D3DXVECTOR3 *pos, D3DXVECTOR3 *dir, float range, float ambient, float diffuse, float specular)
			                                 { dx.set_spotlight( index, pos, dir, range, ambient, diffuse, specular);}
		void set_pointlight( int index, D3DXVECTOR3 *pos, float range, float ambient, float diffuse, float specular)
			                                 { dx.set_pointlight( index, pos, range, ambient, diffuse, specular);}
		void switch_light( int index, int on){ dx.switch_light( index, on);}
		void fog_on( float start, float end, DWORD color = RGB(255,255,255)){dx.fog_on( start, end, color);}
		void fog_off(){dx.fog_off();}

		// Input
		int poll_mouse( DIMOUSESTATE *mstate);
		int poll_keyboard( unsigned char *key);

		// Textausgabe
		void set_textcolor( int r, int g, int b);
		void display_text( int x, int y, char *fmt, ...);

		// Console
		void open_console( char *title = NULL);
		void popup_console();
		void hide_console();
		void close_console();

		// Sound
		void load_sounds( int anz, ...);
		void play_sound( int i, int loop = 0){ sound.play( i, loop);}
		long get_soundpos( int i){ return sound.getpos( i);}
		long set_soundpos( int i, long pos){ return sound.setpos( i, pos);}
		void stop_sound( int i){ sound.stop( i);}

		// Timer
		void set_timer( int on, int avg = 0);
		void set_cps( int cps);

		// Hilfe
		void set_help( char *htmlfile);

		// Callbacks
		virtual void setup() = 0;
		virtual int render() = 0;
		virtual void onsize( int b, int h){}
		virtual void exit(){}

		// Systemfunktionen
		void max_texturesize( int *b, int *h){ dx.max_texturesize( b, h);}

		// Hilfslinien zeichnen
		void render_point( D3DXVECTOR3 &v, float size, int r, int g, int b){ dx.render_point( v, size, r, g, b);}
		void render_line( D3DXVECTOR3 &from, D3DXVECTOR3 &to, int r, int g, int b){ dx.render_line( from, to, r, g, b);}
		void render_coordinates( D3DXVECTOR3 &origin, int anz, float abst, float xysize, float xzsize, float yzsize, int r, int g, int b){ dx.render_coordinates( origin, anz, abst, xysize, xzsize, yzsize, r, g, b);}
		void render_grid( D3DXVECTOR3 &center, int xanz, int yanz, int zanz, float abst, int r, int g, int b){ dx.render_grid( center, xanz, yanz, zanz, abst, r, g, b);}
	};

# endif
