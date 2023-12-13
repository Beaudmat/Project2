#include "GameCore.h"
#include "MapGenerator.h"
#include "Sprite.h"

IMPLEMENT_DYNAMIC_CLASS(MapGenerator);

void MapGenerator::Initialize()
{

}

void MapGenerator::Update()
{

}

void MapGenerator::Load(json::JSON& document)
{
	if (document.hasKey("LevelFile"))
	{
		std::ifstream inputStream(document["LevelFile"].ToString());
		std::string str((std::istreambuf_iterator<char>(inputStream)), std::istreambuf_iterator<char>());
		json::JSON node = json::JSON::Load(str);

		if (node.hasKey("Tiles"))
		{
			_tiles = node["Tiles"];
		}
		if (node.hasKey("MapTexture"))
		{
			_mapFileGUID = GetHashCode(node["MapTexture"].ToString().c_str());
		}
	}

	if (_tiles.length() > 0 && _mapFileGUID != 0)
	{
		//What index in the array we are at
		int count = 0;

		//Position for the next Tile to be generated at
		float x = 22.4;
		float y = 22.4;

		//Runs through all the rows for Y
		for (int z = 0; z < 16; z++)
		{
			//Runs through all the rows for X
			for (int i = 0; i < 16; i++)
			{
				//Creates a new Entity and sets its position and scale information
				Entity* newTile = ownerEntity->GetParentScene()->CreateEntity();
				newTile->GetTransform().position.x = x;
				newTile->GetTransform().position.y = y;
				newTile->GetTransform().Scale(Vec2(1.4, 1.4));

				//Increments X so the next tile is at the right X position
				x += 44.7;

				//Creates a sprite component on the new entity and gives it the Dungeon texture
				Sprite* sprite = (Sprite*)newTile->CreateComponent("Sprite");
				sprite->SetTextureAsset((TextureAsset*)AssetManager::Get().GetAsset(_mapFileGUID));

				/*
				* Pulls the TileID from the array and removes 1. Tiled was providing tile id's that were one too high.
				*/
				float tileId = _tiles[count++].ToInt() - 1;

				//Performs math to grab the X and Y coordinates from the TileID
				float textureCorX = ((int)tileId % 20);
				float textureCorY = tileId - textureCorX;
				textureCorX *= 32;
				textureCorY = (textureCorY / 20) * 32;

				//Sets the sprite rect so it only displays the texture at the given coordinates
				SDL_Rect tileRect = { textureCorX, textureCorY, 32.0, 32.0 };
				sprite->SetSourceRect(tileRect);
			}
			//Resets X since we are going into a new X row
			x = 22.4;
			y += 44.7;
		}
	}
}