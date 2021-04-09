#include "./RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm(const std::string & target)
    :
    Form("robot", 72, 45),
    _target(target)
    { }

RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm & robot)
    :
    Form(robot),
    _target(robot._target)
    { }

RobotomyRequestForm::~RobotomyRequestForm() { }

RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm & robot) {
    if (this == &robot)
        return *this;
    Form::operator=(robot);
    return *this;
}

void RobotomyRequestForm::execute(Bureaucrat const & executor) const {
    srand(clock());
    Form::execute(executor);

    std::cout << "ddddrrrrriliiing nooooooiiiseeeeee...." << std::endl;
    //50% 확률로 성공 실패 나누기
    if (rand() % 2)
        std::cout << _target << " has been robotomized succesfully." << std::endl;
    else
        std::cout << _target << " robotomization has failed." << std::endl;
}