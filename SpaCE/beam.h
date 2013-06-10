# ifndef BEAM_H
# define BEAM_H

# include <d3dx9.h>

class beam
	{
	private:
		LPD3DXMESH mesh;
		D3DXMATRIX t;
		void create_mesh();
		void setup_mesh( float length, float size);
		void setup_attributebuffer();
		void setup_attributetable();
	public:
		beam();
		~beam();
		void create( float length, float size);
		void set_transform( D3DXMATRIX *m){ t = *m;}
		void add_transform( D3DXMATRIX *m){ t *= *m;}
		void render( int r, int g, int b, float a = 1);
	};

# endif