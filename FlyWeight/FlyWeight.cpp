#include <iostream>
#include <map>
#include <string>
using namespace std;

class UnitImage
{
private:
    string image;

public:
    UnitImage(const string& img) : image(img) {}

    const string& GetImage() const
    {
        return image;
    }
};

class Unit
{
protected:
    int power;
    int speed;

public:
    virtual void Show(const UnitImage& ui) const = 0;
};

class Infantry : public Unit
{
public:
    Infantry()
    {
        speed = 20;
        power = 10;
    }
    void Show(const UnitImage& ui) const override
    {
        cout << "Infantry on " << ui.GetImage() << " map; " << speed << " - speed   " << power << " - power" << endl;
    }
};

class TransportVehicle : public Unit
{
public:
    TransportVehicle()
    {
        speed = 70;
        power = 0;
    }
    void Show(const UnitImage& ui) const override
    {
        cout << "Transport vehicle on " << ui.GetImage() << " map; " << speed << " - speed   " << power << " - power" << endl;
    }
};

class HeavyGroundCombat : public Unit
{
public:
    HeavyGroundCombat()
    {
        speed = 15;
        power = 150;
    }
    void Show(const UnitImage& ui) const override
    {
        cout << "Heavy ground combat on " << ui.GetImage() << " map; " << speed << " - speed   " << power << " - power" << endl;
    }
};

class LightGroundCombat : public Unit
{
public:
    LightGroundCombat()
    {
        speed = 50;
        power = 30;
    }
    void Show(const UnitImage& ui) const override
    {
        cout << "Light ground combat on " << ui.GetImage() << " map; " << speed << " - speed   " << power << " - power" << endl;
    }
};

class Aircraft : public Unit
{
public:
    Aircraft()
    {
        speed = 300;
        power = 100;
    }
    void Show(const UnitImage& ui) const override
    {
        cout << "Aircraft on " << ui.GetImage() << " map; " << speed << " - speed   " << power << " - power" << endl;
    }
};

class UnitFactory
{
private:
    map<char, Unit*> characters;
    UnitImage* location;

public:
    UnitFactory(const string& loc) : location(new UnitImage(loc)) {}

    ~UnitFactory()
    {
        delete location;
        for (auto& pair : characters)
            delete pair.second;
    }

    Unit* GetUnit(char key)
    {
        Unit* unit = characters[key];
        if (!unit)
        {
            switch (key)
            {
            case '1':
                unit = new Infantry();
                break;
            case '2':
                unit = new TransportVehicle();
                break;
            case '3':
                unit = new HeavyGroundCombat();
                break;
            case '4':
                unit = new LightGroundCombat();
                break;
            case '5':
                unit = new Aircraft();
                break;
            }
            characters[key] = unit;
        }
        return unit;
    }
};

int main()
{
    string order = "1345123";
    string loc = "desert";

    UnitFactory unitFactory(loc);
    UnitImage location(loc);

    for (char key : order)
    {
        Unit* unit = unitFactory.GetUnit(key);
        unit->Show(location);
    }
    return 0;
}
