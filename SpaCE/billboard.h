# ifndef BILLBOARD_H
# define BILLBOARD_H

# include <d3dx9.h>

# define BILL_FIX_NONE 0
# define BILL_FIX_X    1
# define BILL_FIX_Y    2
# define BILL_FIX_Z    3

class billboard
	{
	private:
		LPD3DXMESH mesh;
		D3DMATERIAL9 material;
		LPDIRECT3DTEXTURE9 textur;
		float posx;
		float posy;
		float posz;
		float scalex;
		float scaley;
		int fix;
		void clear();
		void reset();
		void clone( const billboard& original);
	public:
		billboard(){ clear();}
		~billboard(){ reset();}
		billboard( const billboard& obj){ clear(); clone( obj);}
		billboard& operator=( const billboard& obj) { clone( obj); return *this;}
		void create( float sizx, float sizy, char *tx, DWORD colorkey, int fx);
		void setposition( float x, float y, float z, float scx, float scy) {posx = x; posy = y, posz = z; scalex = scx; scaley = scy;}
		void getposition( D3DXVECTOR3 *v) {v->x = posx; v->y = posy; v->z = posz;}
		void render();
	};

# endif