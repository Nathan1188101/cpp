// same thing as before but take several book objects
#include "Sales_item.h"
#include <iostream>

using namespace std;

int main() {

  // for incoming book
  Sales_item total;

  // checking that there is actually data coming in
  if (cin >> total) {

    // make another Sales_item object called current
    Sales_item current;
    while (cin >> current) {

      // if the current isbn and the new isbn match, me add that to the total
      if (total.isbn() == current.isbn()) {

        total += current;
        // if they don't match we print the sum from the last x amount of books
        // that matched and move on to keeping track of the next inputs
      } else {
        // print results for last books
        cout << "Total: " << total << endl;
        // set total to be the current book
        total = current;
      }
    }
  }

  return 0;
}
