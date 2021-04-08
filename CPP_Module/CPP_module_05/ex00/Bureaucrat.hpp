#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <iostream>
#include <string>
#include <stdexcept>

class Bureaucrat {
    private:
        const std::string _name;
        int _grade; // 1 ~ 150
        Bureaucrat();
    
    public:
        Bureaucrat(const std::string &name, int grade);
        Bureaucrat(const Bureaucrat & b);
        Bureaucrat& operator=(const Bureaucrat & b);
        virtual ~Bureaucrat();

        const std::string getName() const;
        int getGrade() const;
        void incGrade();
        void decGrade();

        class GradeTooHighException : public std::exception {
            public:
                virtual const char* what() const throw();
        };
        class GradeTooLowException : public std::exception {
            public:
                virtual const char* what() const throw();
        };
};

std::ostream& operator<<(std::ostream& os, const Bureaucrat & b);

#endif