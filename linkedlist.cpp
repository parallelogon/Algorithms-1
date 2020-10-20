#include <iostream>
#include <vector>
#include <string>

struct Node
{
	std::string item;
	Node * next;
};

class LinkedStackOfStrings
{
	Node * first;
	
	public:
		LinkedStackOfStrings();
		void push(std::string);
		std::string pop();
		bool isEmpty();
		void print();
};

LinkedStackOfStrings::LinkedStackOfStrings()
{
	first = new Node();
	first->next = 0;
}

bool LinkedStackOfStrings::isEmpty()
{
	return(first->next == 0);
}

std::string LinkedStackOfStrings::pop()
{
	//Get the item stored at the head
	std::string head = first->item;

	//set the next item as the first
	first = first->next;

	//return the top
	return head;
}

void LinkedStackOfStrings::push(std::string newdata)
{
	// Create and allocate a new Node
	Node * newNode = new Node();

	//assign data to the new node
	newNode->item = newdata;

	//set the next of new node to the head address
	newNode -> next = first;

	//Set head as newnode
	first = newNode;

}

void LinkedStackOfStrings::print()
{
	//create a new node at the head of the list
	Node *conductor = new Node();
	conductor = first;

	//test first if it is not empty and iterate through each item, printing as you go
	if(conductor!=0)
	{
		while(conductor -> next !=0)
		{
			std::cout << conductor -> item << " " << "\n";//std::cout << conductor->item << " " << conductor << " " << conductor ->next << std::endl;
			conductor = conductor ->next;
		}
		//std::cout<<conductor->item << " " << conductor << " " << conductor-> next <<  std::endl;
	}
}

int main()
{
	LinkedStackOfStrings links;

	links.push("avocado");
	links.push("pears");
	std::cout << "Just two items" << "\n";
	links.print();
	links.push("apples");
	links.push("bananas");
	std::cout << "Add two more" << "\n";
	links.print();
	std::cout << "Pop off the top" << "\n";
	std::cout << links.pop() << std::endl;

	std::cout<< "The remaining list\n";
	links.print();
	return 0;
}
