#ifndef DUMMY_HPP
# define DUMMY_HPP

# include "ATarget.hpp"

class Dummy : public ATarget
{
private:
    Dummy(Dummy const &other);
    Dummy &operator=(Dummy const &other);

public:
    Dummy();
    ~Dummy();

    virtual Dummy *clone() const;
};

#endif