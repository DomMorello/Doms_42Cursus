#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <stdexcept>
#include "./Bureaucrat.hpp"

class Bureaucrat;

class Form {
    private:
        const std::string _name;
        bool _signed;
        const int _gradeToSign;
        const int _gradeToExec;
        Form();

    public:
        Form(std::string name, int gradeToSign, int gradeToExec);
        Form(const Form & form);
        Form& operator=(const Form & form);
        virtual ~Form();

        const std::string getName() const;
        bool getSigned() const;
        int getGradeToSign() const;
        int getGradeToExec() const;
        void beSigned(const Bureaucrat & b);
        virtual void execute(Bureaucrat const & executor) const = 0;

        class GradeTooHighException : public std::exception {
            public:
                virtual const char* what() const throw();
        };

        class GradeTooLowException : public std::exception {
            public:
                virtual const char* what() const throw();
        };
};

std::ostream& operator<<(std::ostream& os, const Form & form);

#endif