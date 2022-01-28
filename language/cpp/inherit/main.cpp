#include <iostream>
#include <string>

class Base
{
public:
    Base() 
    {
        std::cout << "Base constructor" << std::endl;
    }
    Base(const char* name) : name(name) 
    {
        std::cout << "Base constructor : " << name << std::endl;
    }

    virtual void print()
    {
        std::cout << "Base : " << this->name << std::endl;
    }
protected:
    std::string name;
};


class Derive : public Base
{
protected:
    std::string parent = "Base";
public:
    Derive() : Base() 
    {
        std::cout << "Derive constructor" << std::endl;
    }
    Derive(const char* name) : Base(name) 
    {
        std::cout << "Derive constructor : " << name << std::endl;
    }  

    void print() override
    {
        std::cout << "Derive : " << this->name << ", parent : " << this->parent << std::endl;
    }
};

int main() 
{
    Base b1("base 1");
    Derive d1("derive 1");
    Derive *pD1 = static_cast<Derive*>(&d1);
    Derive *pD2 = dynamic_cast<Derive*>(&b1);

    pD1->print();
    pD2->print();
    return 0;
}
