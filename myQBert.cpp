# include "SpaCE/applikation.h"
# include <math.h>

void EnableReflections(int ix, D3DMATERIAL9 *mat)
{
	D3DCOLORVALUE opaq = {1.0f, 1.0f, 1.0f, 0.0f};
	mat->Specular = opaq;
}

void DisableReflections(int ix, D3DMATERIAL9 *mat)
{
	D3DCOLORVALUE trans = {0.0f, 0.0f, 0.0f, 0.0f};
	mat->Specular = trans;
}

class spiel : public applikation
{
	private:
		objekt cubes[28];
		objekt qbert;
	public:
		void setup();
		int render();
};

void spiel::setup()
{
	// Variablendeklaration
	textur cube_tex;
	textur qbert_tex;
	D3DXMATRIX rota;
	D3DXMATRIX trans;
	float x=0; float y=0; float z=0; float dia=sqrt(50.0f);

	// Titel und Hintergrundfarbe setzen
	set_bkcolor(0, 0, 0);
	set_title("myQBert");

	// Texturen laden
	cube_tex.load("myQBert/Cube-L0-R1-1.png");
	qbert_tex.load("myQBert/QBert-Down-Left.png");
	
	// Modell und Textur laden, Reflektionen ausschalten und Objekte positionieren	
	D3DXMatrixRotationY(&rota, D3DX_PI/4.0f);
	for(int i=0; i<28; i++)
	{
		if ((i==7) || (i==13) || (i==18) || (i==22) || (i==25) || (i==27) || (i==28)) { y++; x=y-(y*0.5f); z=y*dia/2; }
		D3DXMatrixTranslation(&trans, x*dia, y*5.0f, z);
		cubes[i].load("Cube.x", "myQBert");
		cubes[i].set_texture(0, &cube_tex);
		cubes[i].forallmaterials(DisableReflections);
		cubes[i].add_transform(&rota);
		cubes[i].add_transform(&trans);
		x++;
	}
	D3DXMatrixRotationY(&rota, -D3DX_PI/4.0f);
	D3DXMatrixTranslation(&trans, 3*dia, 15.0f, dia);
	qbert.load("TriPrism.x", "myQBert");
	qbert.forallmaterials(DisableReflections);
	qbert.set_texture(0, &qbert_tex);
	qbert.add_transform(&rota);
	qbert.add_transform(&trans);

	// Kamera
	set_perspektive(D3DX_PI/4.0f, 1.0f, 100.0f);
	blickrichtung = D3DXVECTOR3(0, -D3DX_PI/6.0f, 1);
	standort = cubes[19].lookatme(&blickrichtung, 15.0f);
	//standort = D3DXVECTOR3(dia*3.0f, 40, -45);
}

int spiel::render()
{
	for(int i=0;i<28;i++)
		cubes[i].render(0, RENDER_OPAQUE);
	qbert.render(1, RENDER_ALL);
	return 1;
}

spiel mein_spiel;