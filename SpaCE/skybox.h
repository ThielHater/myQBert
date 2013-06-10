# ifndef SKYBOX_H
# define SKYBOX_H

# include <d3dx9.h>

class skybox
	{
	private:
		LPD3DXMESH boxmesh;
		D3DMATERIAL9 material;
		LPDIRECT3DTEXTURE9 textur[6];
		float size;
		void create_textures( char *oben, char *unten, char *links, char *rechts, char*vorn, char *hinten);
		void create_mesh();
		void setup_mesh( float siz);
		void setup_attributebuffer();
		void setup_attributetable();
	public:
		skybox();
		~skybox();
		static void init( LPDIRECT3DDEVICE9 dev);
		void create( float siz, char *oben, char *unten, char *links, char *rechts, char*vorn, char *hinten);
		void render( D3DXVECTOR3 *center);
	};

# endif