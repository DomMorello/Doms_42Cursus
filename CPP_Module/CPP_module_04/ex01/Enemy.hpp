#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <iostream>
#include <string>

class Enemy {
    protected:
        int HP;
        std::string type;

    public:
        Enemy();
        Enemy(int hp, std::string const & type);
        Enemy(const Enemy & enemy);
        virtual ~Enemy();
        Enemy& operator=(const Enemy & enemy);

        const std::string getType() const;
        int getHP() const;
        virtual void takeDamage(int damage);
};

#endif