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
    //���Կ����� ���������� ����ȴ�
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
    //_inventory�� ��ü�� ������ ���� �����Ѵ�.
    for (int i = 0; i < 4; i++)
    {
        if (_inventory[i])
        {
            delete _inventory[i];
            _inventory[i] = NULL;
        }
    }
    //character�� �ִ� inventory ��ü���� clone�ؼ� ���� ���縦 �Ѵ�
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
    //���ο� ����� ������ ������ _cur_idx�� ������Ų��
    /* TODO: �Ȱ��� ���⸦ ������ ������ �� ���°ž�? */
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