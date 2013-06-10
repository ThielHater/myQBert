# ifndef DIRECTX_H
# define DIRECTX_H

# define DIRECTINPUT_VERSION 0x0800

# include <d3dx9.h>
# include <dinput.h>
# include "d3dfont.h"
# include "dsutil.h"

struct lightinfo
	{
	int on;
	D3DLIGHT9 light;
	};

struct beleuchtung
	{
	DWORD ambient;
	int maxlight;
	lightinfo *lightarray;
	};

class directx
	{
	private:
		LPDIRECT3D9 d3d;
		D3DPRESENT_PARAMETERS d3dpp;
		D3DCOLOR bkcolor;
		CD3DFont fnt;
		D3DXMATRIX perspektive;
		void set_renderstates();
		void set_samplerstates();
		float blickfeld;
		float nearpane;
		float farpane;
		DWORD txtcolor;
		unsigned char ambient;
		beleuchtung licht;	
		void reset_light();
		float fogs;
		float foge;
		DWORD fogc;
		char fogon;
	public:
		int init();
		void adjust(int breite, int hoehe);
		void prepare( D3DXVECTOR3 *hier, D3DXVECTOR3 *dahin, D3DXVECTOR3 *oben);
		void present();
		void set_bkcolor( int r, int g, int b){ bkcolor = D3DCOLOR_XRGB(r,g,b);}
		void set_perspektive( float bf, float nr, float fr);
		void display_text( int x, int y, char *fmt, va_list arg);
		void set_txtcolor( DWORD tc) {txtcolor = tc;}
		void set_ambilight( unsigned char intensity);
		void set_sunlight( int index, D3DXVECTOR3 *dir, float ambient, float diffuse, float specular);
		void set_spotlight( int index, D3DXVECTOR3 *pos, D3DXVECTOR3 *dir, float range, float ambient, float diffuse, float specular);
		void set_pointlight( int index, D3DXVECTOR3 *pos, float range, float ambient, float diffuse, float specular);
		void switch_light( int index, int on);
		int get_maxlights() {return licht.maxlight;}
		void fog_on( float start, float end, DWORD color = RGB(255,255,255));
		void fog_off();
		void max_texturesize( int *b, int *h);
		void screenshot( char *prefix);
		void render_point( D3DXVECTOR3 &v, float size, int r, int g, int b);
		void render_line( D3DXVECTOR3 &from, D3DXVECTOR3 &to, int r, int g, int b);
		void render_coordinates( D3DXVECTOR3 &origin, int anz, float abst, float xysize, float xzsize, float yzsize, int r, int g, int b);
		void render_grid( D3DXVECTOR3 &center, int xanz, int yanz, int zanz, float abst, int r, int g, int b);
		directx();
		~directx();
	};

class input
	{
	private:
		LPDIRECTINPUT8 dinput;
		LPDIRECTINPUTDEVICE8 maus;
		LPDIRECTINPUTDEVICE8 tastatur;     
	public:
		int init();
		int poll_mouse( DIMOUSESTATE *mstate);
		int poll_keyboard( 	unsigned char *key);
	};

class sounds
	{
	private:
		CSoundManager smgr;
		CSound **snd;
		int anzahl;
		void clear();
	public:
		sounds();
		int init();
		void load( int anz, va_list arg);
		void play( int snr, int loop);
		long getpos( int snr);
		int setpos( int snr, long pos);
		void stop( int snr);
		~sounds(){ clear();}
	};


# endif
