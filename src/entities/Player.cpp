#include "Player.hpp"
#include "../headers/headers.hpp"

void Player::initVariables() {
    this->attacking = false;
    this->attack_cooldown = 0.f;

    this->direction = DOWN;
}

Player::Player(float x, float y, sf::Texture* texture_sheet)
{
    this->initVariables();

    //this->createSprite(texture);
    //Change according to the sprite scale
    this->sprite->setScale(sf::Vector2f(2.f, 2.f));
    //
    this->setPosition(x,y);
    // this->sprite->setOrigin(sf::Vector2f(this->sprite->getGlobalBounds().width / 2.f, this->sprite->getGlobalBounds().height / 2.f));

    this->createHitboxComponent(48.f, 32.f, 32.f, 64.f);
    this->createMovementComponent(300.f, 15.f, 7.f);
    this->createAnimationComponent(*texture_sheet);

    float idle_anim_timer = 8.f;
    this->animationComponent->addAnimation("IDLE_DOWN", idle_anim_timer, 4, 0, 0, 64, 64);
    this->animationComponent->addAnimation("IDLE_UP", idle_anim_timer, 4, 0, 1, 64, 64);
    this->animationComponent->addAnimation("IDLE_LEFT", idle_anim_timer, 4, 0, 2, 64, 64);
    this->animationComponent->addAnimation("IDLE_RIGHT", idle_anim_timer, 4, 0, 3, 64, 64);

    float walk_anim_timer = 5.f;
    this->animationComponent->addAnimation("WALK_DOWN", walk_anim_timer , 5, 0, 4, 64, 64);
    this->animationComponent->addAnimation("WALK_UP", walk_anim_timer, 5, 0, 5, 64, 64);
    this->animationComponent->addAnimation("WALK_LEFT", walk_anim_timer, 5, 0, 6, 64, 64);
    this->animationComponent->addAnimation("WALK_RIGHT", walk_anim_timer, 5, 0, 7, 64, 64);

    float attack_anim_timer = 6.f;
    this->animationComponent->addAnimation("ATTACK_DOWN", attack_anim_timer, 2,0,8,64,64);
    this->animationComponent->addAnimation("ATTACK_UP", attack_anim_timer, 2,0,9,64,64);
    this->animationComponent->addAnimation("ATTACK_LEFT", attack_anim_timer, 2,0,10,64,64);
    this->animationComponent->addAnimation("ATTACK_RIGHT", attack_anim_timer, 2,0,11,64,64);
}

Player::~Player()
{
}

void Player::update(const float& dt)
{
    this->movementComponent->update(dt);
    this->updateAttack(dt);
    this->playAnimations(dt);
    this->hitboxComponent->update();
}

void Player::playAnimations(const float& dt)
{
    if(attacking)
    {
        switch (this->direction)
        {
        case DOWN:
            if(this->animationComponent->play("ATTACK_DOWN", dt, true))
            {
                this->attacking = false;
                this->attack_cooldown = 0.f;
            }
            break;
        case LEFT:
            if(this->animationComponent->play("ATTACK_LEFT", dt, true))
            {
                this->attacking = false;
                this->attack_cooldown = 0.f;
            }
            break;
        case RIGHT:
            if(this->animationComponent->play("ATTACK_RIGHT", dt, true))
            {
                this->attacking = false;
                this->attack_cooldown = 0.f;
            }
            break;
        case UP:
            if(this->animationComponent->play("ATTACK_UP", dt, true))
            {
                this->attacking = false;
                this->attack_cooldown = 0.f;
            }
            break;
        
        default:
            break;
        }        
    }
    else {
        switch (this->movementComponent->getState())
        {
        case IDLE_DOWN:
            this->animationComponent->play("IDLE_DOWN",dt);
            this->direction = DOWN;
            break;
        case IDLE_UP:
            this->animationComponent->play("IDLE_UP",dt);
            this->direction = UP;
            break;
        case IDLE_LEFT:
            this->animationComponent->play("IDLE_LEFT",dt);
            this->direction = LEFT;
            break;
        case IDLE_RIGHT:
            this->animationComponent->play("IDLE_RIGHT",dt);
            this->direction = RIGHT;
            break;
        case MOVING_DOWN:
            this->animationComponent->play("WALK_DOWN",dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
            this->direction = DOWN;
            break;
        case MOVING_LEFT:
            this->animationComponent->play("WALK_LEFT",dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
            this->direction = LEFT;
            break;
        case MOVING_RIGHT:
            this->animationComponent->play("WALK_RIGHT",dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
            this->direction = RIGHT;
            break;
        case MOVING_UP:
            this->animationComponent->play("WALK_UP",dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
            this->direction = UP;
            break;
        
        default:
            this->animationComponent->play("IDLE_DOWN",dt);
            break;
        }
    }
}

void Player::updateAttack(const float& dt)
{
    this->attack_cooldown += dt;
    if((sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) && this->attack_cooldown > 0.3f)
    {
        this->attacking = true;
    }
}

void Player::render(sf::RenderTarget& target) {
    target.draw(*this->sprite);

    this->hitboxComponent->render(target);
}