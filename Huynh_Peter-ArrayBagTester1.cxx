#include <iostream>
#include <string>
#include "ArrayBag.h"

using namespace std;

int main()
	{
		// here we call the ArrayBag constructor; this particular bag stores strings 
		ArrayBag<string> aBag;
		
		// here we call the isEmpty function on a new ArrayBag 
		if (aBag.isEmpty())
			cout << "New bag is created empty; that is good" << endl;
		else
			cout << "New bag is created with stuff; not so good" << endl;
			
		// here we call the getCapacity function on a new ArrayBag 
		if (aBag.getCapacity() > 0)
			cout << "New bag is created with non-zero capacity; that is good" << endl;
		else
			cout << "New bag is created with zero capacity; not so good" << endl;

		// here we add a couple of things 
		aBag.add("tostada");
		aBag.add("tamale");
		aBag.add("taco");

		/* Things I've Added to further test aBag*/
		cout << "Lab 2 Testing begins!" << endl;

		// 1 Tries to remove something that isn't in the bag.
		aBag.remove("Something that isn't in the bag");
		if (aBag.getCurrentSize == 3)
			cout << "Everything is alright." << endl;
		else
			cout << "Something went wrong with removing something not here." << endl;
			

		// 2 Tries to Adds strings with breaks and then removes it
		aBag.add("/n/t/n Break");
		if (aBag.contains("/n/t/n Break") == true)
			cout << "Bag has the escape strings." << endl;
		else
			cout << "Bag doesn't have the escapes" << endl;
		if (aBag.getCurrentSize == 4)
			cout << "Everything is alright. They went in as one object" << endl;
		else
			cout << "Something is wrong." << endl;
		// 3
		aBag.remove("/n/t/n Break");
		if (aBag.contains("/n/t/n/r Break") == false)
			cout << "Escape strings successfully removed." << endl;
		else
			cout << "Bag still has the escapes" << endl;

		// 4 Tries to add a break that isn't a legitimate break and then removes it
		aBag.add("/goto 1");
		if (aBag.contains("/goto 1") == true)
			cout << "Bag has the unlegit escape." << endl;
		else
			cout << "Bag doesn't have the illegal escape" << endl;	
		if (aBag.getCurrentSize == 4)
			cout << "Everything is alright." << endl;
		else
			cout << "Something went wrong..." << endl;
		
		// 5
		aBag.remove("/goto 1");
		if (aBag.contains("/goto 1") == false)
			cout << "Bag has successfully removed the unlegit escape." << endl;
		else
			cout << "Bag still has the illegal escape" << endl;

		// 6 Tries to add an blank string within a variable
		string blank = "";
		aBag.add(blank);
		if (aBag.contains("") == true)
			cout << "Bag has successfully added a blank string." << endl;
		else
			cout << "The blank string isn't in that bag." << endl;	
		
		// 7
		aBag.remove(blank);
		if (aBag.contains("") == false)
			cout << "Bag has successfully removed a blank string... or the blank string was never there" << endl;
		else
			cout << "The blank string is still in that bag for some odd reason." << endl;	

		// 8 Creates a for loop that adds 100 JUNK strings into the bag
		for(i = 0; i < 100; i++)
			aBag.add("JUNK");
		if (aBag.getCurrentSize() > aBag.getCapacity())
			cout << "How'd you do that? Bag items exceeded Capacity." << endl;
		else
			cout << "Bag within capacity. So, it stopped adding after capacity is reached." << endl;
		
		// 9 Removes JUNK 100 times.
		for(i = 0; i < 100; i++)
			aBag.remove("JUNK");
		if (aBag.contains("JUNK") == true)
			cout << "JUNK strings are still in bag." << endl;
		else
			cout << "All JUNK removed." << endl;
		if (aBag.isEmpty())
			cout << "Somehow the bag is empty..." << endl;
		else
			cout << "Bag is not empty, that is good!" << endl;

		// 10 Adds two strings combined.
		aBag.add("Rofl" + "lol");
		if (aBag.contains("Rofllol") == true)
			cout << "Bag succeeded in adding two strings into one position." << endl;
		else
			cout << "Bag didn't add two strings in one position." << endl;
		if ((aBag.contains("Rofl") == true) && (aBag.contains("lol") == true))
			cout << "Bag succeeded in adding two strings into two position." << endl;
		else
			cout << "Bag didn't add two strings in two position." << endl;

		cout << "Lab 2 Testing Stops" << endl;
		/* Additions Stop Here */

		// here we check if the ArrayBag is empty
		if (aBag.isEmpty())
			cout << "Bag after adding thinks it is empty; that is not so good" << endl;
		else
			cout << "Bag after adding thinks it is not empty; that is good" << endl;
			
		// here we check if it knows its own size
		if (aBag.getCurrentSize() != 3)
			cout << "Bag after adding has wrong size; that is not so good" << endl;
		else
			cout << "Bag after adding has right size; that is good" << endl;

		if (aBag.contains("tamale") == false)
			cout << "Bag can't find added items; that is not so good" << endl;
		else
			cout << "Bag can find added items; that is good" << endl;
		
		if (aBag.contains("torta") == true)
			cout << "Bag can find items we never added; that is not so good" << endl;
		else
			cout << "Bag doesn't find items we never added; that is good" << endl;
			
		// here we check what happens if we ask to remove something not in the ArrayBag
		aBag.remove("torta");
		
		// here we check if the ArrayBag knows its own size after a non-event removal
		if (aBag.getCurrentSize() != 3)
			cout << "Bag should be the same size as before but isn't; that is not so good" << endl;
		else
			cout << "Bag is the same size as before; that is good" << endl;
		
		// here we remove something in the ArrayBag
		aBag.remove("tamale");
		
		// here we check if the size has changed
		if (aBag.getCurrentSize() != 2)
			cout << "Bag should be smaller than before but isn't; that is not so good" << endl;
		else
			cout << "Bag is the right size after removing one item; that is good" << endl;
		
		// empty the bag
		aBag.clear();
		
		// check the size of the empty bag
		if (aBag.getCurrentSize() != 0)
			cout << "Bag after clearing has wrong size; that is not so good" << endl;
		else
			cout << "Bag after clearing has right size; that is good" << endl;
		
		for (int i = 0; i < aBag.getCapacity(); ++i)
			aBag.add("tamale");
			
		if (aBag.getCurrentSize() != aBag.getCapacity())
			cout << "Bag after adding has wrong size; that is not so good" << endl;
		else
			cout << "Bag after adding has right size; that is good" << endl;
		
		// try adding to a full ArrayBag
		aBag.add("tamale");
		
		// check that this has not changed the size
		if (aBag.getCurrentSize() != aBag.getCapacity())
			cout << "Full bag after adding has wrong size; that is not so good" << endl;
		else
			cout << "Full bag after adding has right size; that is good" << endl;
			
		// check if the ArrayBag is now full
		if (aBag.isFull() == false)
			cout << "Full bag doesn't know it's full; that is not so good" << endl;
		else
			cout << "Full bag knows it's full; that is good" << endl;
		
		// check if we can count up how often an item appears in the ArrayBag
		if (aBag.getFrequencyOf("tamale") != aBag.getCapacity())
			cout << "Bag can't count items correctly when they are present; that is not so good" << endl;
		else
			cout << "Bag can count items correctly when they are present; that is good" << endl;
		
		// check if we get the right answer for an item that isn't in the ArrayBag
		if (aBag.getFrequencyOf("torta") != 0)
			cout << "Bag can't count items correctly when they are absent; that is not so good" << endl;
		else
			cout << "Bag can count items correctly when they are absent; that is good" << endl;
				
		// use remove to empty the Bag
		for (int i = 0; i < aBag.getCapacity(); ++i)
			aBag.remove("tamale");
			
		// check that remove has left the size correct
		if (aBag.getCurrentSize() != 0)
			cout << "Size of bag is incorrect after removing all the items; that is not so good" << endl;
		else
			cout << "Size of bag after removing all the items is correct; that is good" << endl;
			
	}

