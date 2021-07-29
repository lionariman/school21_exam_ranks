#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# include <string>

class Warlock
{
private:
    Warlock() {}
    Warlock(Warlock const &other);
    Warlock &operator=(Warlock const &other);
    
    std::string name;
    std::string title;

public:
    Warlock(std::string const &name, std::string const &title);
    ~Warlock();

    void setName(std::string const &name);
    void setTitle(std::string const &title);

    std::string const &getName() const;
    std::string const &getTitle() const;

    void introduce() const;
};

#endif