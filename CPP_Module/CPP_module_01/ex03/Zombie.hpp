#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

#include <iostream>
#include <string>

const std::string c_names[10] = {
    "random_name1",
    "random_name2",
    "random_name3",
    "random_name4",
    "random_name5",
    "random_name6",
    "random_name7",
    "random_name8",
    "random_name9",
    "random_name10",
};

class Zombie {
    public:
        Zombie();
        Zombie(std::string _name, std::string type = "unknown type");
        void announce();
        void setName(std::string name);
        void setType(std::string type);

    private:
        std::string name;
        std::string type;
};

#endif