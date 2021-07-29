#include "Warlock.hpp"

Warlock::Warlock(std::string const &name, std::string const &title)
{
    this->name = name;
    this->title = title;
    std::cout << this->name << ": This looks like another boring day.\n";
}

Warlock::~Warlock()
{
    std::cout << this->name << ": My job here is done!\n";
}

void Warlock::setName(std::string const &name)
{
    this->name = name;
}

void Warlock::setTitle(std::string const &title)
{
    this->title = title;
}

std::string const &Warlock::getName() const
{
    return this->name;
}

std::string const &Warlock::getTitle() const
{
    return this->title;
}

void Warlock::introduce() const
{
    std::cout << this->name << ": I am " << this->name << ", " << this->title << "!\n";
}

void Warlock::learnSpell(ASpell *aspell)
{
    std::vector<ASpell *>::iterator it;
    
    it = this->spells.begin();
    for (; it != this->spells.end(); it++)
    {
        if (!aspell->getName().compare(*it.getName()))
            return ;
    }
    this->spells.push_back(aspell);
}

void Warlock::forgetSpell(std::string const &spells_name)
{
    std::vector<ASpell *>::iterator it;

    it = this->spells.begin();
    for (; it != this->spells.end(); it++)
    {
        if (!spells_name.compare(*it.getName()))
            this->spells.erase(it);
    }
}

void Warlock::launchSpell(std::string const &spells_name, ATarget const &atarget)
{
    std::vector<ASpell *>::iterator it;

    it = this->spells.begin();
    for (; it != this->spells.end(); it++)
    {
        if (!spells_name.compare(*it.getName()))
            *it.launch(atarget);
    }
}