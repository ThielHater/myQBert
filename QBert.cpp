#include "Qbert.h"

QBert::QBert(void)
{
}

QBert::~QBert(void)
{
}

void QBert::move(QBert::qbert_direction direction) {
	if (!is_moving) {
		is_moving = true;
		move_direction = direction;
	}
}

int QBert::Step()
{
	static int moved_sum = 0;

	int speed = 5;

	if (is_moving) {
		
		if (moved_sum >= speed) {
			is_moving = false;
			moved_sum = 0;
			return 0;
		}

		D3DXMATRIX tr;
		float sx = sqrt(50.0f) / 2 / speed;
		float sy = 5.0f / speed;
		float sz = sx;
		
		if (move_direction == LEFTDOWN)
			D3DXMatrixTranslation(&tr, -sx, -sy, -sz);
		else if (move_direction == LEFTUP)
			D3DXMatrixTranslation(&tr, -sx, sy, sz);
		else if (move_direction == RIGHTDOWN)
			D3DXMatrixTranslation(&tr, sx, -sy, -sz);
		else if (move_direction == RIGHTUP)
			D3DXMatrixTranslation(&tr, sx, sy, sz);

		add_transform(&tr);

		moved_sum++;
	}

	return 0;
}

int QBert::Collision(void)
{
	return 0;
}

int QBert::NodeEffect(void)
{
	return 0;
}