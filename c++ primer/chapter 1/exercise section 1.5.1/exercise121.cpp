// write a program that takes two books with same ISBN and sums their prices
#include "Sales_item.h"
#include <iostream>

using namespace std;

int main() {

  Sales_item item_1, item_2;

  cin >> item_1;
  cin >> item_2;

  if (item_1.isbn() == item_2.isbn()) {

    cout << "Sum: " << item_1 + item_2 << endl;
  } else {
    cerr << "ISBN does not match on these books" << endl;
  }

  return 0;
}
