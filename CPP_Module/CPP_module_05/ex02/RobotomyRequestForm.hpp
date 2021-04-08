#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include "Form.hpp"

class RobotomyRequestForm : public Form {
    private:
        RobotomyRequestForm();

    public:
        RobotomyRequestForm(const RobotomyRequestForm & robot);
        ~RobotomyRequestForm();
        RobotomyRequestForm& operator=(const RobotomyRequestForm & shrub);

        
};

#endif