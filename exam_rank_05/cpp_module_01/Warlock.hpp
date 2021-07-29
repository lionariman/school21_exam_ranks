#ifndef WARLOCK_HPP
# define WARLOCK_HPP

# include <iostream>
# include <string>

class ASpell;
# include "ASpell.hpp"
class ATarget;
# include "ATarget.hpp"

class Warlock
{
private:
    Warlock() {}
    Warlock(Warlock const &other);
    Warlock &operator=(Warlock const &other);
    
    std::string name;
    std::string title;

    std::vector<ASpell *> spells;

public:
    Warlock(std::string const &name, std::string const &title);
    ~Warlock();

    void setName(std::string const &name);
    void setTitle(std::string const &title);

    std::string const &getName() const;
    std::string const &getTitle() const;

    void setTitle(std::string const &title);

    void introduce() const;

    void learnSpell(ASpell *aspell);
    void forgetSpell(std::string const &spells_name);
    void launchSpell(std::string const &spells_name, ATarget const &atarget);


};

#endif