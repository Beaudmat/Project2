#include "GameCore.h"
#include "Player.h"
#include "Sprite.h"
#include "Bullet.h"
#include "GhostController.h"

#define NDEBUG_PLAYER

IMPLEMENT_DYNAMIC_CLASS(Player)

void Player::Initialize()
{
    Component::Initialize();
    _start_pos = ownerEntity->GetTransform().position;
    _collider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");
}
void Player::Update() 
{

    if (_timeBetweenShots > 0)
    {
        _timeBetweenShots -= 1 * Time::Instance().DeltaTime();
    }

    if (InputSystem::Instance().isMouseButtonPressed(SDL_BUTTON_LEFT) && _timeBetweenShots <= 0)
    {
        int x, y;
        SDL_GetMouseState(&x, &y);

        Vec2 player = ownerEntity->GetTransform().position;
        Vec2* clickPoint = new Vec2(x, y);

        Vec2 projectileVector = (*clickPoint) - player;
        projectileVector.Normalize();

        Entity* testEntity = ownerEntity->GetParentScene()->CreateEntity();
        Bullet* testBullet = (Bullet*)testEntity->CreateComponent("Bullet");
        testBullet->SetDirection(projectileVector);
        testBullet->SetSpeed(_shotSpeed);
        Sprite* testSprite = (Sprite*)testEntity->CreateComponent("Sprite");
        TextureAsset* testAsset = (TextureAsset*)AssetManager::Get().GetAsset("8475jni3hfji2e8fhu4");

        testSprite->SetTextureAsset(testAsset);

        testEntity->GetTransform().scale.x = 0.2f;
        testEntity->GetTransform().scale.y = 0.2f;

        testEntity->GetTransform().position = ownerEntity->GetTransform().position;
        

        _timeBetweenShots = _timeBetweenShotsMax;
    }

    Vec2 direction = Vec2::Zero;

    // Handle horizontal movement
    if (InputSystem::Instance().isKeyPressed(SDLK_a)) {
        direction.x -= 1;
    }
    if (InputSystem::Instance().isKeyPressed(SDLK_d)) {
        direction.x += 1;
    }

    // Handle vertical movement
    if (InputSystem::Instance().isKeyPressed(SDLK_w)) {
        direction.y -= 1;
    }
    if (InputSystem::Instance().isKeyPressed(SDLK_s)) {
        direction.y += 1;
    }

    // Normalize the direction vector if it's not zero
    if (direction != Vec2::Zero) 
    {
        direction.Normalize();
    }

    // Move the player
    ownerEntity->GetTransform().position += direction * _speed * Time::Instance().DeltaTime();
    //ownerEntity->GetTransform().position += _direction * _speed * Time::Instance().DeltaTime();

    //Makes sure the player doesn't leave the bounds of the map
    if (ownerEntity->GetTransform().position.x < 35)
    {
        ownerEntity->GetTransform().position.x = 35;
    }
    if (ownerEntity->GetTransform().position.y < 35)
    {
        ownerEntity->GetTransform().position.y = 35;
    }
    if (ownerEntity->GetTransform().position.x > 900)
    {
        ownerEntity->GetTransform().position.x = 900;
    }
    if (ownerEntity->GetTransform().position.y > 675)
    {
        ownerEntity->GetTransform().position.y = 675;
    }

    for (const auto& other: _collider->OnCollisionEnter())
    {
        GhostController* enemy = (GhostController*)other->GetOwner()->GetComponent("GhostController");
	    if (enemy == NULL)
	    {
            std::cout << "WE TOUCHING LE NON ENEMY" << std::endl;
            ownerEntity->GetTransform().position -= direction * _speed * 200 * Time::Instance().DeltaTime();

            continue;
        }
        else
        {
            std::cout << "WE TOUCHING LE ENEMY" << std::endl;
        }
    }
}
void Player::Load(json::JSON& document)
{
    if (document.hasKey("TimeBetweenShots"))
    {
        _timeBetweenShotsMax = document["TimeBetweenShots"].ToFloat();
    }

    if (document.hasKey("ShotSpeed"))
    {
        _shotSpeed = document["ShotSpeed"].ToFloat();
    }

    if (document.hasKey("Speed"))
    {
        _speed = document["Speed"].ToFloat();
    }
}
