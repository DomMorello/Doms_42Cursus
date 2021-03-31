#include "./FragTrap.hpp"
#include "./ScavTrap.hpp"
#include "./ClapTrap.hpp"

int main()
{
    std::cout << "@@@@@@@@@@@@@@  start  @@@@@@@@@@@@@@" << std::endl;
    FragTrap dong;   //����Ʈ������
    FragTrap morello("morello");
    dong = morello; //���� ������ �����ε�
    FragTrap lee(dong); //���������

    FragTrap domas("domas");

    //domas�� morello�� melee�� ������
    morello.takeDamage(domas.meleeAttack(morello.getName()));
    //morello�� domas�� range�� ������
    domas.takeDamage(morello.rangedAttack(domas.getName()));
    morello.printStat();
    domas.printStat();

    //domas�� morello�� ���� ���������� ��.
    morello.takeDamage(domas.vaulthunter_dot_exe(morello.getName()));
    domas.takeDamage(morello.vaulthunter_dot_exe(domas.getName()));
    morello.takeDamage(domas.vaulthunter_dot_exe(morello.getName()));
    domas.takeDamage(morello.vaulthunter_dot_exe(domas.getName()));
    morello.printStat();
    domas.printStat();

    //ȸ���ϱ�
    morello.beRepaired(50);
    domas.beRepaired(30);
    morello.beRepaired(100);    //������ ȸ���ϱ�
    morello.printStat();
    domas.printStat();

    //domas ���̱�
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