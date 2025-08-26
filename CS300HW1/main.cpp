#include "MenuList.h"
#include "OrderQueue.h"
#include "PreparedStack.h"
#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    MenuList menu;
    OrderQueue orders;
    PreparedStack prepared;

    int command;

    while (true) {
        cin >> command;

        switch (command) {
            case 1: {       // add drink to menu
                int code;
                string name;
                double price;

                 cin >> code >> name >> price;

                Drink newDrink(code, name, price);
                menu.addDrink(newDrink);
                cout << "Drink added." << endl;
                break;
            }

            case 2: {   // remove drink from menu
                int code;
                cin >> code;

                bool removed = menu.removeDrink(code);
                if (removed) {
                    cout << "Removed." << endl;
                } else {
                    cout << "Not found." << endl;
                }
                break;
            }

            case 3: { // swap
                int code1, code2;
                cin >> code1 >> code2;

                if (menu.swapDrinks(code1, code2)) {
                    cout << "Swapped." << endl;
                } else {
                    cout << "Not found." << endl;
                }
                break;
            }

            case 4: { // Feature Drink
                int code;
                cin >> code;

                if (menu.featureDrink(code)) {
                    cout << "Featured." << endl;
                 } else {
                    cout << "Not found." << endl;
                }
                break;
            }

            case 5: {   // list menu
                menu.printAll();
                break;
            }

            case 6: {   // Take Order
                int orderId, drinkCode, sugarPackets;
                cin >> orderId >> drinkCode >> sugarPackets;

                if (menu.findDrink(drinkCode) != nullptr) {
                    Order newOrder(orderId, drinkCode, sugarPackets);
                    orders.enqueue(newOrder);
                      cout << "Order queued." << endl;
                } else {
                    cout << "Invalid drink code." << endl;
                }
                break;
            }

            case 7: {   // Rush
                int orderId;
                cin >> orderId;

                if (orders.rushOrder(orderId)) {
                    cout << "Order rushed." << endl;
                } else {
                    cout << "Not found." << endl;
                }
                break;
            }

            case 8: { // cancel
                int orderId;
                cin >> orderId;

                if (orders.cancelOrder(orderId)) {
                    cout << "Order canceled." << endl;
                } else {
                    cout << "Not found." << endl;
                 }
                break;
            }

             case 9: { //   pending Orders
                if (orders.empty()) {
                    cout << "No pending orders." << endl;
                } else {
                    orders.traverse([](const Order& o) {
                        cout << "Order " << o.orderId << ": Drink " << o.drinkCode
                             << ", " << o.sugarPackets << " sugar(s)" << endl;
                      });
                }
                break;
            }

            case 10: {  // Prepare Next Drink
                if (orders.empty()) {
                    cout << "No pending orders." << endl;
                } else {
                    Order nextOrder;
                    orders.dequeue(nextOrder);

                     Drink* drink = menu.findDrink(nextOrder.drinkCode);
                    Prepared preparedDrink(nextOrder.orderId, drink->name, nextOrder.sugarPackets);
                     prepared.push(preparedDrink);

                     cout << "Prepared Order " << nextOrder.orderId << ": "
                         << drink->name << " with " << nextOrder.sugarPackets
                         << " sugar(s)" << endl;
                }
                 break;
            }

            case 11: {   // Next Drink
                if (prepared.empty()) {
                    cout << "None to serve." << endl;
                } else {
                    Prepared servedDrink;
                    prepared.pop(servedDrink);
                    cout << "Served Order " << servedDrink.orderId << ": "
                         << servedDrink.drinkName << endl;
                 }
                break;
            }

            case  12: {         // Exit
                cout << "Exiting. Goodbye!" << endl;
                return 0;
            }
        }
    }

    return 0;
}