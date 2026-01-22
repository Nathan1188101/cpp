#include "Sales_item.h"
#include <iostream>

using namespace std;

int main() {

  // write a program that reads a set of book sales transactions, write each
  // transaction to the std output

  Sales_item book;
  while (cin >> book) {
    cout << book;
  }
  return 0;
}
