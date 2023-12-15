#include "GameCore.h"
#include "Player.h"
#include "Sprite.h"
#include "GhostController.h"

#define NDEBUG_PLAYER

IMPLEMENT_DYNAMIC_CLASS(Player)

void Player::Initialize()
{
    Component::Initialize();
    _start_pos = ownerEntity->GetTransform().position;
    _collider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");

    for (int i = 0; i < _bulletPoolSize; i++)
    {
        _bullets.push_back(nullptr);
    }
}
void Player::Update() 
{
    if (_timeBetweenShots > 0)
    {
        _timeBetweenShots -= 1 * Time::Instance().DeltaTime();
    }

    if (InputSystem::Instance().isMouseButtonPressed(SDL_BUTTON_RIGHT))
    {
        ownerEntity->RemoveComponent(ownerEntity->GetComponent("BoxCollider"));
        _collider = nullptr;
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
        Sprite* testSprite = (Sprite*)testEntity->CreateComponent("Sprite");
        TextureAsset* testAsset = (TextureAsset*)AssetManager::Get().GetAsset("8475jni3hfji2e8fhu4");
        testEntity->CreateComponent("BoxCollider");
        Bullet* testBullet = (Bullet*)testEntity->CreateComponent("Bullet");

        testBullet->SetDirection(projectileVector);
        testBullet->SetSpeed(_shotSpeed);

        testSprite->SetTextureAsset(testAsset);

        testEntity->GetTransform().scale.x = 0.2f;
        testEntity->GetTransform().scale.y = 0.2f;

        testEntity->GetTransform().position = ownerEntity->GetTransform().position;
        

        _timeBetweenShots = _timeBetweenShotsMax;
    }

    Vec2 direction = Vec2::Zero;

    // Handle horizontal movement
    if (InputSystem::Instance().isKeyPressed(SDLK_a) && _colliding == false) {
        direction.x -= 1;
    }
    if (InputSystem::Instance().isKeyPressed(SDLK_d) && _colliding == false) {
        direction.x += 1;
    }

    // Handle vertical movement
    if (InputSystem::Instance().isKeyPressed(SDLK_w) && _colliding == false) {
        direction.y -= 1;
    }
    if (InputSystem::Instance().isKeyPressed(SDLK_s) && _colliding == false) {
        direction.y += 1;
    }

    // Normalize the direction vector if it's not zero
    if (direction != Vec2::Zero) 
    {
        direction.Normalize();
    }

    // Move the player
    ownerEntity->GetTransform().position += direction * _speed * Time::Instance().DeltaTime();

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

    if (_collider != nullptr)
    {
        // Collision for Wallsand Enemies
        for (const auto& other : _collider->OnCollisionEnter())
        {
            if (other->GetOwner()->GetName() == "Wall")
            {
                if (direction != Vec2::Zero)
                {
                    _directionOnCollision = direction;
                }
                _colliding = true;
                break;
            }
        }

        for (const auto& other : _collider->OnCollisionExit())
        {
            if (other->GetOwner()->GetName() == "Wall")
            {
                _colliding = false;
                break;
            }
        }

        if (_colliding)
        {
            ownerEntity->GetTransform().position -= _directionOnCollision * (_speed * 0.25) * Time::Instance().DeltaTime();
        }

        _previousPosition = ownerEntity->GetTransform().position;
    }
    else
    {
        _colliding = false;
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

    if (document.hasKey("BulletPoolSize"))
    {
        _bulletPoolSize = document["BulletPoolSize"].ToInt();
    }
}
