// @file: Player.cpp
//
// @brief: Player moves around using the WASD Key. Collision will prevent them from walking through walls or enemies.
// The collision system prevents the player from moving and forces them backwards based on their last direction until
// they exit the collider. The player can also shoot using the left mouse button. Direction will be determined based
// on where on the screen the mouse is.
//
// @author: Matthew Beaudoin
// @date: 2023-12-15

#include "GameCore.h"
#include "Player.h"
#include "Sprite.h"
#include "GhostController.h"

#define NDEBUG_PLAYER

IMPLEMENT_DYNAMIC_CLASS(Player)

void Player::Initialize()
{
    //Grabs onto the start position for later use
    _start_pos = ownerEntity->GetTransform().position;

    //Grabs the BoxCollider for later reference
    _collider = (BoxCollider*)ownerEntity->GetComponent("BoxCollider");
}
void Player::Update() 
{
    //Timer tracking time between shots
    if (_timeBetweenShots > 0)
    {
        _timeBetweenShots -= 1 * Time::Instance().DeltaTime();
    }

    //If the player clicks the left mouse button and the timer has passed
    if (InputSystem::Instance().isMouseButtonPressed(SDL_BUTTON_LEFT) && _timeBetweenShots <= 0)
    {
        //Grabs the mouse position on screen
        int x, y;
        SDL_GetMouseState(&x, &y);
        Vec2 clickPoint = Vec2(x, y);

        //Calculates the direction the fire shot needs to move in
        Vec2 projectileVector = clickPoint - ownerEntity->GetTransform().position;
        projectileVector.Normalize();

        //Creates a new entity and sets information
        Entity* newEntity = ownerEntity->GetParentScene()->CreateEntity();
        newEntity->GetTransform().Scale(Vec2(0.2f, 0.2f));
        newEntity->GetTransform().position = ownerEntity->GetTransform().position;
        newEntity->SetName("PlayerBullet");

        //Creates a new sprite component for the entity
        Sprite* bulletSprite = (Sprite*)newEntity->CreateComponent("Sprite");
        TextureAsset* bulletAsset = (TextureAsset*)AssetManager::Get().GetAsset("8475jni3hfji2e8fhu4");
        bulletSprite->SetTextureAsset(bulletAsset);

        //Creates a new boxcollider for the entity
        newEntity->CreateComponent("BoxCollider");

        //Creates a new bullet component for the entity
        Bullet* testBullet = (Bullet*)newEntity->CreateComponent("Bullet");
        testBullet->SetDirection(projectileVector);
        testBullet->SetSpeed(_shotSpeed); 

        //Resets the shot timer
        _timeBetweenShots = _timeBetweenShotsMax;
    }

    //Direction the player will move in
    Vec2 direction = Vec2::Zero;

    // Handles horizontal movement
    if (InputSystem::Instance().isKeyPressed(SDLK_a) && _colliding == false) {
        direction.x -= 1;
    }
    if (InputSystem::Instance().isKeyPressed(SDLK_d) && _colliding == false) {
        direction.x += 1;
    }

    // Handles vertical movement
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

    //Checks if the player collided with a wall or enemy
    for (const auto& other : _collider->OnCollisionEnter())
    {
        if (other->GetOwner()->GetName() == "Wall" || other->GetOwner()->GetName() == "Enemy")
        {
            //Direction on collision will be used to move the player back. It won't accept if its a zero direction
            if (direction != Vec2::Zero)
            {
                _directionOnCollision = direction;
            }

            //If were colliding it locks down player movement
            _colliding = true;
            break;
        }
    }

    //If the player has exited the collision it lets the player regain control of their movement
    for (const auto& other : _collider->OnCollisionExit())
    {
        if (other->GetOwner()->GetName() == "Wall" || other->GetOwner()->GetName() == "Enemy")
        {
            _colliding = false;
            _collidingTimer = 2;
            break;
        }
    }

    //Makes sure the player doesn't get stuck backing up
    if (_collidingTimer <= 0)
    {
        _colliding = false;
        _collidingTimer = 2;
    }

    //Moves the player backwards from their last previously good direction vector if they are colliding
    if (_colliding)
    {
        _collidingTimer -= 1 * Time::Instance().DeltaTime();
        ownerEntity->GetTransform().position -= _directionOnCollision * (_speed * 0.25) * Time::Instance().DeltaTime();
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
