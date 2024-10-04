#include "ArrayList.h"
#include <cassert>
#include <iostream>

int main() {
  ArrayList<int>* list = new ArrayList<int>();

  list->append(1);
  list->append(2);
  list->append(3);

  list->insert(4, 1);
  
  list->remove(2);

  assert(list->get(0) == 1);
  assert(list->get(1) == 4);
  assert(list->get(2) == 0);
}
