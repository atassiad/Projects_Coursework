#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>

using namespace std;

int main() {
  //initalize ticket amount variables
  int firstamount = 15; //first class
  int businessamount = 25; //business class
  int economyamount = 50; // economy amount

  //initalize selection variable
  char select = 'u';

  //initalize purchasing amount variables
  int tickets = 0;
  double totalcost = 0;

  //exit condition variable
  char shutdown = 'a';
  
  //begin purchasing loop
  while(true){
    //prompt user for tickets if they are available
    while (true){
      //check for availability
      if (firstamount > 0){
        cout << "(F)irst\n";
      }
      if (businessamount > 0){
        cout << "(B)usiness\n";
      }
      if (economyamount > 0){
        cout << "(E)conomy\n";
      }
      cout << "Enter a selection: ";
      cin >> select;
      select = tolower(select);

      //exit condition
      if (select == 'f' && firstamount > 0){
        break;
      }
      if (select == 'b' && businessamount > 0){
        break;
      }
      if (select == 'e' && economyamount > 0){
        break;
      }

      //clear cin in case of failure
      cin.clear();
      cin.ignore(100, '\n');
    }

    //prompt for ticket amount
    while (true){
      cout << "Enter amount: ";
      cin >> tickets;

      //exit condition + new ticket amounts
      //first
      if (select == 'f'){
        if (tickets >= 0 && tickets <= firstamount){
          firstamount -= tickets;
          break;
        }
      }
      //bussiness
      else if (select == 'b'){
        if (tickets >= 0 && tickets <= businessamount){
          businessamount -= tickets;
          break;
        }
      }
      //economy
      else if (select == 'e'){
        if (tickets >= 0 && tickets <= economyamount){
          economyamount -= tickets;
          break;
        }
      }
      //clear false input
      cin.clear();
      cin.ignore(100, '\n');
    }

    //cost calculations
    switch (select){
      case 'f':
      totalcost = (750.0 * tickets) * 1.085;
      break;
      case 'b':
      totalcost = (225.0 * tickets) * 1.085;
      break;
      case 'e':
      totalcost = (150.0 * tickets) * 1.085;
      break;
    }
    //output cost
    cout << "Cost $ " << fixed << setprecision(2) << totalcost << endl;
    
    //prompt user to exit purchasing loop
    while (true){
      cout << "Shutdown? (Y/N):";
      cin >> shutdown;
      shutdown = tolower(shutdown);

      //exit condition
      if (shutdown == 'y' || shutdown == 'n'){
        break;
      }
    }

    //final exit condition
    if (shutdown == 'y'){
      return 0;
    }
    //final exit condition 2
    if ((firstamount + businessamount + economyamount) == 0){
      return 0;
    }
  }
}