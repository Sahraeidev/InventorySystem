#include <iostream>
#include <string.h>
#include <vector>


enum TIPO {
  ARMOR ,
  WEAPON ,
  CONSUMABLE
};

class Item{
	public:
	Item(float w,std::string n,TIPO t) : weight(w), name(n), type(t){}
	

	std::string GetTypeName() {
    switch(type) {
        case ARMOR: return "Armor";
        case WEAPON: return "Weapon";
        case CONSUMABLE: return "Consumable";
        default: return "Unknown";
    }
	} 
	inline std::string GetName()  
	{
		return name;
	}
	inline float GetWeight() {
		return weight;
	}

	private:
	TIPO type;
	std::string name;
	float weight;
};

class Inventory{
	public:
	Inventory(float mw) : maxWeight(mw) {
		currentWeight = 0.f;
	}
	
	inline float GetMaxWeight() { return maxWeight;}

	bool AddItem(Item& ItemToAdd)
	{
		if(currentWeight + ItemToAdd.GetWeight() > maxWeight )
		{
			return false;
		}

		Items.push_back(ItemToAdd);
		currentWeight+=ItemToAdd.GetWeight();
		return true;
	}

	bool RemoveItem(std::string NameToRemove)
	{
		for(int i = 0; i < Items.size(); i++)
		{
			if(Items[i].GetName() == NameToRemove)
			{
				currentWeight-=Items[i].GetWeight();
				Items.erase(Items.begin() + i);
				return true;
			}
		}

		return false;
	}

	void DisplayItem()
	{
		if(Items.empty()) {
    std::cout << "Inventory is empty" << std::endl;
    return;
}
		std::cout << "===INVENTORY===" << std::endl;
		std::cout << "*CURRENT WEIGHT : " << currentWeight << std::endl;
		std::cout << "*MAX WEIGHT : " << maxWeight << std::endl;
		std::cout << "===ITEMS===" << std::endl;
		for(int i = 0 ; i < Items.size() ; i++)
		{
			std::cout << i+1 <<  " | " << Items[i].GetName() << std::endl;
			std::cout << "	weight : " << Items[i].GetWeight() << std::endl;
			std::cout << "	type : " << Items[i].GetTypeName() << std::endl;
		}
	}

	float FindItem(std::string Name)
	{
		for(int i = 0; i < Items.size(); i++)
		{
			if(Items[i].GetName() == Name)
			{
				return Items[i].GetWeight();
			}
		}
		return -1;
	}

	private:
	float currentWeight;
	float maxWeight;
	std::vector<Item> Items;
};

class Character{
	public:

	Character(std::string n,float hp) : Health(hp),Name(n),MaxHealth(hp) {
		bIsAlive = true;
	}

	bool TakeDamage(float Damage){
		Health-=Damage;
		if(Health <= 0 )
		{
			bIsAlive = false;
			Health = 0;
			return false;
		}
		return true;
	}

	void DisplayStats()
	{
		std::cout << "NAME : " << Name << std::endl;
		std::cout << "HEALTH : " << Health << std::endl;
	}
	inline float GetHealth() { return Health;}
	inline std::string GetName() {return Name;}

	protected:
	bool bIsAlive;
	float Health;
	float MaxHealth;
	std::string Name;
};

class Player : public Character{
	public:
	Player(std::string n, float hp, float maxW) : Character(n, hp), PlayerInventory(maxW) {}


	private:
	Inventory PlayerInventory;

};

int main()
{
	int choice;
	std::cout << "Welcome to inventory system" << std::endl;
	std::cout << "Enter the max weight : ";
	float mw;
	std::cin >> mw;
	Inventory Inventory(mw);

	


	while(1)
	{
		std::cout << "===MENU===" << std::endl;
		std::cout << "1-Add item" << std::endl;
		std::cout << "2-Remove item" << std::endl;
		std::cout << "3-Display item" << std::endl;
		std::cout << "4-Exit" << std::endl;
		std::cout << "Enter your choice : ";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
		{
			std::string itemName;
    	float itemWeight;
    	std::cout << "Enter item name : ";
    	std::cin >> itemName;
    	std::cout << "Enter item weight : ";
    	std::cin >> itemWeight;
			std::cout << "Enter type (0=Armor, 1=Weapon, 2=Consumable) : ";
			int t;
			std::cin >> t;
			Item NewItem(itemWeight, itemName, (TIPO)t);
			Inventory.AddItem(NewItem);
			break;
		}
			
		case 2:
		{
			std::string name;
			std::cout << "Enter item name : ";
			std::cin >> name;
			Inventory.RemoveItem(name);
			break;
		}
		case 3 :
		{
			Inventory.DisplayItem();
			break;
		}	
		case 4 :
		{
			return 0;
			break;
		}
		default:
			break;
		}
	}
	

	return 0;	
}