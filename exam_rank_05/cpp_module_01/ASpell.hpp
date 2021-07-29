#ifndef ASPELL_HPP
# define ASPELL_HPP

# include <iostream>
# include <string>

class ATarget;
# include "ATarget.hpp"

class ASpell
{
private:
    std::string name;
    std::string effects;

public:
    ASpell();
    ASpell(std::string const &name, std::string const &effects);
    ASpell(ASpell const &other);
    ASpell &operator=(ASpell const &other);
    virtual ~ASpell();

    std::string const &getName() const;
    std::string const &getEffects() const;

    virtual ASpell const *clone() const = 0;

    void launch(ATarget const &atarget) const;
};

#ifndef