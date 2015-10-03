#include <vector>
#include <cstddef>

// Constructor; creates and initializes an empty Bag of "capacity" size
template <class ItemType>
ArrayBag<ItemType>::ArrayBag(int capacity)
{
	itemCount = 0;
	myCapacity = capacity;
	items = new ItemType[myCapacity];
}

// Copy constructor; creates and initializes Bag from another Bag
template <class ItemType>
ArrayBag<ItemType>::ArrayBag(const ArrayBag& anotherBag)
{
	itemCount = anotherBag.getCurrentSize();
	myCapacity = anotherBag.getCapacity();
	items = new ItemType[anotherBag.getCapacity()];
	
	for(int index = 0; index < myCapacity; index++)
		items[index] = anotherBag.items[index];
}

//destructor
template <class ItemType>
ArrayBag<ItemType>::~ArrayBag()
{
	delete [] items;
}

// Assignment operator
template <class ItemType>
ArrayBag<ItemType>& ArrayBag<ItemType>::operator=(const ArrayBag<ItemType>& anotherBag)
{	
	clear();
	
    delete [] items;

    itemCount = anotherBag.getCurrentSize();
    myCapacity = anotherBag.getCapacity();
    items = new ItemType[myCapacity];

    for (int index = 0; index < itemCount; index++)
        items[index] = anotherBag.items[index];
	
	return *this;
}

// Return the number of Items being stored in the Bag
template <class ItemType>
int ArrayBag<ItemType>::getCurrentSize() const
{
	return itemCount;	
}

// Return the capacity of the bag (the maximum Items it can store) 
template <class ItemType>
int ArrayBag<ItemType>::getCapacity( ) const
{
	return myCapacity;
}

//Resizes the bag's capacity to newCapacity
//if the new size is larger, copy all bag contents
// we don't downsize a bag in HW2
template <class ItemType> 
void ArrayBag<ItemType>::resize(int newCapacity)
{
	ItemType* resizedBag = items;
	items = new ItemType[newCapacity];
	for(int index = 0; index < itemCount; index++)
		items[index] = resizedBag[index];
	delete [] resizedBag;
	myCapacity = newCapacity;
}

// Report whether the Bag is empty
// Return true if the Bag is empty (storing no Items);
// Return false if Items exist in the Bag
template <class ItemType>
bool ArrayBag<ItemType>::isEmpty() const
{
	return (itemCount == 0);
}

// Report whether the Bag is full
// Return true if the Bag is filled to capacity
// Return false if there is still room
template <class ItemType>
bool ArrayBag<ItemType>::isFull() const
{
	return (itemCount >= getCapacity());
}

// Give the Bag a new Item to store
// If Bag is full, double capacity and add newItem
// Else, Bag must add this Item to its Item array and update its numberOfItems
// If Bag is full after this, return true; else return false
template <class ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newItem)
{
	if (isFull())
	{
		resize(2 * getCapacity());
		items[itemCount] = newItem;
		itemCount++;
		return false;
	}
	else
	{
		items[itemCount] = newItem;
		itemCount++;

		if (isFull())
			return true;
		else
			return false;
	}
}

// Make the Bag act like an empty Bag again
template <class ItemType>
void ArrayBag<ItemType>::clear()
{
	itemCount = 0;
}

// Remove an Item from the bag
// If Item is not there, nothing changes and we return false
// Else, we fill in its spot in that Item array and count number of Items down
template <class ItemType>
bool ArrayBag<ItemType>::remove(const ItemType& anItem)
{
	int itemIndex = -1;
	for(int searchIndex = 0; searchIndex < itemCount; searchIndex++)
	{
		if (items[searchIndex] == anItem)
		{
			itemIndex = searchIndex;
			break;
		}
	}
	if (!isEmpty() && (itemIndex > -1))
	{
		itemCount--;
		items[itemIndex] = items[itemCount];
	}
	return (!isEmpty() && (itemIndex > -1));
}

// Check if an Item is in the Bag
// Return true if it is in the Bag, and false if not
template <class ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anItem) const
{
	return (getFrequencyOf(anItem) > 0);
}

// Check how many times an Item is in the Bag
// return 0 if it's not there; otherwise,
// return the number of times it occurs
template <class ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anItem) const
{
	int frequency = 0;
	for(int currentIndex = 0; currentIndex < itemCount; currentIndex++)
	{
		if (items[currentIndex] == anItem)
		{
			frequency++;
		}
	}
	return frequency;
}

// Make an output vector of Items from the bag (for checking)
template <class ItemType>
vector<ItemType> ArrayBag<ItemType>::toVector() const
{
	vector<ItemType> bagContents;
	for(int index = 0; index < itemCount; index++)
		bagContents.push_back(items[index]);
	return bagContents;
}
