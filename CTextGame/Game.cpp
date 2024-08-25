#include "Game.h"

#include "Renderer.h"

#include <Windows.h>

Enitiy Player;
Enitiy Monsters[MAX_MONSTER_COUNT];
Bullet bullets[MAX_BULLET_COUNT];

void LoadPlayerData()
{
	Player.IsViaild = true;

	Player.Hp = 10;
	Player.Att = 1;

	Player.Position = { 5 ,5 };
}

void LoadMonsterData()
{

}

bool PlayerInput()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		if (Player.Position.x == 0)
			return false;

		--Player.Position.x;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		if (Player.Position.x + 1 == MAP_WITDH_SIZE - 1)
		{
			return false;
		}

		++Player.Position.x;
	}

	if (GetAsyncKeyState(VK_SPACE))
	{
		for (auto& bullet : bullets)
		{
			if ( bullet.IsViaild == false )
			{
				uvector2 bulletSpawnPosition = Player.Position;
				bulletSpawnPosition.y -= 1;

				bullet.Position = bulletSpawnPosition;

				bullet.IsViaild = true;
			}
		}
		return true;
	}

	return false;
}

int PlayerPorcess()
{

	return 0;
}

int PlayerRender()
{
	CopyDataToRendBuffer(Player.Position, "@");

	return 0;
}

int BulletProcess()
{
	for (unsigned int bulletIndex = 0; bulletIndex < MAX_BULLET_COUNT; bulletIndex++)
	{
		Bullet& bullet = bullets[bulletIndex];

		// 현재 활성된 총알만 체크
		if (bullet.IsViaild == false )
		{
			continue;
		}
		
		// 몬스터와 충돌 처리
		for (unsigned int monsterIndex = 0; monsterIndex < MAX_MONSTER_COUNT; monsterIndex++)
		{
			if (Monsters[monsterIndex].IsViaild == false)
			{
				continue;
			}

			if (Colision(bullet.Position, Monsters[monsterIndex].Position) == true)
			{
				BulletHit(Monsters[monsterIndex], bullet);
			}
		}

		BulletMove(bullet);
	}


	return 0;
}

int BulletRender()
{
	for (unsigned int bulletIndex = 0; bulletIndex < MAX_BULLET_COUNT; bulletIndex++)
	{
		Bullet& bullet = bullets[bulletIndex];

		if (bullet.IsViaild == true)
		{
			CopyDataToRendBuffer(bullet.Position, '^');
		}

	}

	return 0;
}

// 총알이 이동 후 맵 밖으로 나가면 제거
void BulletMove(Bullet& bullet)
{
	bullet.Position.y -= 1;

	if (bullet.Position.y == -1)
	{
		bullet.IsViaild = false;
	}
}

void BulletHit(Enitiy& monster, const Bullet& bullet)
{
	monster.Hp -= bullet.Att;

	if (monster.Hp <= 0)
	{
		monster.IsViaild = false;
	}
}