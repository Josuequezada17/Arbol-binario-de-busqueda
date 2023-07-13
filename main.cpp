#include "menu.hpp"

int main()
{
  Menu myMenu;
  BTree<Song> myArbol;

  myMenu.mainMenu(myArbol);

  return 0;
}
