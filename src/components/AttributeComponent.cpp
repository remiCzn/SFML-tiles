#include "AttributeComponent.hpp"

AttributeComponent::AttributeComponent(unsigned level)
{
    this->level = level;
    this->exp = 0;
    this->expNext = static_cast<unsigned>((50 / 3) * pow(this->level, 3));
    this->attributePoints = 2;

    this->vitality = 1;
    this->strength = 1;
    this->dexterity = 1;
    this->agility = 1;
    this->intelligence = 1;

    this->updateLevel();
    this->updateStats(true);
}

AttributeComponent::~AttributeComponent()
{
}

std::string AttributeComponent::debugPrint() const
{
    std::stringstream ss;
    ss << "Level: " << this->level << "\n"
       << "Exp: " << this->exp << "\n"
       << "Exp next: " << this->expNext << "\n"
       << "Attp: " << this->attributePoints << "\n"
       << "HP/HPMax: " << this->hp << "/" << this->hpMax;

    return ss.str();
}

void AttributeComponent::gainExp(const unsigned exp)
{
    this->exp += exp;
    this->updateLevel();
}

void AttributeComponent::updateStats(const bool reset)
{
    this->hpMax = this->vitality * 5 + this->vitality + this->strength / 2 + this->intelligence / 5;
    this->damageMin = this->strength * 2 + this->strength / 4 + this->intelligence / 5;
    this->damageMax = this->strength * 2 + this->strength / 2 + this->intelligence / 5;
    this->accuracy = this->dexterity * 5 + this->dexterity / 2 + this->intelligence / 5;
    this->defence = this->agility * 2 + this->agility / 4 + this->intelligence / 5;
    this->luck = this->intelligence * 2 + this->intelligence / 5;

    if (reset)
    {
        this->hp = this->hpMax;
    }
}

void AttributeComponent::updateLevel()
{
    while (this->exp >= this->expNext)
    {
        ++this->level;
        this->exp -= this->expNext;
        this->expNext = static_cast<unsigned>((50 / 3) * pow(this->level, 3));
        ++this->attributePoints;
    }
}

void AttributeComponent::update()
{
    this->updateLevel();
}

void AttributeComponent::loseHp(const unsigned hp)
{
    this->hp -= hp;
    if (this->hp < 0)
        this->hp = 0;
}

void AttributeComponent::gainHp(const unsigned hp)
{
    this->hp += hp;
    if (this->hp > this->hpMax)
        this->hp = this->hpMax;
}