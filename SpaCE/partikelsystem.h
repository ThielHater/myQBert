# ifndef PARTIKELSYSTEM_H
# define PARTIKELSYSTEM_H

# include <d3dx9.h>

class partikelsystem
	{
	private:
		LPDIRECT3DVERTEXBUFFER9 partikelbuffer;
		int anzahl;
		D3DXMATRIX transform;
		float pointsize;
	public:
		partikelsystem();
		~partikelsystem();
		void create( int anz, float ptsiz);
		void set( int context);
		virtual void set_partikel( int context, int i, D3DXVECTOR3 &pos, D3DCOLOR &ambient, D3DCOLOR &emissive) = 0;
		void set_transform( D3DXMATRIX *tr) {transform = *tr;}
		void add_transform( D3DXMATRIX *tr) {transform *= *tr;}
		void render();
	};

# endif