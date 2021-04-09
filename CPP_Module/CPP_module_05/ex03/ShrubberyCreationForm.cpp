#include "./ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm(const std::string & target)
    :
    Form("shrub", 45, 137),
    _target(target)
    { }

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm & shrub)
    :
    Form(shrub),
    _target(shrub._target)
    { }

ShrubberyCreationForm::~ShrubberyCreationForm() { }

ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm & shrub) {
    if (this == &shrub)
        return *this;
    Form::operator=(shrub);
    return *this;
}

void ShrubberyCreationForm::execute(Bureaucrat const & executor) const {
    Form::execute(executor);

    //파일을 만들어서 나무 이미지를 파일에 입력한다
    std::ofstream ofs(_target + "_shrubbery");

    ofs <<"                                              .       "<< std::endl;
    ofs <<"                                   .         ;        "<< std::endl;  
    ofs <<"      .              .              ;%     ;;         "<< std::endl;
    ofs <<"        ,           ,                :;%  %;          "<< std::endl;
    ofs <<"         :         ;                   :;%;'     .,   "<< std::endl;
    ofs <<",.        %;     %;            ;        %;'    ,;     "<< std::endl;
    ofs <<"  ;       ;%;  %%;        ,     %;    ;%;    ,%'      "<< std::endl;     
    ofs <<"   %;       %;%;      ,  ;       %;  ;%;   ,%;'       "<< std::endl;
    ofs <<"    ;%;      %;        ;%;        % ;%;  ,%;'         "<< std::endl;
    ofs <<"     `%;.     ;%;     %;'         `;%%;.%;'           "<< std::endl;
    ofs <<"      `:;%.    ;%%. %@;        %; ;@%;%'              "<< std::endl;    
    ofs <<"         `:%;.  :;bd%;          %;@%;'                "<< std::endl;            
    ofs <<"           `@%:.  :;%.         ;@@%;'                 "<< std::endl;    
    ofs <<"             `@%.  `;@%.      ;@@%;                   "<< std::endl;
    ofs <<"               `@%%. `@%%    ;@@%;                    "<< std::endl;
    ofs <<"                 ;@%. :@%%  %@@%;                     "<< std::endl;
    ofs <<"                   %@bd%%%bd%%:;                      "<< std::endl;    
    ofs <<"                     #@%%%%%:;;                       "<< std::endl;
    ofs <<"                     %@@%%%::;                        "<< std::endl;
    ofs <<"                     %@@@%(o);  . '                   "<< std::endl;    
    ofs <<"                     %@@@o%;:(.,'                     "<< std::endl;    
    ofs <<"                 `.. %@@@o%::;                        "<< std::endl;
    ofs <<"                    `)@@@o%::;                        "<< std::endl;
    ofs <<"                     %@@(o)::;                        "<< std::endl;
    ofs <<"                    .%@@@@%::;                        "<< std::endl;
    ofs <<"                    ;%@@@@%::;.                       "<< std::endl;
    ofs <<"                   ;%@@@@%%:;;;.                      "<< std::endl;
    ofs <<"               ...;%@@@@@%%:;;;;,..                   "<< std::endl;
}