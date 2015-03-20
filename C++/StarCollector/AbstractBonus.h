#ifndef ABSTRACTBONUS_H
    #define ABSTRACTBONUS_H

class Player;

class Bonus : public VisualCollide
{
public:
    virtual void apply(Player *player){};
};
#endif // ABSTRACTBONUS_H
