#include "./FragTrap.hpp"
#include "./ScavTrap.hpp"

int main()
{
    FragTrap dong;   //디폴트생성자
    FragTrap morello("morello");
    dong = morello; //대입 연산자 오버로딩
    FragTrap lee(dong); //복사생성자

    FragTrap domas("domas");

    //domas가 morello를 melee로 공격함
    morello.takeDamage(domas.meleeAttack(morello.getName()));
    //morello가 domas를 range로 공격함
    domas.takeDamage(morello.rangedAttack(domas.getName()));
    morello.printStat();
    domas.printStat();

    //domas와 morello가 서로 랜덤공격을 함.
    morello.takeDamage(domas.vaulthunter_dot_exe(morello.getName()));
    domas.takeDamage(morello.vaulthunter_dot_exe(domas.getName()));
    morello.takeDamage(domas.vaulthunter_dot_exe(morello.getName()));
    domas.takeDamage(morello.vaulthunter_dot_exe(domas.getName()));
    morello.printStat();
    domas.printStat();

    //회복하기
    morello.beRepaired(50);
    domas.beRepaired(30);
    morello.beRepaired(100);    //완전히 회복하기
    morello.printStat();
    domas.printStat();

    //domas 죽이기
    domas.takeDamage(morello.rangedAttack(domas.getName()));
    domas.takeDamage(morello.rangedAttack(domas.getName()));
    domas.takeDamage(morello.rangedAttack(domas.getName()));
    domas.takeDamage(morello.rangedAttack(domas.getName()));
    domas.takeDamage(morello.rangedAttack(domas.getName()));
    domas.takeDamage(morello.rangedAttack(domas.getName()));
    domas.printStat();

    ScavTrap scavTrap("doorMan");
    morello.takeDamage(scavTrap.meleeAttack(morello.getName()));
    morello.takeDamage(scavTrap.rangedAttack(morello.getName()));
    morello.printStat();
    scavTrap.printStat();
    scavTrap.challengeNewcomer();
    scavTrap.beRepaired(20);
    scavTrap.takeDamage(morello.meleeAttack(scavTrap.getName()));
    scavTrap.printStat();

    return 0;
}