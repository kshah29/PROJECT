#include"header.h "


int main ()
{
	// declaring varibales
	MovieList Minventory ;
	CustomerList Cinventory ;
	OrderList Oinventory ;
	string name , genre, actors, first, last, address, city, state ;
	int year, Id  ;
	double rating ;
		
	// giving a variable to the file 
	ifstream myfile ;
	
// opening file ------------------------------------------------------------MOVIES
	myfile.open( "movies.txt" ) ;
	
	
	// check if that is the end of the file
	while ( ! myfile.eof() ) 
	{
		getline ( myfile, name , ';' ) ;
		getline ( myfile, genre , ';' ) ;
		myfile >> rating  ;
		myfile >> year ;
		getline ( myfile, actors  ) ;
		
		Minventory.insertNode( Movie(name,genre,rating,year,actors) ) ;	
	}
		
	// closing file 	
	myfile.close() ;	
		
	//Minventory.display() ;
	
// opening file ----------------------------------------------------------CUSTOMER
	myfile.open( "customer.txt" ) ;
	
	// check if that is the end of the file
	while ( ! myfile.eof() ) 
	{
		myfile >> Id  ;
		myfile >> first  ;
		getline ( myfile, last , ';' ) ;
		getline ( myfile, address , ';' ) ;
		myfile >> city  ;
		myfile >> state ;
		
		Cinventory.insertNode( Customer(Id,first,last,address,city,state) ) ;	
	}
		
	// closing file 	
	myfile.close() ;
	
	//Cinventory.display() ;
	
	//Minventory.searchActor() ;
	//int option = mainMenu()  ;
	//cout <<"\n\n\n" << option ;
	
	//cout << getCustomer() ;
 	
	int main = mainMenu() ;
	
	while ( main != 4 ) // user doent want to exit 
	{
		cout << endl ;
		
		switch ( main )  // for 
		{
			case 1 : // Look for movies
			{
				int sub = movieMenu() ;
				
				while ( sub != 7 )  // user doesnt want to return 
				{
					cout << endl ;
					
					switch ( sub )  // for movie search
					{
						case 1 :	// Name - keyword
							Minventory.searchName() ;
							break ;
						
						case 2 :	// Rating Range
							Minventory.ratingRange() ;
							break ;
							
						case 3 :	// Year Range
							Minventory.yearRange() ;
							break ;
							
						case 4 :	// Genre - keyword
							Minventory.searchGenre() ;
							break ;
						
						case 5 :	// Price Range
							Minventory.priceRange() ;
							break ;
							
						case 6 :	// Actor - keyword			
							Minventory.searchActor() ;	
							break ;				
							
					}	// end of witch case for Movie Menu 
					
					cout << endl ;
					sub = movieMenu() ;
				}
				
				break ;
			}
			
			case 2 : // Order a movie
			{
				cin.ignore()  ;
				cout << "Enter the full name of the movie: " ;
				getline ( cin, name ) ;
				cout << "Enter your customer Id: " ;
				cin >> Id ;
				
				// creating an order
				Order temp  (Minventory.giveMovie(name) , Cinventory.giveCustomer(Id)) ;
				// adding order to the list
				Oinventory.push( temp ) ;
				//inserting into the next file
				insertOrder( temp )	;				
				cout << endl ;				
				
				while ( orderMenu() == 'y' ) // users want to continue
				{
					cin.ignore()  ;
					cout << "Enter the full name of the movie: " ;
					getline ( cin, name ) ;
					
					// creating an order
					Order temp  (Minventory.giveMovie(name) , Cinventory.giveCustomer(Id)) ;
					// adding order to the list
					Oinventory.push( temp ) ;
					//inserting into the next file
					insertOrder( temp )	;					
					cout << endl ;				
				}
				
				cout << "\nBilling Information : \n" ;
				Oinventory.printStack() ;
				 
				break ;
			}
			
			case 3 : // Create an account 
			{
				Customer c = getCustomer() ;
				// add the customer into the inventory/list
				Cinventory.insertNode(c) ;
				// insert it back into the text file 
				insertCustomer (c) ;
			
				break ;
			}	
			
		} // end of switch case 
		
		cout <<  endl ;
		main = mainMenu() ;
		
	} // end of while loop 
	
				
	cout << "\nGoodbye ! \n" ;		
	
	return 0 ;

}
