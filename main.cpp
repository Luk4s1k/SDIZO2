#include "Menu/ListGraphMenu.h"
#include "Menu/MatrixGraphMenu.h"

int main()
{
ListGraphMenu *listGraphMenu = new ListGraphMenu();
MatrixGraphMenu *matrixGraphMenu = new MatrixGraphMenu();
int choice = 0;
std::cout << "Choose graph representation " << std::endl;
    std::cout << "1 - List graph " << std::endl;
    std::cout << "2 - Matrix graph " << std::endl;
std::cin >> choice;
if(choice == 1){
    listGraphMenu->listGraphCreationMode();
}else if (choice == 2){
    matrixGraphMenu->matrixGraphCreationMode();
}
return 0;

}


