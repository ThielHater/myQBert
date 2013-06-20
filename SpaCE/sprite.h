# ifndef SPRITE_H
# define SPRITE_H

# include <d3dx9.h>

class sprite
	{
	private:
		static sprite *first;
		sprite *next;
		LPDIRECT3DTEXTURE9 tx;
		LPD3DXSPRITE sp;
		int breite;
		int hoehe;
		float xfactor;
		float yfactor;
		int zeilen;
		int spalten;
	public:
		sprite();
		~sprite();
		static void OnLostDevice();
		static void OnResetDevice();
		void load( char *txfile, DWORD colorkey, int z = 1, int s = 1);
		void move( float xtrans, float ytrans, float xscale, float yscale, float zdreh);
		void move( int lox, int loy, int rux, int ruy);
		void render(int z = 0, int s = 0);
		void set_tx(LPDIRECT3DTEXTURE9 arg_tx) { tx = arg_tx; }
	};

# endif