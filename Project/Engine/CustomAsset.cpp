#include "pch.h"
#include "CustomAsset.h"

CustomAsset::CustomAsset(const string& Key, const string& relativePath) 
	: Asset(Key, relativePath)
{
}

CustomAsset::~CustomAsset()
{
}