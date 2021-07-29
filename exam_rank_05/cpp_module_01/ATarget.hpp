#ifndef ATARGET_HPP
# define ATARGET_HPP

# include <iostream>
# include <string>

class ASpell;
# include "ASpell.hpp"

class ATarget
{
private:
    std::string type;

public:
    ATarget();
    ATarget(std::string const &type);
    ATarget(ATarget const other);
    ATarget &operator=(ATarget const &other);
    virtual ~ATarget();

    std::string const &getType() const;

    virtual ATarget const *clone() const = 0;

    void getHitBySpell(ASpell const *aspell) const;
};

#endif