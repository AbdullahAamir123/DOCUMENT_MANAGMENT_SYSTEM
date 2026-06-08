#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class Document {
private:
    int    serial;
    string title, type, status;

public:
    Document(int s, string ti, string ty, string st)
        : serial(s), title(ti), type(ty), status(st) {}

    virtual ~Document() {}

    int    getSerial() { return serial; }
    string getTitle()  { return title;  }
    string getType()   { return type;   }
    string getStatus() { return status; }

    virtual void show() = 0;
};


class PDFDoc : public Document {
public:
    PDFDoc(int s, string t, string st) : Document(s, t, "PDF", st) {}
    void show() override {
        cout << "  [PDF]   #" << getSerial() << "  |  " << getTitle() << "  |  " << getStatus() << endl;
    }
};

class JPGDoc : public Document {
public:
    JPGDoc(int s, string t, string st) : Document(s, t, "JPG", st) {}
    void show() override {
        cout << "  [JPG]   #" << getSerial() << "  |  " << getTitle() << "  |  " << getStatus() << endl;
    }
};

class PNGDoc : public Document {
public:
    PNGDoc(int s, string t, string st) : Document(s, t, "PNG", st) {}
    void show() override {
        cout << "  [PNG]   #" << getSerial() << "  |  " << getTitle() << "  |  " << getStatus() << endl;
    }
};

class TXTDoc : public Document {
public:
    TXTDoc(int s, string t, string st) : Document(s, t, "TXT", st) {}
    void show() override {
        cout << "  [TXT]   #" << getSerial() << "  |  " << getTitle() << "  |  " << getStatus() << endl;
    }
};


class Manager {

    Document* docs[100];
    int count;
    int nextSerial;

    static int totalReceived;
    static int totalSent;


    string detectType(string t) {

        int dotPos = -1;
        for (int i = t.length() - 1; i >= 0; i--) {
            if (t[i] == '.') { dotPos = i; break; }
        }

        if (dotPos == -1) return "";

        string ext = t.substr(dotPos + 1);

        if (ext == "pdf") return "PDF";
        if (ext == "jpg") return "JPG";
        if (ext == "png") return "PNG";
        if (ext == "txt") return "TXT";
        return "";
    }


    Document* makeDoc(int s, string t, string ty, string st) {
        if (ty == "PDF") return new PDFDoc(s, t, st);
        if (ty == "JPG") return new JPGDoc(s, t, st);
        if (ty == "PNG") return new PNGDoc(s, t, st);
        if (ty == "TXT") return new TXTDoc(s, t, st);
        return nullptr;
    }


public:

    Manager() {
        count      = 0;
        nextSerial = 1;

        ifstream file("docs.txt");
        string sStr, title, type, status;

        while (getline(file, sStr)   &&
               getline(file, title)  &&
               getline(file, type)   &&
               getline(file, status)) {

            int s = stoi(sStr);

            Document* d = makeDoc(s, title, type, status);
            if (d) docs[count++] = d;

            if (s >= nextSerial) nextSerial = s + 1;
            if (status == "Received") totalReceived++;
            else if (status == "Sent") totalSent++;
        }

        if (count > 0)
            cout << "  [" << count << " document(s) loaded]\n";
    }


    ~Manager() {
        ofstream file("docs.txt");
        for (int i = 0; i < count; i++) {
            file << docs[i]->getSerial() << "\n"
                 << docs[i]->getTitle()  << "\n"
                 << docs[i]->getType()   << "\n"
                 << docs[i]->getStatus() << "\n";
        }
        for (int i = 0; i < count; i++) delete docs[i];
    }


    void receive(string title) {
        string type = detectType(title);
        if (type.empty()) { cout << "  Unknown type! Use .pdf .jpg .png .txt\n"; return; }
        if (count >= 100) { cout << "  Storage full!\n"; return; }

        docs[count] = makeDoc(nextSerial, title, type, "Received");
        cout << "  Received!  Serial: " << nextSerial << "  Type: " << type << endl;
        count++;
        nextSerial++;
        totalReceived++;
    }


    void send(string title) {
        string type = detectType(title);
        if (type.empty()) { cout << "  Unknown type! Use .pdf .jpg .png .txt\n"; return; }
        if (count >= 100) { cout << "  Storage full!\n"; return; }

        docs[count] = makeDoc(nextSerial, title, type, "Sent");
        cout << "  Sent!  Serial: " << nextSerial << "  Type: " << type << endl;
        count++;
        nextSerial++;
        totalSent++;
    }


    void search(int serial) {
        for (int i = 0; i < count; i++)
            if (docs[i]->getSerial() == serial) { docs[i]->show(); return; }
        cout << "  Not found.\n";
    }

    void search(string title) {
        for (int i = 0; i < count; i++)
            if (docs[i]->getTitle() == title) { docs[i]->show(); return; }
        cout << "  Not found.\n";
    }


    void deleteDoc(int serial) {
        for (int i = 0; i < count; i++) {
            if (docs[i]->getSerial() == serial) {

                delete docs[i];

                for (int j = i; j < count - 1; j++) {
                    docs[j] = docs[j + 1];
                }

                count--;
                cout << "  Document deleted successfully.\n";
                return;
            }
        }
        cout << "  Not found.\n";
    }


    void showAll() {
        if (count == 0) { cout << "  No documents yet.\n"; return; }
        cout << "  TYPE    SERIAL   TITLE                STATUS\n";
        cout << "  -----------------------------------------------\n";
        for (int i = 0; i < count; i++) docs[i]->show();
    }


    void showStats() {
        cout << "  Total Documents : " << count          << endl;
        cout << "  Total Received  : " << totalReceived  << endl;
        cout << "  Total Sent      : " << totalSent      << endl;
    }
};

int Manager::totalReceived = 0;
int Manager::totalSent     = 0;

#endif
