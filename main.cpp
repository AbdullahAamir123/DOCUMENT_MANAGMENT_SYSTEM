#include <iostream>
#include <string>
#include "library.h"
using namespace std;

int main() {
    Manager mgr;

    int    choice;
    string title;
    int    serial;

    cout << "\n  === DOCUMENT MANAGEMENT SYSTEM ===\n";
    cout << "  Supported: .pdf  .jpg  .png  .txt\n";

    while (true) {
        cout << "\n  1. Receive Document\n";
        cout << "  2. Send Document\n";
        cout << "  3. Search by Serial Number\n";
        cout << "  4. Search by Title\n";
        cout << "  5. View All Documents\n";
        cout << "  6. View Statistics\n";
        cout << "  7. Delete Document\n";
        cout << "  8. Exit\n";
        cout << "  Choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            cout << "  Enter filename (e.g. report.pdf): ";
            getline(cin, title);
            mgr.receive(title);

        } else if (choice == 2) {
            cout << "  Enter filename to send (e.g. photo.jpg): ";
            getline(cin, title);
            mgr.send(title);

        } else if (choice == 3) {
            cout << "  Enter serial number: ";
            cin >> serial;
            cin.ignore();
            mgr.search(serial);

        } else if (choice == 4) {
            cout << "  Enter title: ";
            getline(cin, title);
            mgr.search(title);

        } else if (choice == 5) {
            mgr.showAll();

        } else if (choice == 6) {
            mgr.showStats();

        } else if (choice == 7) {
            cout << "  Enter serial number to delete: ";
            cin >> serial;
            cin.ignore();
            mgr.deleteDoc(serial);

        } else if (choice == 8) {
            cout << "  Goodbye!\n";
            break;

        } else {
            cout << "  Invalid Choice.\n";
        }
    }

    return 0;
}
