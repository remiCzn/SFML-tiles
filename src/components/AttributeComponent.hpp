#ifndef ATTRIBUTE_COMPONENT_H
#define ATTRIBUTE_COMPONENT_H

#include "../headers/headers.hpp"

class AttributeComponent
{
public:
    unsigned level;
    unsigned exp;
    unsigned expNext;
    unsigned attributePoints;

    int vitality;
    int strength;
    int dexterity;
    int agility;
    int intelligence;

    int hp;
    int hpMax;
    int damageMin;
    int damageMax;
    int accuracy;
    int defence;
    int luck;

    AttributeComponent(unsigned level);
    virtual ~AttributeComponent();

    std::string debugPrint() const;

    void gainExp(const unsigned exp);
    void updateStats(const bool reset);
    void updateLevel();

    void update();
};

#endif