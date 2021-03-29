#include "./FragTrap.hpp"

int main()
{
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

    return 0;
}