#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>		// files
#include <stdio.h>      // printf, NULL 
#include <stdlib.h>     // srand, rand 
#include <time.h>       // time 


using namespace std ;



// declarations of the struct and class datatypes
// BINARY TREES ----------------------------------------------------------------------
template <class T>
struct TreeNode 
{
	T value;   //the data
	TreeNode* left;
	TreeNode* right;
};


template <class T>
class IntBTree
{
protected:
	TreeNode<T>* root;
	//private member functions
	void insert(TreeNode<T>* &, TreeNode<T>* &);
	void displayInOrder(TreeNode<T>*) const;
	void totalNodes ( TreeNode<T>* nodePtr , int & total ) ;
	void destroySubTree(TreeNode<T>* nodePtr) ;

public:
	//constructor
	IntBTree() { root = 0; }
	//destructor
	~IntBTree() { destroySubTree(root); }

	//operations
	void insertNode(T);
//	void remove(T);
	
	void display() const
	{
		displayInOrder(root);
	}

	int totalNodes ( ) 
	{
		int total = 0 ;
		totalNodes ( root , total ) ;
		return total ;
	}

//	TreeNode<T>* getHead () { return root ;	} ;
};


// STACK -----------------------------------------------------------------------------------------
template <class T>
struct StackNode
{
	T value;
	StackNode* next;
};

template <class T>
class DStack
{
private:
	StackNode<T>* top;

public:
	DStack() { top = 0; }  //default constructor
	~DStack();
	bool isEmpty() { return (top == 0); }
	void printStack();
	void push(T);
	void pop(T&);
	
};


// MOVIE & MOVIELIST -------------------------------------------------------------------
class Movie
{
	protected :
		string name ;
		string genre ;
		double rating ;
		int year ;
		string actors ;
		double price ;

	public :
		Movie () {		} ;
 		Movie ( string n, string g, double r, int y, string a ) ;	
 		string getName ()  { return name ; } 
 		string getGenre () { return genre ; } 
 		double getRating () { return rating ; } 
 		int getYear () { return year ; }
 		double getPrice () { return price ; }
 		string getActor() { return actors ;	 }
 		
 		// operator overloading ..
		friend ostream& operator<< ( ostream & out , Movie right ); 
		bool operator < (  Movie right );  
		bool operator == (  Movie right ); 		

}   ;


class MovieList : public IntBTree < Movie >
{
	private :
		void displayByName(TreeNode<Movie>* nodePtr , string sub ) ;
		void displayByRating(TreeNode<Movie>* nodePtr , double h, double l ) ;
		void displayByYear(TreeNode<Movie>* nodePtr , double h, double l ) ;
		void displayByPrice(TreeNode<Movie>* nodePtr , double h, double l ) ;
		void displayByGenre(TreeNode<Movie>* nodePtr , string sub ) ;
		void displayByActor(TreeNode<Movie>* nodePtr , string sub ) ;
		
	public :
		void searchName ()  ;
		void ratingRange ( ) ;
		void yearRange () ;
		void priceRange () ;
		void searchGenre ()  ;
		void searchActor () ; 
		
		Movie * giveMovie( string name ) ; 
		
}	;


// CUSOMER & CUSTOMERLIST ---------------------------------------------------------------
class Customer 
{
	protected :
		int Id ;
		string first ;
		string last ;
		string address ;
		string city ;
		string state ;
		
	public :
		Customer () {	 } ;
		Customer ( int i, string f, string l, string add, string c, string s ) ;	
		int getId () { return Id ; }
		string getFirst () { return first ; } 
		string getLast () { return last ; } 
		string getAdd () { return address ; } 
		string getCity () { return city ; } 
		string getState () { return state ; }
		
		// operator overloading ..
		friend ostream& operator<< ( ostream & out , Customer right ); 
		bool operator < (  Customer right );  
		bool operator == (  Customer right ); 			
} ;


class CustomerList : public IntBTree < Customer >
{
	private :
		
	public :
		Customer * giveCustomer ( int Id ) ;
				
}	;


// ORDER & ORDERLIST --------------------------------------------------------------------
class Order 
{
	protected :
		Movie * m ;
		Customer * c ;		
		
	public :
		Order () ;
		Order ( Movie * m2 , Customer * c2 ) ;
		string getOName () { return m->getName () ; }
		double getOPrice () { return m->getPrice() ; }
		int getOId () { return  c->getId() ; }		 
		
		friend ostream& operator<< ( ostream & out , Order right ) ;
} ;


class OrderList : public DStack < Order >
{
	private :
		
	public :
		
}	;


// ------ 	other Functions : MENUS - MAIN, MOVIE, CREATE CUSTOMER, INSERT CUSOMER, INSERT ORDER -----------


char orderMenu()
{
	char cont ;
	cout << "Do you want to order more ? (y/n) : " ;
	cin >> cont ;
				
	return cont ;
}


int mainMenu ()
{
	int choice ;
	
	cout << "1. Look for movies \n" ;
	cout << "2. Order a movie \n" ;
	cout << "3. Create an account \n" ;
	cout << "4. Exit \n" ;
	cout << "Enter your choice : " ;
	cin >> choice ;
	
	return choice ;
}


int movieMenu ()
{
	int choice ;
	cout << "1. Search a movie by Keyword \n" ;
	cout << "2. Search a movie by Rating \n" ;
	cout << "3. Search a movie by Year \n" ;
	cout << "4. Search a movie by Genre \n" ;
	cout << "5. Search a movie by Price \n" ;
	cout << "6. Search a movie by Actors \n" ;
	cout << "7. Go to previous menu \n" ;
	cout << "Enter your choice : " ;
	cin >> choice ;
	
	return choice ;	
}


// this fn gives a customer varibale- it collects all the data needed. 
Customer getCustomer ()
{
	srand(time(NULL));
	int Id ;
	string add, city, state, first, last ;
	
	cout << "Enter your First name: " ;
	cin >> first ;
	
	cout << "Enter your Last name: " ;
	cin >> last ; 
	
	cin.ignore() ;
	cout << "Enter your address: " ;
	getline ( cin , add ) ;
	
	cout << "Enter your City: " ;
	cin >> city ; 
	
	cout << "Enter your State: " ;
	cin >> state ; 
	
	Id = rand() % 100001 ;
	cout << "\nYour new Customer ID is : " << Id << endl << endl ;
	cout << "Your Information is : \n"  ;
	
	Customer append ( Id, first, last, add, city, state ) ;
	cout << append ;
		
	return append ;
}

// adds order to its text file
void insertOrder ( Order o )
{
	if ( &o != 0 ) // if o iis not a null pointer
	{
		// giving a variable to the file 
		ofstream myfile ; 
	
		// opening file ----------------------------------------------------------CUSTOMER
		myfile.open( "order.txt" , fstream::app ) ;
			
		myfile << o.getOId() << " " << o.getOName() << " " << o.getOPrice() << endl ;

		// closing file 	
		myfile.close() ;	
	}	
}

// adds customer to its text file
void insertCustomer ( Customer c ) 
{
	if ( &c != 0 ) // if c is not a null pointer
	{
		// giving a variable to the file 
		ofstream myfile ; 
	
		// opening file ----------------------------------------------------------CUSTOMER
		myfile.open( "customer.txt" , fstream::app ) ;
				
		myfile << c.getId() << " " << c.getFirst() << " " << c.getLast() << ";" ;
		myfile << c.getAdd() << ";" << c.getCity() << " " << c.getState() << endl ;
	
		// closing file 	
		myfile.close() ;
	}	
}


//----------------------------------class definitions------------------------------------


//--------------------------------ORDER CLASS ---------------------------------

Order :: Order () 
{
	m = 0 ;
	c = 0 ;
}


Order :: Order ( Movie * m2 , Customer * c2 ) 
{
	m = m2 ;
	c = c2 ;
}


ostream& operator<< ( ostream & out , Order right )
{
	out << setw(7) << left << right.getOId() << " : " << right.getOName() << " ( $ "  ;
	out << setprecision(2) << fixed << showpoint << right.getOPrice() << " )" << endl ;
	return out ;
}


// ----------------------------CUSTOMER CLASS ---------------------------------

Customer :: Customer ( int i, string f, string l, string add, string c, string s )	
{
	Id = i ;
	first = f ;
	last = l ;
	address = add ;
	city = c ;
	state = s ;	
}
		

ostream& operator<< ( ostream & out , Customer right )
{
	out << right.Id << endl << right.first << " " << right.last << endl ;
	out << right.address <<", " << right.city << ", " << right.state << endl ;
	
}
bool Customer :: operator < (  Customer right )
{
	if ( Id < right.Id )
		return true ;
	else 
		return false ;		
}

bool Customer :: operator == (  Customer right ) 		
{
	if ( Id < right.Id )
		return true ;
	else 
		return false ;
}


// --------------------------------- CUSTOMERLIST CLASS -------------------------------


Customer* CustomerList :: giveCustomer ( int Id ) 
{
	bool found = false ; // not found
	TreeNode<Customer>* nodePtr = root;  //start at root
	
	while (nodePtr && !found )  //still something to search
	{
		if (nodePtr->value.getId() == Id && !found)
			found = true; //found it
		else if (Id < nodePtr->value.getId())
			nodePtr = nodePtr->left;  // look in left branch
		else
			nodePtr = nodePtr->right;  // look in right branch
	}
	
	if ( found = false )	//searched everything, it's not there
		return 0 ;
	else
		return &(nodePtr->value) ; // returns the adress of the customer	
		
}


// ----------------------------------- MOVIELIST CLASS ---------------------------------


Movie* MovieList :: giveMovie( string name )
{
	bool found = false ; // not found
	TreeNode<Movie>* nodePtr = root;  //start at root
	
	while (nodePtr && !found )  //still something to search
	{
		if (nodePtr->value.getName() == name && !found)
			found = true; //found it
		else if (name < nodePtr->value.getName())
			nodePtr = nodePtr->left;  // look in left branch
		else
			nodePtr = nodePtr->right;  // look in right branch
	}
	
	if ( found = false )	//searched everything, it's not there
		return 0 ;
	else
		return &(nodePtr->value) ; // returns the adress of the customer	
		
}


void MovieList :: displayByName(TreeNode<Movie>* nodePtr , string sub ) 
{
	string name ;
		
	if (nodePtr != 0)   //not null, there is something to print
	{
		displayByName(nodePtr->left, sub);
		
		//stores the name of the movie
		name = nodePtr->value.getName() ;
		
		//prints the movie if the phrase in the movie found
		if ( name.find( sub ) <= name.length()  )
			cout << nodePtr->value << endl;

		displayByName(nodePtr->right, sub);
	}	
}

void MovieList :: displayByActor(TreeNode<Movie>* nodePtr , string sub ) 
{
	string actor ;
		
	if (nodePtr != 0)   //not null, there is something to print
	{
		displayByActor(nodePtr->left, sub);
		
		//stores the name of the movie
		actor = nodePtr->value.getActor() ;
		
		//prints the movie if the phrase in the movie found
		if ( actor.find( sub ) <= actor.length()  )
			cout << nodePtr->value << endl;

		displayByActor(nodePtr->right, sub);
	}	
}

void MovieList :: displayByRating(TreeNode<Movie>* nodePtr , double h, double l ) 
{
	if (nodePtr != 0)   //not null, there is something to print
	{
		displayByRating(nodePtr->left,h,l);
	
		//prints the movie if the rating is in range 
		if ( nodePtr->value.getRating() <= h && nodePtr->value.getRating() >= l )
			cout << nodePtr->value << endl;
		
		displayByRating(nodePtr->right,h,l);
	}		
}

void MovieList :: displayByYear(TreeNode<Movie>* nodePtr , double h, double l ) 
{
	if (nodePtr != 0)   //not null, there is something to print
	{
		displayByYear(nodePtr->left,h,l);
	
		//prints the movie if the rating is in range 
		if ( nodePtr->value.getYear() <= h && nodePtr->value.getYear() >= l )
			cout << nodePtr->value << endl;
		
		displayByYear(nodePtr->right,h,l);
	}
}	
	
	
void MovieList :: displayByPrice(TreeNode<Movie>* nodePtr , double h, double l ) 
{
	if (nodePtr != 0)   //not null, there is something to print
	{
		displayByPrice(nodePtr->left,h,l);
	
		//prints the movie if the rating is in range 
		if ( nodePtr->value.getPrice() <= h && nodePtr->value.getPrice() >= l )
			cout << nodePtr->value << endl;
		
		displayByPrice(nodePtr->right,h,l);
	}
}
	
	
void MovieList :: displayByGenre(TreeNode<Movie>* nodePtr , string sub ) 
{
	string genre ;
		
	if (nodePtr != 0)   //not null, there is something to print
	{
		displayByGenre(nodePtr->left,sub);
		
		//stores the name of the movie
		genre = nodePtr->value.getGenre() ;
		
		//prints the movie if the phrase in the movie found
		if ( genre.find( sub ) <= genre.length()   )
			cout << nodePtr->value << endl;
		
		displayByGenre(nodePtr->right,sub);
	}	
}
	

void MovieList :: searchName () 
{
	string name ;
	cout << "Enter the keyword in the movie : "  ;
	cin >> name ;
	cout << endl ;
	displayByName (root, name ) ;	
}

void MovieList :: searchActor () 
{
	cin.ignore() ;
	string actor ;
	cout << "Enter the name of the actor : "  ;
	getline ( cin, actor) ;
	cout <<  endl ;
	displayByActor (root, actor ) ;	
}

void MovieList :: ratingRange ( ) 
{
	double h , l ;
	cout << "Enter the min and max rating : " ;
	cin >> l >> h ; 
	cout << endl ;
	displayByRating ( root, h , l ) ;
}

void MovieList :: yearRange () 
{
	double h , l ;
	cout << "Enter the min and max Year : " ;
	cin >> l >> h ;
	cout << endl ;
	displayByYear ( root, h , l ) ;
}

void MovieList :: priceRange () 
{
	double h , l ;
	cout << "Enter the min and max Price : " ;
	cin >> l >> h ;
	cout << endl ;
	displayByPrice ( root, h , l ) ;
}

void MovieList :: searchGenre ()  
{
	string genre ;
	cout << "Enter the genre : "  ;
	cin >> genre ;
	cout << endl ;
	displayByGenre (root, genre ) ;	
}


//--------------------------------------- MOVIE CLASS -------------------------------------


Movie :: Movie ( string n, string g, double r, int y, string a)
{
	name = n ;
	genre = g ;
	rating = r ;
	year = y ;
	actors = a ;
	price = 1 + (0.5*rating) + (0.001 * year) ;
	
}

ostream& operator<< ( ostream & out , Movie right )
{
	out << right.name << endl << endl << setw(7) << left << "Genre" << " : "<< right.genre << endl;
	out << setw(7) << "Rating" <<  " : " << right.rating << endl << setw(7) << "Year" << " : " << right.year ;
	out << endl << setw(7) << "Actors" << " : " << right.actors << endl ;
	out << setw(7) << "Price" << " : " << right.price << endl ;
	out <<"---------------------------------------------------------" << endl ;
	return out ;
}


bool Movie :: operator < (  Movie right )
{
	if ( name < right.name )
		return true ;
	else 
		return false ;		
}


bool Movie :: operator == (  Movie right )	
{
	if ( name == right.name )
		return true ;
	else 
		return false ;		
}


// --------------------------------BINARY TREE CLASS ---------------------------------

// recursive- private function 
template <class T>
void IntBTree<T>::totalNodes ( TreeNode<T>* nodePtr , int & total )
{
	if (nodePtr)   //not null, there is nothing there
	{
		totalNodes( nodePtr->left , total);
		total ++ ;
		totalNodes(nodePtr->right, total);
	}

}

// inserting the element 
template <class T>
void IntBTree<T>::insertNode(T num)
{
	TreeNode<T>* newNode = 0 ;  //ptr to new node  
	//create new node and store num
	newNode = new TreeNode<T>;
	newNode->value = num;
	newNode->left = 0;
	newNode->right = 0;

	//call private member function to insert the node
	insert(root, newNode);  //insert this node in tree starting at root
}

//recursive function to insert into tree that starts at nodePtr
//takes pointer to "subtree" and pointer to new node as parameters
template <class T>
void IntBTree<T>::insert(TreeNode<T>* &nodePtr, TreeNode<T>* &newNode)
{

	if (nodePtr == 0) //"empty tree or subtree", insert value
		nodePtr = newNode;   //that's why must be passed by ref

	else if (newNode->value < nodePtr->value)  //goes in left branch
		insert(nodePtr->left, newNode);
		
	else //goes in right branch
		insert(nodePtr->right, newNode);
		
}

template <class T>
void IntBTree<T>::destroySubTree(TreeNode<T>* nodePtr)
{
	if (nodePtr)
	{
		if (nodePtr->left) //has a left branch
			destroySubTree(nodePtr->left);
		if (nodePtr->right) //has a right branch
			destroySubTree(nodePtr->right);
		//no children so you can delete
		delete nodePtr;
	}
}


//------------------------------------ STACK CLASS ------------------------------------

// destructor definition for releasing memeory at the end 
template <class T>
DStack<T>::~DStack()
{
	//walk through stack and release memory
	StackNode<T>* nodePtr;
	StackNode<T>* nextNode;
	//start at the top
	nodePtr = top;
	//traverse stack
	while (nodePtr != 0)
	{
		//hold the next node
		nextNode = nodePtr->next;
		//now delete nodePtr
		delete nodePtr;
		//move to next
		nodePtr = nextNode;
	}
}


// public fn pop to delete the last element- store the value of the deleted element
template <class T>
void DStack<T>::pop(T& val)
{
	//make a new top
	StackNode<T>* temp;  //for deleting the node
	//make sure stack not empty
	if (isEmpty())
		cout << "Stack is empty" << endl;
	else
	{
		val = top->value;
		temp = top->next; //need to hold the new top
		delete top;
		top = temp;
	}

}

// public fn push is to add a new element on the top
template <class T>
void DStack<T>::push(T newValue)
{
	//allocate a new node
	StackNode<T>* newNode;
	newNode = new StackNode <T> ; //allocate memory
	newNode->value = newValue;
	
	// if the stack is empty
	if (isEmpty())
	{
		top = newNode;
		newNode->next = 0;
	}
	else
	{		
		newNode->next = top;
		top = newNode;
	}
}

// public fn printStsck is to print the elements in the stack
template <class T>
void DStack<T>::printStack()
{
	StackNode<T>* nodePtr;
	
	// if the stack is empty
	if (isEmpty())
		cout << "Stack is empty" << endl;
	else
	{
		nodePtr = top;
		//walk through and print
		while (nodePtr != 0)
		{
			cout << nodePtr->value ;
			nodePtr = nodePtr->next;
		}
	}
}



