#include <iostream>
#include <string>
#include <iterator>

template <typename T>
struct Node
{
	T item;
	Node * next;
	Node * prev;
};


template <typename T>
class MyIterator : public std::iterator<std::input_iterator_tag, T>
{
        Node<T> * p;

        public:
                MyIterator(Node<T> * x) : p(x) {}
                MyIterator(const MyIterator& myitr) : p(myitr.p) {}
                MyIterator& operator++() {p = p->next; return *this;}
                bool operator== (const MyIterator& rhs) const {return p == rhs.p;}
                bool operator!= (const MyIterator&rhs) const {return p!= rhs.p;}
                T& operator*() const {return p->item;}
};


template <typename T> 
class Deque
{

	Node<T> * head;
	Node<T> * tail;

	int length = 0;

	public:
		Deque();
		bool isEmpty();
		int size();
		void addFirst(T);
		void addLast(T);
		T popFirst();
		T popLast();
		void print();
		MyIterator<T> begin();
		MyIterator<T> end();
};

template <typename T>
MyIterator<T> Deque<T>::begin()
{
	return(MyIterator<T>(head->next));
}

template <typename T>
MyIterator<T> Deque<T>::end()
{
	return(MyIterator<T>(tail));
}
template <typename T>
bool Deque<T>::isEmpty()
{
	return(head->next == tail);
}

template <typename T>
Deque<T>::Deque()
{
	head = new Node<T>();
	tail = new Node<T>();

	head->next = tail;
	head->prev = 0;

	tail->next = 0;
	tail->prev = head;
}

template <typename T>
void Deque<T>::addFirst(T newdata)
{
	//make a new node
	Node<T> * newNode = new Node<T>();

	//set the new data to the new node
	newNode->item = newdata;

	//set the new node to be at the beginning of the queue
	//it does this by pointing to the thing head used to point to
	newNode->prev = head;
	newNode->next = head->next;

	//have head point to newNode
	head->next = newNode;

	//have the next node point to newNode
	newNode->next->prev = newNode;

	length +=1;
}

template <typename T>
T Deque<T>::popFirst()
{
	//make a new object, whatever head points to
	Node<T> *tmpNode = new Node<T>();
	tmpNode = head->next;

	//get the data of whatever head points to
	T outdata = tmpNode->item;

	//have head point to the next item
	head->next = tmpNode->next;

	//have the next item point to head
	tmpNode->next->prev = head;

	//nullifty the node
	tmpNode = NULL;

	//adjust the length
	length -=1;
	//return the found data
	return outdata;
}
template <typename T>
void Deque<T>::addLast(T newdata)
{
	//make a new node
	Node<T> * newNode = new Node<T>();

	//set the new data to the new node
	newNode->item = newdata;

	//Set newnode to point to the tail
	newNode->next = tail;

	//set the newnode to point to the previous end
	newNode->prev = tail->prev;

	//set tail to point to the newnode
	tail->prev = newNode;

	//change the length
	length += 1;

	//set the previous end to point to newnode
	newNode->prev->next = newNode;
}


template <typename T>
T Deque<T>::popLast()
{
	//make a temporary node
	Node<T> * tmpNode = new Node<T>();

	//set the new node to equal the end node and get it's data
	tmpNode = tail->prev;
	T outdata = tmpNode->item;

	//have the tail point to the next node
	tail->prev = tmpNode->prev;

	//have the new end node point to the tail
	tmpNode->prev->next = tail;

	//set the popped node to null
	tmpNode = NULL;

	//change the length
	length -= 1;
	//return the data
	return outdata;
}

template <typename T>
void Deque<T>::print()
{
	Node<T> * conductor = new Node<T>();

	conductor = head->next;

	while(conductor->next !=0)
	{
		std::cout << conductor->item << std::endl;
		conductor = conductor -> next;
	}
}

template <typename T>
int Deque<T>::size()
{
	return length;
}


int main()
{
	float pi = 3.14;
	Deque<float> deck;


	std::cout << "Add a few things to the deque" << "\n";
	deck.addFirst(pi);
	deck.addFirst(2.333);
	deck.print();
	std::cout << "Add something to the end" << "\n";
	deck.addLast(4.44);
	deck.print();

	std::cout << "Print with an iterator!\n";
	for(MyIterator<float> it = deck.begin(); it != deck.end(); ++it)
	{
		std::cout << *it << "\n";
	}
	std::cout << "the queue is now " << deck.size() << "long\n";

	std::cout << "Pop something off the front" << "\n";
	std::cout << deck.popFirst() << "\n";
	std::cout << "The list is now: \n";
	deck.print();
	std::cout << "Pop something off the back" << "\n";
	std::cout << deck.popLast() << "\n";
	std::cout <<"The list is now: \n";
	deck.print();
	
	std::cout <<"Is it empty? " << deck.isEmpty();
	std::cout <<"After popping " << deck.popLast() << "\n";
	std::cout <<"Is it empty now? " << deck.isEmpty() << "\n";
	std::cout <<"It's length is: " << deck.size() << "\n";

	return 0;
}
