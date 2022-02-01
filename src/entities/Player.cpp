#include "Player.hpp"
#include "../headers/headers.hpp"

void Player::initVariables()
{
    this->attacking = false;
    this->attack_cooldown = 0.f;

    this->direction = DOWN;

    this->rect.setFillColor(sf::Color::Green);
    this->rect.setOutlineColor(sf::Color::Blue);
    this->rect.setOutlineThickness(-1.f);
    this->rect.setSize(sf::Vector2f(16.f, 32.f));
    this->rect.setPosition(24.f, 16.f);
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
    this->animationComponent->addAnimation("IDLE_DOWN", new AnimatedSprite(this->sprite, *texture_sheet, idle_anim_timer, 0, 0, 5, 64, 64));
    this->animationComponent->addAnimation("IDLE_UP", new AnimatedSprite(this->sprite, *texture_sheet, idle_anim_timer, 0, 1, 5, 64, 64));
    this->animationComponent->addAnimation("IDLE_LEFT", new AnimatedSprite(this->sprite, *texture_sheet, idle_anim_timer, 0, 2, 5, 64, 64));
    this->animationComponent->addAnimation("IDLE_RIGHT", new AnimatedSprite(this->sprite, *texture_sheet, idle_anim_timer, 0, 3, 5, 64, 64));

    float walk_anim_timer = 5.f;
    this->animationComponent->addAnimation("WALK_DOWN", new AnimatedSprite(this->sprite, *texture_sheet, walk_anim_timer, 0, 4, 5, 64, 64));
    this->animationComponent->addAnimation("WALK_UP", new AnimatedSprite(this->sprite, *texture_sheet, walk_anim_timer, 0, 5, 5, 64, 64));
    this->animationComponent->addAnimation("WALK_LEFT", new AnimatedSprite(this->sprite, *texture_sheet, walk_anim_timer, 0, 6, 5, 64, 64));
    this->animationComponent->addAnimation("WALK_RIGHT", new AnimatedSprite(this->sprite, *texture_sheet, walk_anim_timer, 0, 7, 5, 64, 64));

    float attack_anim_timer = 6.f;
    this->animationComponent->addAnimation("ATTACK_DOWN", new AnimatedSprite(this->sprite, *texture_sheet, attack_anim_timer, 0, 8, 4, 64, 64));
    this->animationComponent->addAnimation("ATTACK_UP", new AnimatedSprite(this->sprite, *texture_sheet, attack_anim_timer, 0, 9, 4, 64, 64));
    this->animationComponent->addAnimation("ATTACK_LEFT", new AnimatedSprite(this->sprite, *texture_sheet, attack_anim_timer, 0, 10, 4, 64, 64));
    this->animationComponent->addAnimation("ATTACK_RIGHT", new AnimatedSprite(this->sprite, *texture_sheet, attack_anim_timer, 0, 11, 4, 64, 64));

    std::vector<sf::IntRect> steps_right = {};
    steps_right.push_back(sf::IntRect(24, 16, 36, 32));
    steps_right.push_back(sf::IntRect(24, 16, 36, 32));
    steps_right.push_back(sf::IntRect(24, 16, 36, 32));
    steps_right.push_back(sf::IntRect(24, 16, 16, 32));
    this->animationComponent->addAnimation("ATTACK_RIGHT_HITBOX", new AnimatedHitbox(this->rect, this->sprite, attack_anim_timer, steps_right));

    std::vector<sf::IntRect> steps_left = {};
    steps_left.push_back(sf::IntRect(24, 16, 36, 32));
    steps_left.push_back(sf::IntRect(24, 16, 36, 32));
    steps_left.push_back(sf::IntRect(24, 16, 36, 32));
    steps_left.push_back(sf::IntRect(24, 16, 16, 32));
    this->animationComponent->addAnimation("ATTACK_LEFT_HITBOX", new AnimatedHitbox(this->rect, this->sprite, attack_anim_timer, steps_left));

    std::vector<sf::IntRect> steps_up = {};
    steps_up.push_back(sf::IntRect(24, 16, 36, 32));
    steps_up.push_back(sf::IntRect(24, 16, 36, 32));
    steps_up.push_back(sf::IntRect(24, 16, 36, 32));
    steps_up.push_back(sf::IntRect(24, 16, 16, 32));
    this->animationComponent->addAnimation("ATTACK_UP_HITBOX", new AnimatedHitbox(this->rect, this->sprite, attack_anim_timer, steps_up));

    std::vector<sf::IntRect> steps_down = {};
    steps_down.push_back(sf::IntRect(24, 16, 36, 32));
    steps_down.push_back(sf::IntRect(24, 16, 36, 32));
    steps_down.push_back(sf::IntRect(24, 16, 36, 32));
    steps_down.push_back(sf::IntRect(24, 16, 16, 32));
    this->animationComponent->addAnimation("ATTACK_DOWN_HITBOX", new AnimatedHitbox(this->rect, this->sprite, attack_anim_timer, steps_down));


    std::cout << "Animation initialized" << std::endl;
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
    //this->rect.setPosition(this->sprite->getPosition());
    std::cout << this->sprite->getPosition().x << " " << this->sprite->getPosition().y << std::endl;
    std::cout << this->rect.getPosition().x << " " << this->rect.getPosition().y << " " << this->rect.getSize().x << " " << this->rect.getSize().y << std::endl;
}

void Player::updateAnimation(const float &dt)
{
    if (attacking)
    {
        switch (this->direction)
        {
        case DOWN:
            this->playAttackAnimation("ATTACK_DOWN", "ATTACK_DOWN_HITBOX", dt);
            break;
        case LEFT:
            this->playAttackAnimation("ATTACK_LEFT", "ATTACK_LEFT_HITBOX", dt);
            break;
        case RIGHT:
            this->playAttackAnimation("ATTACK_RIGHT", "ATTACK_RIGHT_HITBOX", dt);
            break;
        case UP:
            this->playAttackAnimation("ATTACK_UP", "ATTACK_UP_HITBOX", dt);
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

void Player::playAttackAnimation(std::string sprite_key, std::string hitbox_key, const float& dt)
{
    if (!this->animationComponent->isDone(sprite_key) && !this->animationComponent->isDone(hitbox_key)) {
        bool playing_sprite = this->animationComponent->play(sprite_key, dt);
        bool playing_hitbox = this->animationComponent->play(hitbox_key, dt, true);
        if (playing_sprite && playing_hitbox) {
            this->attacking = false;
            this->attack_cooldown = 0.f;
        }
    }
    else {
        this->animationComponent->reset(sprite_key);
        this->animationComponent->reset(hitbox_key);
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

    target.draw(this->rect);
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
