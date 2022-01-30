#include "Player.hpp"
#include "../headers/headers.hpp"

void Player::initVariables()
{
    this->attacking = false;
    this->attack_cooldown = 0.f;

    this->direction = DOWN;
}

Player::Player(float x, float y, sf::Texture *texture_sheet)
{
    this->initVariables();

    //this->createSprite(texture);
    //Change according to the sprite scale
    //this->sprite->setScale(sf::Vector2f(2.f, 2.f));
    //
    this->setPosition(x, y);
    // this->sprite->setOrigin(sf::Vector2f(this->sprite->getGlobalBounds().width / 2.f, this->sprite->getGlobalBounds().height / 2.f));

    this->createHitboxComponent(24.f, 16.f, 16.f, 32.f);
    this->createMovementComponent(200.f, 15.f, 10.f);
    this->createAnimationComponent();
    this->createAttributeComponent(1);

    float idle_anim_timer = 8.f;
    this->animationComponent->addAnimation("IDLE_DOWN", new AnimatedSprite(this->sprite, *texture_sheet, idle_anim_timer, 0, 0, 4, 64, 64));
    this->animationComponent->addAnimation("IDLE_UP", new AnimatedSprite(this->sprite, *texture_sheet, idle_anim_timer, 0, 1, 4, 64, 64));
    this->animationComponent->addAnimation("IDLE_LEFT", new AnimatedSprite(this->sprite, *texture_sheet, idle_anim_timer, 0, 2, 4, 64, 64));
    this->animationComponent->addAnimation("IDLE_RIGHT", new AnimatedSprite(this->sprite, *texture_sheet, idle_anim_timer, 0, 3, 4, 64, 64));

    float walk_anim_timer = 5.f;
    this->animationComponent->addAnimation("WALK_DOWN", new AnimatedSprite(this->sprite, *texture_sheet, walk_anim_timer, 0, 4, 5, 64, 64));
    this->animationComponent->addAnimation("WALK_UP", new AnimatedSprite(this->sprite, *texture_sheet, walk_anim_timer, 0, 5, 5, 64, 64));
    this->animationComponent->addAnimation("WALK_LEFT", new AnimatedSprite(this->sprite, *texture_sheet, walk_anim_timer, 0, 6, 5, 64, 64));
    this->animationComponent->addAnimation("WALK_RIGHT", new AnimatedSprite(this->sprite, *texture_sheet, walk_anim_timer, 0, 7, 5, 64, 64));

    float attack_anim_timer = 6.f;
    this->animationComponent->addAnimation("ATTACK_DOWN", new AnimatedSprite(this->sprite, *texture_sheet, attack_anim_timer, 0, 8, 2, 64, 64));
    this->animationComponent->addAnimation("ATTACK_UP", new AnimatedSprite(this->sprite, *texture_sheet, attack_anim_timer, 0, 9, 2, 64, 64));
    this->animationComponent->addAnimation("ATTACK_LEFT", new AnimatedSprite(this->sprite, *texture_sheet, attack_anim_timer, 0, 10, 2, 64, 64));
    this->animationComponent->addAnimation("ATTACK_RIGHT", new AnimatedSprite(this->sprite, *texture_sheet, attack_anim_timer, 0, 11, 2, 64, 64));
}

Player::~Player()
{
}

void Player::update(const float &dt)
{
    this->movementComponent->update(dt);
    this->updateAttack(dt);
    this->updateAnimation(dt);
    this->hitboxComponent->update();
}

void Player::updateAnimation(const float &dt)
{    
    if (attacking)
    {
        switch (this->direction)
        {
        case DOWN:
            if (this->animationComponent->play("ATTACK_DOWN", dt, true))
            {
                this->attacking = false;
                this->attack_cooldown = 0.f;
            }
            break;
        case LEFT:
            if (this->animationComponent->play("ATTACK_LEFT", dt, true))
            {
                this->attacking = false;
                this->attack_cooldown = 0.f;
            }
            break;
        case RIGHT:
            if (this->animationComponent->play("ATTACK_RIGHT", dt, true))
            {
                this->attacking = false;
                this->attack_cooldown = 0.f;
            }
            break;
        case UP:
            if (this->animationComponent->play("ATTACK_UP", dt, true))
            {
                this->attacking = false;
                this->attack_cooldown = 0.f;
            }
            break;

        default:
            break;
        }
    }
    else
    {
        switch (this->movementComponent->getState())
        {
        case IDLE_DOWN:
            this->animationComponent->play("IDLE_DOWN", dt);
            this->direction = DOWN;
            break;
        case IDLE_UP:
            this->animationComponent->play("IDLE_UP", dt);
            this->direction = UP;
            break;
        case IDLE_LEFT:
            this->animationComponent->play("IDLE_LEFT", dt);
            this->direction = LEFT;
            break;
        case IDLE_RIGHT:
            this->animationComponent->play("IDLE_RIGHT", dt);
            this->direction = RIGHT;
            break;
        case MOVING_DOWN:
            this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
            this->direction = DOWN;
            break;
        case MOVING_LEFT:
            this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
            this->direction = LEFT;
            break;
        case MOVING_RIGHT:
            this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
            this->direction = RIGHT;
            break;
        case MOVING_UP:
            this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
            this->direction = UP;
            break;

        default:
            this->animationComponent->play("IDLE_DOWN", dt);
            break;
        }
    }
}

void Player::updateAttack(const float &dt)
{
    this->attack_cooldown += dt;
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::R) || sf::Mouse::isButtonPressed(sf::Mouse::Left)) && this->attack_cooldown > 0.3f)
    {
        this->attacking = true;
    }
}

void Player::render(sf::RenderTarget &target, bool debugMode)
{
    target.draw(*this->sprite);

    this->hitboxComponent->render(target, debugMode);
}

AttributeComponent *Player::getAttributeComponent()
{
    return this->attributeComponent;
}

void Player::loseHP(const int hp)
{
    this->attributeComponent->loseHp(hp);
}

void Player::gainHP(const int hp)
{
    this->attributeComponent->gainHp(hp);
}

void Player::gainExp(const int exp)
{
    this->attributeComponent->gainExp(exp);
}
