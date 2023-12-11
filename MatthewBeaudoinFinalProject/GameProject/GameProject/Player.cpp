#include "GameCore.h"
#include "Player.h"
#include "Sprite.h"
#include "Bullet.h"

#define NDEBUG_PLAYER

IMPLEMENT_DYNAMIC_CLASS(Player)

void Player::Initialize()
{
    Component::Initialize();
    start_pos = ownerEntity->GetTransform().position;
    collider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");
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

    Vec2 dir = Vec2::Zero;
    const InputSystem& input = InputSystem::Instance();

    // Handle horizontal movement
    if (input.isKeyPressed(SDLK_LEFT) || input.isKeyPressed(SDLK_a)) {
        dir.x -= 1;
    }
    if (input.isKeyPressed(SDLK_RIGHT) || input.isKeyPressed(SDLK_d)) {
        dir.x += 1;
    }

    // Handle vertical movement
    if (input.isKeyPressed(SDLK_UP) || input.isKeyPressed(SDLK_w)) {
        dir.y -= 1;
    }
    if (input.isKeyPressed(SDLK_DOWN) || input.isKeyPressed(SDLK_s)) {
        dir.y += 1;
    }

    // Normalize the direction vector if it's not zero
    if (dir != Vec2::Zero) 
    {
        dir.Normalize();
    }

    // Move the player
    ownerEntity->GetTransform().position += dir * (400 * Time::Instance().DeltaTime());

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

    for (const auto& other: collider->OnCollisionEnter())
    {
	    if (other->GetOwner()->GetName() != "Enemy")
	    {
            continue;
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
        std::cout << "FOUND Speed" << std::endl;
        _shotSpeed = document["ShotSpeed"].ToFloat();
    }
}
