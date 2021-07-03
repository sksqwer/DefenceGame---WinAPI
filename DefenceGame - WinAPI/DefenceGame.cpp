#include "DefenceGame.h"
#include "ctime"
#include <fstream>

POINT Rotate(const POINT &center, const POINT &p, const FLOAT radian);
FLOAT get_distance(FLOAT x, FLOAT y, FLOAT _x, FLOAT _y);



void DefenceGame::ID_Screen(HDC &hdc, RECT &rectview, SIZE &size)
{
	RECT ID_rect = { rectview.right / 2 - 100, rectview.bottom / 2, rectview.right / 2 + 100, rectview.bottom / 2 + 17 };
	TextOut(hdc, rectview.right / 2 - 105, rectview.bottom / 2 - 20, _T("ID를 입력하십시오"), _tcslen(_T("ID를 입력하십시오")));
	POINT point[4] = {
		{rectview.right / 2 - 120, rectview.bottom / 2 - 4},
		{rectview.right / 2 + 40, rectview.bottom / 2 - 4},
		{rectview.right / 2 + 40, rectview.bottom / 2 + 18},
		{rectview.right / 2 - 120, rectview.bottom / 2 + 18} };
	Polygon(hdc, point, 4);
	DrawText(hdc, ID, _tcslen(ID), &ID_rect, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
	GetTextExtentPoint(hdc, ID, _tcslen(ID), &size);
	SetCaretPos(rectview.right / 2 - 100 + size.cx, rectview.bottom / 2);

}

void DefenceGame::Game_Screen(HDC & hdc, RECT &rectview)
{
	RECT temp_rect = { 50, 10, 200, 27 };
	DrawText(hdc, _T("ID: "), _tcslen(_T("ID: ")), &temp_rect, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
	temp_rect.left += 25;
	DrawText(hdc, ID, _tcslen(ID), &temp_rect, DT_SINGLELINE | DT_VCENTER | DT_LEFT);
	temp_rect.left += 250;
	temp_rect.right += 250;
	TCHAR SCORE[10] = { 0 };
	TCHAR temp[100] = _T("Score: ");
	_itot_s(Score, SCORE, _countof(SCORE), 10);
	int j = 7;
	for (int i = 0; i < 6 - _tcslen(SCORE); i++)
	{
		temp[7 + i] = _T('0');
		j = 7 + i;
			
	}
	for (int i = 0; i < _tcslen(SCORE); i++)
		temp[j++] = SCORE[i];
	DrawText(hdc, temp, _tcslen(temp), &temp_rect, DT_SINGLELINE | DT_VCENTER | DT_LEFT);

	DrawCannon(hdc);
	DrawWall(hdc);

	for(int i = 0; i < bullet.size(); i++)
		DrawBullet(hdc, i);

	for (int i = 0; i < enemy.size(); i++)
		DrawEnemy(hdc, i);





}

void DefenceGame::Record_Screen(HDC & hdc, RECT & rectview, TCHAR name[][15], int *score)
{
	TCHAR SCORE[100] = { 0 };
	_itot_s(Score, SCORE, _countof(SCORE), 10);
	TextOut(hdc, rectview.right / 2 - 155, rectview.bottom / 2 - 20, _T("현재 플레이어 기록"), _tcslen(_T("현재 플레이어 기록")));
	TextOut(hdc, rectview.right / 2 - 10, rectview.bottom / 2 - 20, ID, _tcslen(ID));
	TextOut(hdc, rectview.right / 2 + 65, rectview.bottom / 2 - 20, SCORE, _tcslen(SCORE));


	for (int i = 0; i < 5; i++)
	{

	}


	memset(SCORE, 0, sizeof(SCORE));
	_itot_s(score[0], SCORE, _countof(SCORE), 10);
	TextOut(hdc, rectview.right / 2 - 155, rectview.bottom / 2 + 5, _T("    1위    "), _tcslen(_T("    1위    ")));
	TextOut(hdc, rectview.right / 2 - 10, rectview.bottom / 2 + 5, name[0], _tcslen(name[0]));
	TextOut(hdc, rectview.right / 2 + 65, rectview.bottom / 2 + 5, SCORE, _tcslen(SCORE));
	memset(SCORE, 0, sizeof(SCORE));
	_itot_s(score[1], SCORE, _countof(SCORE), 10);
	TextOut(hdc, rectview.right / 2 - 155, rectview.bottom / 2 + 30, _T("    2위    "), _tcslen(_T("    2위    ")));
	TextOut(hdc, rectview.right / 2 - 10, rectview.bottom / 2 + 30, name[1], _tcslen(name[1]));
	TextOut(hdc, rectview.right / 2 + 65, rectview.bottom / 2 + 30, SCORE, _tcslen(SCORE));
	memset(SCORE, 0, sizeof(SCORE));
	_itot_s(score[2], SCORE, _countof(SCORE), 10);
	TextOut(hdc, rectview.right / 2 - 155, rectview.bottom / 2 + 55, _T("    3위    "), _tcslen(_T("    3위    ")));
	TextOut(hdc, rectview.right / 2 - 10, rectview.bottom / 2 + 55, name[2], _tcslen(name[2]));
	TextOut(hdc, rectview.right / 2 + 65, rectview.bottom / 2 + 55, SCORE, _tcslen(SCORE));
	memset(SCORE, 0, sizeof(SCORE));
	_itot_s(score[3], SCORE, _countof(SCORE), 10);
	TextOut(hdc, rectview.right / 2 - 155, rectview.bottom / 2 + 80, _T("    4위    "), _tcslen(_T("    4위    ")));
	TextOut(hdc, rectview.right / 2 - 10, rectview.bottom / 2 + 80, name[3], _tcslen(name[3]));
	TextOut(hdc, rectview.right / 2 + 65, rectview.bottom / 2 + 80, SCORE, _tcslen(SCORE));
	memset(SCORE, 0, sizeof(SCORE));
	_itot_s(score[4], SCORE, _countof(SCORE), 10);
	TextOut(hdc, rectview.right / 2 - 155, rectview.bottom / 2 + 105, _T("    5위    "), _tcslen(_T("    5위    ")));
	TextOut(hdc, rectview.right / 2 - 10, rectview.bottom / 2 + 105, name[4], _tcslen(name[4]));
	TextOut(hdc, rectview.right / 2 + 65, rectview.bottom / 2 + 105, SCORE, _tcslen(SCORE));
}

void DefenceGame::Update(RECT rectview)
{

	//coillision
	for (int i = 0; i < bullet.size(); i++)
		for (int j = 0; j < enemy.size(); j++)
			if (bullet[i]->Collision(enemy[j])) Score += 100;
	for (int i = 0; i < enemy.size(); i++)
		for (int j = 0; j < wall.size(); j++)
			if (enemy[i]->Collision(wall[j])) HP--;

	//delete
	for (int i = 0; i < bullet.size(); i++)
		if (bullet[i]->get_delete() || bullet[i]->gety() < 0)
		{
			delete bullet[i];
			bullet.erase(bullet.begin() + i);
			i--;
		}

	for (int i = 0; i < enemy.size(); i++)
		if (enemy[i]->get_delete() || enemy[i]->gety() > rectview.bottom)
		{
			delete enemy[i];
			enemy.erase(enemy.begin() + i);
			i--;
		}

	for (int i = 0; i < wall.size(); i++)
		if (wall[i]->get_delete())
		{
			delete wall[i];
			wall.erase(wall.begin() + i);
			i--;
		}


	//move
	for (int i = 0; i < bullet.size(); i++)
	{
		bullet[i]->setx(bullet[i]->getx() - bullet[i]->getvx());
		bullet[i]->sety(bullet[i]->gety() - bullet[i]->getvy());
	}
	for (int i = 0; i < enemy.size(); i++)
	{
		enemy[i]->setx(enemy[i]->getx() + enemy[i]->getvx());
		enemy[i]->sety(enemy[i]->gety() + enemy[i]->getvy());
	}




}

void DefenceGame::make_Wall(RECT & rectview, FLOAT width, FLOAT height)
{
	FLOAT x = width * 0.5;
	FLOAT y = rectview.bottom - height * 0.5 - 5;
	Wall *temp;

	while (x < rectview.right)
	{
		temp = new Wall(x, y, width, height);
		wall.push_back(temp);
		x += width + 1;
	}

	HP = wall.size();
}

void DefenceGame::DrawWall(HDC hdc)
{
	int left, right, top, bottom;
	for (int i = 0; i < wall.size(); i++)
	{
		left = wall[i]->getx() - (wall[i]->getw() * 0.5);
		right = wall[i]->getx() + (wall[i]->getw() * 0.5);
		top = wall[i]->gety() - (wall[i]->geth() * 0.5);
		bottom = wall[i]->gety() + (wall[i]->geth() * 0.5);
		POINT p[4] = { {left,top}, {right, top},{right, bottom}, {left, bottom} };
		Polygon(hdc, p, 4);

	}
}

void DefenceGame::make_Cannon(RECT & rectview, FLOAT radius, FLOAT height)
{
	FLOAT x = rectview.right * 0.5;
	FLOAT y = rectview.bottom - radius - 5;

	cannon = new Cannon(x, y, radius);
}

void DefenceGame::DrawCannon(HDC hdc)
{
	POINT p2[2] = { {cannon->getx(), cannon->gety()},{cannon->getx() - cannon->getr() - 50, cannon->gety()} };
	p2[1] = Rotate(p2[0], p2[1], cannon->getradian());
	Polygon(hdc, p2, 2);

	int left, right, top, bottom;
	Ellipse(hdc, cannon->getx() - cannon->getr(), cannon->gety() - cannon->getr(), cannon->getx() + cannon->getr(), cannon->gety() + cannon->getr());

	HPEN hPen, oldPen;
	hPen = CreatePen(PS_DOT, 1, RGB(255, 255, 255));
	left = cannon->getx() - cannon->getr();
	right = cannon->getx() + cannon->getr();
	top = cannon->gety();
	bottom = cannon->gety() + cannon->getr();
	POINT p[4] = { {left,top}, {right, top},{right, bottom}, {left, bottom} };
	Polygon(hdc, p, 4);
	oldPen = (HPEN)SelectObject(hdc, hPen);
	SelectObject(hdc, oldPen);
	DeleteObject(hPen);


}

void DefenceGame::MoveCannon(bool dir)
{
	FLOAT radian = cannon->getradian();
	if (dir)
	{
		if (radian >= M_PI - M_PI / 18.0)
			return;
		else
		{
			radian += M_PI / 36.0;
			cannon->setradian(radian);
		}
	}
	else
	{
		if (radian <= M_PI / 18.0)
			return;
		else
		{
			radian -= M_PI / 36.0;
			cannon->setradian(radian);
		}
	}
}

void DefenceGame::ShootCannon(FLOAT radius)
{
	Bullet *b = new Bullet(cannon->getx() - cos(cannon->getradian()) * (cannon->getr() + 50),
					cannon->gety() - sin(cannon->getradian()) * (cannon->getr() + 50),
					radius, cannon->getradian());

	bullet.push_back(b);
}

void DefenceGame::DrawBullet(HDC hdc, int i)
{
	Ellipse(hdc, bullet[i]->getx() - bullet[i]->getr(),
		bullet[i]->gety() - bullet[i]->getr(),
		bullet[i]->getx() + bullet[i]->getr(),
		bullet[i]->gety() + bullet[i]->getr());

}

void DefenceGame::make_Enemy(RECT & rectview, FLOAT radius)
{

//	srand((unsigned int)time(NULL));
	Enemy *e = new Enemy((rand() * rand()) % (rectview.right - (2 * int(radius))) + radius, radius, 0, 1, radius);

	enemy.push_back(e);

}

void DefenceGame::DrawEnemy(HDC hdc, int i)
{
	Ellipse(hdc, enemy[i]->getx() - enemy[i]->getr(),
		enemy[i]->gety() - enemy[i]->getr(),
		enemy[i]->getx() + enemy[i]->getr(),
		enemy[i]->gety() + enemy[i]->getr());
}

void DefenceGame::Save(TCHAR (*name)[15], int *score)
{
	std::ifstream fin("Record.txt",std::ios::in | std::ios::binary);


	for (int i = 0; i < 5; i++)
	{
		fin.read((char *)name[i], sizeof(TCHAR) * 15);
		fin.read((char *)&score[i], sizeof(int));
	}
	fin.close();
	TCHAR tt[15];
	_tcscpy_s(tt, _countof(tt), ID);
	int nt = Score;

	for (int i = 0; i < 5; i++)
	{
		if (score[i] < Score)
		{
			TCHAR temp[15] = { 0 };
			_tcscpy_s(temp, _countof(temp), name[i]);
			int int_temp = score[i];

			_tcscpy_s(name[i], _countof(name[i]), ID);
			score[i] = Score;

			_tcscpy_s(ID, _countof(ID), temp);
			Score = int_temp;
		}
	}

	_tcscpy_s(ID, _countof(ID), tt);
	Score = nt;

	std::ofstream fout("Record.txt", std::ios::out | std::ios::binary);


	for(int i = 0; i < 5; i++)
	{
		fout.write((char *)name[i], sizeof(TCHAR) * 15);
		fout.write((char *)&score[i], sizeof(int));
	}

	fout.close();
}

bool Bullet::Collision(Structure *s)
{
	Enemy *e = dynamic_cast<Enemy *>(s);

	if (e)
	{
		if (e->get_delete()) return false;
		FLOAT len = get_distance(x, y, e->getx(), e->gety());
		if (radius + e->getr() >= len)
		{
			_delete = true;
			e->set_delete(true);
			return true;
		}

	}
	return false;

}

bool Enemy::Collision(Structure *s)
{

	Wall *w = dynamic_cast<Wall *>(s);

	if (w)
	{
		if (w->get_delete()) return false;
		if (y + radius >= w->gety() - w->geth() * 0.5 && x >= w->getx() - w->getw() * 0.5 && x <= w->getx() + w->getw() * 0.5)
		{
			_delete = true;
			w->set_delete(true);
			return true;
		}

	}
	return false;
}



POINT Rotate(const POINT &center, const POINT &p, const FLOAT radian)
{
	POINT temp = { p.x - center.x, p.y - center.y };

	LONG tempx = cos(radian) * temp.x - sin(radian) * temp.y;
	LONG tempy = sin(radian) * temp.x + cos(radian) * temp.y;

	return { tempx + center.x, tempy + center.y };
}

FLOAT get_distance(FLOAT x, FLOAT y, FLOAT _x, FLOAT _y)
{
	return sqrt(pow(x - _x, 2) + pow(y - _y, 2));
}
