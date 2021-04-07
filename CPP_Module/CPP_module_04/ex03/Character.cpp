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
    //대입연산자 오버로딩이 실행된다
    *this = character;
}

Character::~Character() {
    for (int i = 0; i < 4; i++)
    {
        if (_inventory[i] != NULL)
        {
            delete _inventory[i];
            _inventory[i] = NULL;
        }
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
    //똑같은 객체가 이미 inventory안에 있으면 아무 행동 하지 않는다.
    for (int i = 0; i < _cur_idx; i++)
        if (_inventory[i] == m)
            return ;
    //현재 넣으려고 하는 inventory가 자리가 있어야 함.
    if (m && _inventory[_cur_idx] == NULL && _cur_idx < 4)
    { 
        _inventory[_cur_idx] = m;
        _cur_idx++;
        //새로운 무기룰 장착할 때마다 _cur_idx를 증가시킨다
    }
}

void Character::unequip(int idx) {
    if (idx < 0 || idx > 4 || _inventory[idx] == NULL)
        return ;
    //_cur_idx 를 정확하게 위치하게 하기 위해서
    //제거하려고 하는 객체를 맨 뒤로 옮겨준다.
    while (idx < 3)
    {
        _inventory[idx] = _inventory[idx + 1];
        idx++;
    }
    _inventory[idx] = NULL;
    _cur_idx--; //마지막 객체의 위치로 돌려주기 위해 1을 뺀다.
}

void Character::use(int idx, ICharacter& target) {
    if (idx < 0 || idx > 4)
        return ;
    if (_inventory[idx])
        _inventory[idx]->use(target);
}