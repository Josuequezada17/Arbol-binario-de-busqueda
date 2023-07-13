#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED

#include "btree.hpp"
#include "Song.hpp"

class Menu {
  public:
    void mainMenu(BTree<Song>&);
  };

#endif // MENU_HPP_INCLUDED
