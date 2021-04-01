#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <string>

class ClapTrap {
    public:
        ClapTrap();
        ClapTrap(const std::string name);
        ClapTrap(const ClapTrap& clapTrap);
        virtual ~ClapTrap();
        ClapTrap& operator=(const ClapTrap& clapTrap);
        
        unsigned int rangedAttack(std::string const & target);
        unsigned int meleeAttack(std::string const & target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
        std::string getName(void);
        void printStat(void);

    //처음에 이 부분을 습관적으로 private으로 했었는데 이렇게 하면 자식클래스에서
    //이 맴버변수에 접근할 수가 없다. 그래서 맴버변수를 출력할 때 printStat함수를
    //자식 클래스에서 오버라이딩하지 않는 한 부모의 맴버변수를 출력하는
    //그래서 전부 0으로 초기화된 값이 나오는 오류가 있었다.
    //protected로 바꿈으로써 부모의 맴버변수만 사용하면 출력하는데도 이상이 없다.
    protected:
        int hit;
        int maxHit;
        int energy;
        int maxEnergy;
        int level;
        std::string name;
        unsigned int meleeDamage;
        unsigned int rangedDamage;
        unsigned int armorReduction;
};

#endif