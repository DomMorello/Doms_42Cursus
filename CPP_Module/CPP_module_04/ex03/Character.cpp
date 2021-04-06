#include "Character.hpp"

Character::Character() : _name("unkonwn"), _cur_idx(0) {
    for (int i = 0; i < 4; i++)
        _inventory[i] = NULL;
}

Character::Character(const std::string name) : _name(name), _cur_idx(0) {
    for (int i = 0; i < 4; i++)
        _inventory[i] = NULL;
}

Character::Character(const Character & character) {
    //대입연산자 오버러딩이 실행된다
    *this = character;
}

Character::~Character() {
    for (int i = 0; i < 4; i++)
    {
        delete _inventory[i];
        _inventory[i] = NULL;
    }
}

Character& Character::operator=(const Character & character) {
    this->_name = character.getName();
    this->_cur_idx = character._cur_idx;
    //_inventory에 객체가 있으면 먼저 삭제한다.
    for (int i = 0; i < 4; i++)
    {
        if (_inventory[i])
        {
            delete _inventory[i];
            _inventory[i] = NULL;
        }
    }
    //character에 있는 inventory 객체들을 clone해서 깊은 복사를 한다
    for (int i = 0; i < 4; i++)
    {
        if (character._inventory[i] != NULL)
            _inventory[i] = character._inventory[i]->clone();
    }
    return *this;
}

std::string const & Character::getName() const {
    return _name;
}

void Character::equip(AMateria* m) {
    //새로운 무기룰 장착할 때마다 _cur_idx를 증가시킨다
    /* TODO: 똑같은 무기를 여러개 장착할 순 없는거야? */
    if (m && _inventory[_cur_idx] == NULL && _inventory[_cur_idx] != m)
    { 
        _inventory[_cur_idx] = m;
        _cur_idx++;
    }
}

void Character::unequip(int idx) {

}

void Character::use(int idx, ICharacter& target) {
    if (idx < 0 || idx > 4)
        return ;
    if (_inventory[idx])
        _inventory[idx]->use(target);
}