#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include<algorithm> 
#include <fstream>
#include <climits>

using namespace std;
using std::cout;
using std::cin;


class weapon {
public:
    string _weaponName;
    int _powerRating = 0;
    float _powerConsumption = 0;
    void getDescription() {
        cout << _weaponName << ", " << _powerRating << ", " << std::setprecision(1)<< _powerConsumption
        << endl;
    }
    weapon() {}
    weapon(string weaponName, int powerRating, float powerConsumption)
    {
        _weaponName = weaponName;
        _powerRating = powerRating;
        _powerConsumption = powerConsumption;
    }
};

class ship
{
public:
    string _class = " ";
    string _name = " ";
    int _shieldCapacity = 0;
    int _length = 0;
    float _maxWarpSpeed = 0;
    vector<weapon> _inventory;
    void getDescription() {
        int totalFirepower = 0;
        cout << "Name: " << _name << endl;
        cout << "Class: " << _class << endl;
        cout << "Length: " << _length << endl;
        cout << "Shield capacity: " << _shieldCapacity << endl;
        cout << "Maximum Warp: " << std::setprecision(1)<<_maxWarpSpeed<< endl;
        cout << "Armaments: " << endl;
        if (_inventory.size() > 0) {
            for (unsigned int i = 0; i < _inventory.size(); i++) {
                _inventory[i].getDescription();
                totalFirepower += _inventory[i]._powerRating;
            }
            cout << "Total firepower: " << totalFirepower << endl << endl;
        }
        else { cout << "Unarmed" << endl; }
    };
    int getTotalFirePower() {
        int totalFirePower = 0;
        for (unsigned int i = 0; i < _inventory.size(); i++) {
            totalFirePower += _inventory[i]._powerRating;
        }
        return totalFirePower;
    }

    ship()
    {
        //  cout << "Default Constructor called" << endl;
    }

    ship(string name, string weaponClass, int shieldCapacity, int length, float maxWarpSpeed, vector<weapon> inventory)
    {
        _class = weaponClass;
        _name = name;
        _shieldCapacity = shieldCapacity;
        _length = length;
        _maxWarpSpeed = maxWarpSpeed;
        _inventory = inventory;
    }

    int getStrongestWeapon() {
        int highestWPower = 0;
        for (unsigned int i = 0; i < _inventory.size(); i++) {
            if (_inventory[i]._powerRating > highestWPower) {
                highestWPower = _inventory[i]._powerRating;
            }
        }
        return highestWPower;
    }
};

void readData(string fileName, vector<ship>& allShips) {
    ifstream filePath(fileName, ios::in | ios::binary);
    if (filePath.is_open())
    {
        vector<weapon> inventory;
        int count = 0;
        filePath.read((char*)&count, 4);
        for (int j = 0; j < count; ++j) {

            int nameLength;
            filePath.read((char*)&nameLength, 4);
            char* temp = new char[nameLength];
            filePath.read(temp, nameLength);
            string name = temp;
            delete[] temp;
            int weaponClassLength = 0;
            filePath.read((char*)&weaponClassLength, 4);
            temp = new char[weaponClassLength];
            filePath.read(temp, weaponClassLength);
            string weaponClass = temp;
            delete[] temp;
            short length = 0;
            filePath.read((char*)&length, 2);
            int shieldCapacity = 0;
            filePath.read((char*)&shieldCapacity, 4);
            float maxWarpSpeed = 0;
            filePath.read((char*)&maxWarpSpeed, 4);
            int weaponCount = 0;
            filePath.read((char*)&weaponCount, 4);
            for (unsigned short i = 0; i < weaponCount; ++i) {
                int wNameLength = 0;
                int pRating = 0;
                float pConsumption = 0;
                filePath.read((char*)&wNameLength, 4);
                char* buffer = new char[wNameLength];
                filePath.read(buffer, wNameLength);
                string wName = buffer;
                filePath.read((char*)&pRating, 4);
                filePath.read((char*)&pConsumption, 4);
                inventory.push_back(weapon(wName, pRating, pConsumption));
                delete[] buffer;
                buffer = nullptr;
            }
            allShips.push_back(ship(name, weaponClass, shieldCapacity, length, maxWarpSpeed, inventory));
            inventory.clear();
        }
        // 
        filePath.close();
        // fileData.clear();
    }

}
int main()
{
    vector<ship> ships;
    cout << std::fixed << setprecision(2);
    cout << "Which file(s) to open?\n";
    cout << "1. friendlyships.shp" << endl;
    cout << "2. enemyships.shp" << endl;
    cout << "3. Both files" << endl;
    int option;
    cin >> option;
    switch (option)
    {

    case 1: {
        string fileName = "friendlyships.shp";
        readData(fileName, ships);
        break; }
    case 2: {
        string fileName = "enemyships.shp";
        readData(fileName, ships);
        break; }
    case 3: {
        string fileName = "friendlyships.shp";
        readData(fileName, ships);
        fileName = "enemyships.shp";
        readData(fileName, ships);
        break; }
    default: cout << "Invalid Choice";
    }

    cout << "1. Print all ships" << endl;
    cout << "2. Starship with the strongest weapon" << endl;
    cout << "3. Strongest starship overall" << endl;
    cout << "4. Weakest ship (ignoring unarmed)" << endl;
    cout << "5. Unarmed ships" << endl;

    int choice;
    cin >> choice;
    cin.get();
    switch (choice)
    {
    case 1:
    {
        for (unsigned short i = 0; i < ships.size(); i++) {
            ships[i].getDescription();
        }
    }
    break;
    case 2: {
        int highestWeaponPower = 0;
        int highestWeaponPowerIndex = 0;
        for (unsigned short i = 0; i < ships.size(); i++) {
            if (ships[i].getStrongestWeapon() > highestWeaponPower) {
                highestWeaponPower = ships[i].getStrongestWeapon();
                highestWeaponPowerIndex = i;
            }
        }
        ships[highestWeaponPowerIndex].getDescription();
    }break;
    case 3: {
        int highestFirePower = 0;
        int highestFirePowerIndex = 0;
        for (unsigned short i = 0; i < ships.size(); i++) {
            if (ships[i].getTotalFirePower() > highestFirePower) {
                highestFirePower = ships[i].getTotalFirePower();
                highestFirePowerIndex = i;
            }
        }
        ships[highestFirePowerIndex].getDescription();
    }break;
    case 4: {
        int lowestFirePower = INT_MAX;
        int lowestFirePowerIndex = 0;
        for (unsigned short i = 0; i < ships.size(); i++) {
            if (ships[i].getTotalFirePower() < lowestFirePower && ships[i].getTotalFirePower() != 0) {
                lowestFirePower = ships[i].getTotalFirePower();
                lowestFirePowerIndex = i;
            }
        }
        ships[lowestFirePowerIndex].getDescription();
    }break;
    case 5: { for (unsigned short i = 0; i < ships.size(); i++) {
        if (ships[i].getTotalFirePower() == 0) {
            ships[i].getDescription();
        }
    }}break;
    default: return 0;

        return 0;
    }
}