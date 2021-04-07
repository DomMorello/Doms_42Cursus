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
    //���Կ����� �����ε��� ����ȴ�
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
    //�Ȱ��� ��ü�� �̹� inventory�ȿ� ������ �ƹ� �ൿ ���� �ʴ´�.
    for (int i = 0; i < _cur_idx; i++)
        if (_inventory[i] == m)
            return ;
    //���� �������� �ϴ� inventory�� �ڸ��� �־�� ��.
    if (m && _inventory[_cur_idx] == NULL && _cur_idx < 4)
    { 
        _inventory[_cur_idx] = m;
        _cur_idx++;
        //���ο� ����� ������ ������ _cur_idx�� ������Ų��
    }
}

void Character::unequip(int idx) {
    if (idx < 0 || idx > 4 || _inventory[idx] == NULL)
        return ;
    //_cur_idx �� ��Ȯ�ϰ� ��ġ�ϰ� �ϱ� ���ؼ�
    //�����Ϸ��� �ϴ� ��ü�� �� �ڷ� �Ű��ش�.
    while (idx < 3)
    {
        _inventory[idx] = _inventory[idx + 1];
        idx++;
    }
    _inventory[idx] = NULL;
    _cur_idx--; //������ ��ü�� ��ġ�� �����ֱ� ���� 1�� ����.
}

void Character::use(int idx, ICharacter& target) {
    if (idx < 0 || idx > 4)
        return ;
    if (_inventory[idx])
        _inventory[idx]->use(target);
}