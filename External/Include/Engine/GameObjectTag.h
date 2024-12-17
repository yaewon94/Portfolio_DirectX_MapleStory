#pragma once

// TODO : Ŀ���� �±� �߰��ϸ� �ݿ��ǰ� ����
enum OBJECT_TAG : byte
{
	TAG_DEFAULT, 
	TAG_PLAYER, TAG_PLAYER_SKILL, 
	TAG_MONSTER, 
	TAG_GROUND,
	TAG_END
};

static OBJECT_TAG& operator++(OBJECT_TAG& tag)
{
	if (tag == TAG_END) assert(nullptr);
	tag = (OBJECT_TAG)(tag + 1);
	return tag;
}

typedef UINT OBJECT_TAGS; // OBJECT_TAGS & (1 << OBJECT_TAG) ���� �뵵