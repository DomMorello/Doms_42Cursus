#include "./Enemy.hpp"

Enemy::Enemy() : HP(0), type("unknown") { }

Enemy::Enemy(int hp, std::string const & type)
    :
    HP(hp),
    type(type)
{ }

Enemy::Enemy(const Enemy & enemy) {
    *this = enemy;
}

Enemy::~Enemy() { }

Enemy& Enemy::operator=(const Enemy & enemy) {
    HP = enemy.HP;
    type = enemy.type;
    return *this;
}

const std::string Enemy::getType() const {
    return type;
}

int Enemy::getHP() const {
    return HP;
}

void Enemy::takeDamage(int damage) {
    HP -= damage;
    if (HP < 0)
        HP = 0;
}