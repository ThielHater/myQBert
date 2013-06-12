# ifndef OBJEKT_H
# define OBJEKT_H

# include <d3dx9.h>

# define RENDER_OPAQUE 1
# define RENDER_TRANSPARENT 2
# define RENDER_ALL 3

class textur
	{
	friend class objekt;
	private:
		LPDIRECT3DTEXTURE9 tx;
	public:
		textur();
		~textur();
		int load( char *txfilename);
	};

class objekt
	{
	private:
		LPD3DXMESH mesh;
		D3DMATERIAL9 *materialien;
		DWORD anz_mat;
		LPDIRECT3DTEXTURE9 *texturen;
		D3DXMATRIX transform;
		D3DXMATRIX inverse;
		int ivalid;
		void clear();
		void reset();
		void clone( const objekt& original);
		D3DXVECTOR3 min, max, center;
		float radius;
		D3DCULL cullmode;

	public:
		objekt(){ clear();}
		~objekt(){ reset();}
		objekt( const objekt& obj){ clear(); clone( obj);}
		objekt& operator=( const objekt& obj) { clone( obj); return *this;}
		int load( char *xfile, char *directory = 0, D3DCULL cmode = D3DCULL_CCW);
		void set_transform( D3DXMATRIX *tr) {transform = *tr; ivalid = 0;}
		void add_transform( D3DXMATRIX *tr) {transform *= *tr; ivalid = 0;}
		void get_transform( D3DXMATRIX *m) { *m = transform;}
		void get_inverse( D3DXMATRIX *m){ if( !ivalid){D3DXMatrixInverse( &inverse, 0, &transform);ivalid = 1;} *m = inverse;}
		void render( int blending = 0, int opcode = RENDER_ALL);
		int distance( D3DXVECTOR3 pos, D3DXVECTOR3 dir, float *dist);
		void get_boundingbox( D3DXVECTOR3 *luv, D3DXVECTOR3 *roh){ *luv = min; *roh = max;}
		void get_boundingsphere( D3DXVECTOR3 *c, float *r){ *c = center, *r = radius;}
		int inbox( D3DXVECTOR3 *v);
		int insphere( D3DXVECTOR3 *v);
		void render_box(int r, int g, int b);
		void render_sphere(int r, int g, int b);
		D3DXVECTOR3 lookatme( D3DXVECTOR3 *dir, float abst);
		void impact( D3DXVECTOR3 pos, D3DXVECTOR3 dir, float radius, float intensity, float random = 0);
		void deformation( int (*test)( const D3DXVECTOR3 *), D3DXMATRIX *m);
		void destruction( D3DXVECTOR3 center, float radius, int anz = 3);
		void destruction( D3DXVECTOR3 from, D3DXVECTOR3 to, float radius, int anz = 3);
		void destruction( int (*test)( const D3DXVECTOR3 *, const D3DXVECTOR3 *, const D3DXVECTOR3 *));
		void forallvertices( void (*doit)( D3DXVECTOR3 *));
		void forallmaterials( void (*doit)( int , D3DMATERIAL9 *));
		int set_texture( int i, textur *tx);
		int swap_texture( int i, textur *tx);
		void enable_reflections() { D3DCOLORVALUE opaq = {1.0f, 1.0f, 1.0f, 0.0f}; for(unsigned int i=0; i<anz_mat; i++) (materialien+i)->Specular = opaq; }
		void disable_reflections() { D3DCOLORVALUE trans = {0.0f, 0.0f, 0.0f, 0.0f}; for(unsigned int i=0; i<anz_mat; i++) (materialien+i)->Specular = trans; }
	};

# endif