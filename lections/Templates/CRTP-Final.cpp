template <typename FriendClass>
class MakeFinal
{
    friend FriendClass;
private:
    MakeFinal() {}
};

class Final1 : virtual MakeFinal<Final1>
{
public:
    Final1() {}
};


class Final2 : virtual MakeFinal<Final2>
{
public:
    Final2() {}
};

/*
class Derived : public Final1
{
public:
    Derived() {}
};
*/
