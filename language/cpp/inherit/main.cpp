#include <iostream>
#include <string>
#include <typeinfo>

class Base
{
public:
    Base() 
    {
        std::cout << "Base constructor" << std::endl;
    }

    virtual ~Base() 
    {
        std::cout << "Base destructor" << std::endl;
    }

    virtual void print()
    {
        std::cout << "Base print" << std::endl;
    }
    
    // int age;
    // bool is[5];
    // bool is1;
};


class Derive : public Base
{
public:
    // int date;

    Derive() : Base() 
    {
        std::cout << "Derive constructor" << std::endl;
    }

    ~Derive() 
    {
        std::cout << "Derive destructor" << std::endl;
    }

    void print() override
    {
        std::cout << "Derive print" << std::endl;
    }
};

int main() 
{
    Derive nDerive1;
    Base& rBaseFromDerive = nDerive1;
    // Derive& rDeriveFromBaseFromDerive = rBaseFromDerive;

    Derive* pDerive1 = new Derive;
    Base* pBaseFromDerive = dynamic_cast<Base*>(pDerive1);
    pBaseFromDerive->~Base();
    delete pBaseFromDerive;
    // pBaseFromDerive->print();
    // Derive *pD1 = static_cast<Derive*>(&nDerive1);
    // Derive *pDerive1 = dynamic_cast<Derive*>(&nBase1);
    // Derive *pDerive2 = dynamic_cast<Derive*>(&rBaseFromBase);
    // Derive *pDerive3 = dynamic_cast<Derive*>(&rBaseFromDerive);


    // std::cout << "same" << std::endl;

    // std::cout << sizeof(Base) << std::endl;
    // std::cout << sizeof(Derive) << std::endl;
    // std::cout << sizeof(void*) << std::endl;

    // std::cout << "rBaseFromDerive : " << typeid(rBaseFromDerive).name() << std::endl;
    // std::cout << "pDerive1 : " << typeid(pDerive1).name() << std::endl;
    // std::cout << "pDerive1 : " << typeid(pDerive1).name() << std::endl;
    // std::cout << "pDerive2 : " << typeid(pDerive2).name() << std::endl;
    // std::cout << "pDerive3 : " << typeid(pDerive3).name() << std::endl;
    // std::cout << "rBaseFromBase : " << typeid(rBaseFromBase).name() << std::endl;
    // std::cout << "nBase1 : " << typeid(nBase1).name() << std::endl;
    // std::cout << "rBaseFromDerive : " << typeid(rBaseFromDerive).name() << std::endl;

    return 0;
}
