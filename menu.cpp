#include <iostream>
#include <fstream>
#include "menu.hpp"

using namespace std;

void Menu::mainMenu(BTree<Song>& myArbol) {
    char op, opcionMenuPrincipal;
    string myCadena;
    bool carga = false;

    Name myCantante, myInterprete;
    Song myCancion;

    BTree<Song>::Position pos;

    do {
        system("cls");
        system("color 79");

        if(carga == true){
        cout <<myArbol.parsePreOrder() << endl;
        }
        cout << "  SPOTIFY PREMIUM " << endl
             << "    MAIN MENU     " << endl << endl
             << "Add a new song [A]" << endl
             << "Delete song    [B]" << endl
             << "Find song      [C]" << endl
             << "Retrieve song  [D]" << endl
             << "Get height     [E]" << endl
             << "Get higest     [F]" << endl
             << "Get lowest     [G]" << endl
             << "Parse preOrder [H]" << endl
             << "Parse inOrder  [I]" << endl
             << "Parse posOrder [J]" << endl
             << "Show tree      [K]" << endl
             << "Load tree      [L]" << endl
             << "Save tree      [M]" << endl
             << "DeleteAll      [N]" << endl
             << "EXIT           [0]" << endl << endl
             << "Option: ";

        cin >> opcionMenuPrincipal;
        cin.ignore();
        system("cls");

        switch(opcionMenuPrincipal) {
        case 'A':
            do {
                cout << "Song: ";
                getline(cin, myCadena);
                myCancion.setCancion(myCadena);

                cout << "Artist name: ";
                getline(cin, myCadena);
                myCantante.setFirst(myCadena);

                cout << "Artist last name: ";
                getline(cin, myCadena);
                myCantante.setLast(myCadena);

                myCancion.setArtista(myCantante);

                cout << "Interpeter name: ";
                getline(cin, myCadena);
                myInterprete.setFirst(myCadena);

                cout << "Interpeter last name: ";
                getline(cin, myCadena);
                myInterprete.setLast(myCadena);

                myCancion.setNameInterpeter(myInterprete);

                cout <<"Ranking: ";
                getline(cin,myCadena);
                myCancion.setRanking(myCadena);

                cout << "Format MP3: ";
                getline(cin, myCadena);
                myCancion.setMP3(myCadena);

                myArbol.insertData(myCancion);
                myArbol.writeToDisk();

                cout << "Insert one more? (y/n): ";
                cin >> op;
                cin.ignore();

            } while(op == 'y' or op == 'Y');
            system("pause");

            break;

        case 'B':

            cout<< myArbol.parsePreOrder()<<endl;

            do {

                cout<<"Write the name of the song to delete: ";
                getline(cin,myCadena);
                myCancion.setCancion(myCadena);
                pos = myArbol.findData(myCancion);

                cout << endl << endl;

                if(pos == nullptr) {
                    cout << "Isn't found" << endl;
                } else {
                    cout<<"Deleting the song: "<<myCadena<<endl;

                    cout<< myArbol.retrieve(pos).toString();

                    cout<<endl<<endl;

                    myArbol.deleteData(myCancion);

                    cout <<endl;
                }

                cout << myArbol.parsePreOrder()<<endl<<endl;

                cout << "Do you want to delete other? (y/n): ";
                cin >> op;
                cin.ignore();

            } while(op == 'y' or op == 'Y');
            break;

        case 'C':
            cout << myArbol.parsePreOrder()<<endl<<endl;

            cin.ignore();
            cout << "Write the song to search: ";
            getline(cin, myCadena);
            myCancion.setCancion(myCadena);
            system("cls");

            pos = myArbol.findData(myCancion);

            cout<< "The song with name "<<myCadena;
            if(pos == nullptr) {
                cout<<" isn't in the list "<<endl<<endl;
            } else {
                cout<< " is in the position "<<pos<< " of the tree"<<endl<<endl;
                cout<< " Song: ";
                cout<< myArbol.retrieve(pos).getMP3()<<endl<<endl;
                cout<< " Full record: "<<endl;
                cout<< myArbol.retrieve(pos).toString()<<endl<<endl;
            }
            pos = nullptr;

            system("pause");
            break;

        case 'D':
            cout << "Introduce the song's name to retrieve: ";
            getline(cin, myCadena);
            system("cls");
            myCancion.setCancion(myCadena);
            pos = myArbol.findData(myCancion);
            cout << myArbol.retrieve(pos).toString() << endl;
            system("pause");
            break;

        case 'E':
            cout << "Height of the tree: " << myArbol.getHeight()
                 << endl;
            break;

        case 'F':
            cout << "Higest: " << myArbol.retrieve(myArbol.getHighest()) << endl;
            break;

        case 'G':
            cout << "Lowest: " << myArbol.retrieve(myArbol.getLowest()) << endl;
            break;

        case 'H':
            cout << "Parse Pre-Order: " << endl
                 << myArbol.parsePreOrder() << endl;
            break;

        case 'I':
            cout << "Parse In-Order: " << endl
                 << myArbol.parseInOrder() << endl;
            break;

        case 'J':
            cout << "Parse Post-Order: " << endl
                 << myArbol.parsePostOrder() << endl;
            break;

        case 'K':
            cout << endl << myArbol.toString() << endl;
            break;

        case 'L':
            myArbol.readFromDisk();
            cout << "Tree ready." << endl;
            carga = true;
            break;

        case 'M':
           myArbol.writeToDisk();
            cout << "Saving tree." << endl;
            break;

        case 'N':
            myArbol.deleteAll();
            cout << "Delete all the tree." << endl;
            break;

            case '0':
                system("Color A0");
                cout<<"Exit of spotify premium"<<endl;
                break;

            default:
                system("color 4F");
                cout<<"Invalid option!"<<endl;
                cout<<"Insert a valid option"<<endl;

        }

        cout << endl;
        system("pause");

    } while(opcionMenuPrincipal != '0');
}

