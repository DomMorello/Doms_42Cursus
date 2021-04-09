#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "Form.hpp"
#include <cstdlib>

class RobotomyRequestForm : public Form {
    private:
        const std::string _target;
        RobotomyRequestForm();

    public:
        RobotomyRequestForm(const std::string & target);
        RobotomyRequestForm(const RobotomyRequestForm & robot);
        ~RobotomyRequestForm();
        RobotomyRequestForm& operator=(const RobotomyRequestForm & robot);

        void execute(Bureaucrat const & executor) const;
};

#endif