#include "MateriaSource.hpp"

MateriaSource::MateriaSource() : _cur_idx(0) {
    for (int i = 0; i < 4; i++)
        _materia[i] = NULL;
}

MateriaSource::MateriaSource(const MateriaSource & source) {
    *this = source;
}

MateriaSource::~MateriaSource() {
    for (int i = 0; i < _cur_idx; i++)
    {
        if (_materia[i])
        {
            delete _materia[i];
            _materia[i] = NULL;
        }
    }
}

MateriaSource& MateriaSource::operator=(const MateriaSource & source) {
    _cur_idx = source._cur_idx;
    //_materia에 객체가 있으면 먼저 삭제한다.
    for (int i = 0; i < _cur_idx; i++)
    {
        if (_materia[i])
        {
            delete _materia[i];
            _materia[i] = NULL;
        }
    }
    //source 있는 _materia 객체들을 clone해서 깊은 복사를 한다
    for (int i = 0; i < 4; i++)
    {
        if (source._materia[i] != NULL)
            _materia[i] = source._materia[i]->clone();
    }
    return *this;
}

void MateriaSource::learnMateria(AMateria* m) {
    if (m != NULL && _cur_idx <= 3)
    {
        _materia[_cur_idx] = m; //여기서 clone하면 메모리누수
        _cur_idx++;
    }
}

AMateria* MateriaSource::createMateria(std::string const & type) {
    for (int i = 0; i < _cur_idx; i++)
        if (_materia[i]->getType() == type)
            return _materia[i]->clone();
    return NULL;
}