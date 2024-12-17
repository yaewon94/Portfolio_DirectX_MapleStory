#pragma once

// TODO : 커스텀 태그 추가하면 반영되게 구현
enum OBJECT_TAG : byte
{
	TAG_DEFAULT = 1,
	TAG_PLAYER = TAG_DEFAULT << 1,
	TAG_PLAYER_SKILL = TAG_PLAYER << 1,
	TAG_MONSTER = TAG_PLAYER_SKILL << 1,
	TAG_MONSTER_SKILL = TAG_MONSTER << 1,
	TAG_GROUND = TAG_MONSTER_SKILL << 1
};

static OBJECT_TAG& operator<<=(OBJECT_TAG& tag, UINT val)
{
	return tag = (OBJECT_TAG)(tag << val);
}

typedef UINT OBJECT_TAGS; // OBJECT_TAGS & (1 << OBJECT_TAG) 연산 용도