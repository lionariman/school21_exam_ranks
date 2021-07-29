#ifndef FWOOSH_HPP
# define FWOOSH_HPP

# include "ASpell.hpp"

class Fwoosh : public ASpell
{
private:
    Fwoosh(Fwoosh const &other);
    Fwoosh &operator=(Fwoosh const &other);

public:
    Fwoosh();
    ~Fwoosh();

    virtual Fwoosh *clone() const;
};

#endif