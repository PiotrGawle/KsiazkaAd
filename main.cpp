#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

struct Contact {
    int id=0;
    string name="",surname="",phone="",email="",address="";
};

void addContact(vector<Contact>&friends);
void displayAllFriends(vector<Contact>&friends);
void searchForFriendByName(vector<Contact>&friends);
void searchForFriendBySurname(vector<Contact>&friends);
int loadFriendsFromFile(vector<Contact>&friends,int numberOfFriends);
void addingFriendToFile(int id,string name,string surname,string phone,string email,string address);
void displayFriend (vector<Contact>&friends,vector<Contact>::iterator itr);
void editContact(vector<Contact>&friends);
void overwritingContact(vector<Contact>&friends);
void deleteContact(vector<Contact>&friends);

int main() {
    vector<Contact> friends;
    char choice;
    int numberOfFriends = loadFriendsFromFile(friends,numberOfFriends);
    while(true) {
        system("cls");
        cout << "1.Add contact" << endl;
        cout << "2.Search for contact by name" << endl;
        cout << "3.Search for contact by surname" << endl;
        cout << "4.Display all Contact" << endl;
        cout << "5.Delete Contact" << endl;
        cout << "6.Edit Contact" << endl;
        cout << "9.Exit" << endl;
        cin>>choice;
        if(choice=='1') {
            addContact(friends);
        } else if (choice=='2') {
            searchForFriendByName(friends);
        } else if (choice=='3') {
            searchForFriendBySurname(friends);
        } else if (choice=='4') {
            displayAllFriends(friends);
        } else if (choice=='5') {
            deleteContact(friends);
        } else if (choice=='6') {
            editContact(friends);
        } else if (choice=='9') {
            exit(0);
        }
    }
    return 0;
}
void addContact(vector<Contact>&friends) {
    string name,surname,phone,email,address;
    Contact contact;
    cout<<"Enter name: ";
    cin>>name;
    cout<<"Enter surname: ";
    cin>>surname;
    cout<<"Enter phone: ";
    cin.clear();
    cin.sync();
    getline(cin,phone);
    cout<<"Enter email: ";
    cin>>email;
    cout<<"Enter address: ";
    cin.clear();
    cin.sync();
    getline(cin,address);
    contact.name = name;
    contact.surname = surname;
    contact.phone = phone;
    contact.email = email;
    contact.address = address;
    contact.id = friends.size()== 0 ? 1 : friends[friends.size()-1].id+1 ;
    friends.push_back(contact);
    addingFriendToFile(contact.id,name,surname,phone,email,address);
    cout<<"Contact has been added."<<endl;
    Sleep(2000);

}
void searchForFriendBySurname(vector<Contact>&friends) {
    string surname;
    cout << "Enter surname: ";
    cin >> surname;
    bool contactExists = false;
    for (vector<Contact>::iterator itr = friends.begin(); itr != friends.end(); itr++) {
        if (itr -> surname == surname) {
            contactExists = true;
            displayFriend(friends,itr);
        }
    }
    if (contactExists == false)
        cout << endl << "There is no Contact with that surname!" << endl << endl;
    system ("pause");
}
void searchForFriendByName(vector<Contact>&friends) {
    string name;
    cout << "Enter name: ";
    cin >> name;
    bool contactExists = false;
    for (vector<Contact>::iterator itr = friends.begin(); itr != friends.end(); itr++) {
        if (itr -> name == name) {
            contactExists = true;
            displayFriend(friends,itr);
        }
    }
    if (contactExists == false)
        cout << endl << "There is no Contact with that name!" << endl << endl;
    system ("pause");
}
void displayAllFriends(vector<Contact>&friends) {
    for (vector<Contact>::iterator itr = friends.begin(); itr != friends.end(); itr++) {
        displayFriend(friends,itr);
    }
    system("pause");
}
int loadFriendsFromFile(vector<Contact>&friends,int numberOfFriends) {
    fstream file;
    char sign = '|';
    string line;
    string idSwitch;
    file.open("ContactBook.txt",ios::in);
    if(!file.good()) {
        return 0;
    }
    while(getline(file, line)) {
        Contact contact;
        stringstream ss(line);
        getline(ss,idSwitch,'|');
        contact.id = atoi(idSwitch.c_str());
        getline(ss,contact.name,'|');
        getline(ss,contact.surname,'|');
        getline(ss,contact.phone,'|');
        getline(ss,contact.email,'|');
        getline(ss,contact.address,'|');
        friends.push_back(contact);
        numberOfFriends++;
    }
    file.close();
    return numberOfFriends;
}
void addingFriendToFile(int id,string name,string surname,string phone,string email,string address) {
    fstream file;
    file.open("ContactBook.txt",ios::out | ios::app);
    cout<<endl;
    file<<id<<"|";
    file<<name<<"|";
    file<<surname<<"|";
    file<<phone<<"|";
    file<<email<<"|";
    file<<address<<"|"<<endl;
    file.close();
}
void displayFriend (vector<Contact>&friends,vector<Contact>::iterator itr) {
    cout<<endl;
    cout << itr -> id << endl;
    cout << itr -> name << endl;
    cout << itr -> surname << endl;
    cout << itr -> phone << endl;
    cout << itr -> address << endl;
    cout << itr -> email << endl;
}

void editContact(vector<Contact>&friends) {
    int id;
    char choice;
    cout<<"Enter id of a Contact you want to edit: ";
    cin>>id;
    bool contactExists = false;
    for (vector<Contact>::iterator itr = friends.begin(); itr != friends.end(); itr++) {
        if (itr -> id == id) {
            contactExists = true;
            while(true) {
                system("cls");
                cout << "1.Change name" << endl;
                cout << "2.Change surname" << endl;
                cout << "3.Change phone number" << endl;
                cout << "4.Change email" << endl;
                cout << "5.Change address" << endl;
                cout << "9.Return to main menu" << endl;
                cin>>choice;
                if(choice=='1') {
                    cout<<"Enter new name: ";
                    cin>>friends[id-1].name;
                    overwritingContact(friends);
                    cout<<"Data has been updated";
                    Sleep(2000);
                } else if (choice=='2') {
                    cout<<"Enter new surname: ";
                    cin>>friends[id-1].surname;
                    overwritingContact(friends);
                    cout<<"Data has been updated";
                    Sleep(2000);

                } else if (choice=='3') {
                    cout<<"Enter new phone: ";
                    cin.clear();
                    cin.sync();
                    getline(cin,friends[id-1].phone);
                    overwritingContact(friends);
                    cout<<"Data has been updated";
                    Sleep(2000);

                } else if (choice=='4') {
                    cout<<"Enter new email: ";
                    cin>>friends[id-1].email;
                    overwritingContact(friends);
                    cout<<"Data has been updated";
                    Sleep(2000);

                } else if (choice=='5') {
                    cout<<"Enter new address: ";
                    cin.clear();
                    cin.sync();
                    getline(cin,friends[id-1].address);
                    overwritingContact(friends);
                    cout<<"Data has been updated";
                    Sleep(2000);
                } else if (choice=='9') {
                    return;
                }
            }
        }
    }
    if(contactExists == false)
        cout << endl << "There is no Contact with that surname!" << endl;
    system ("pause");
}
void overwritingContact(vector<Contact>&friends) {
    fstream file;
    file.open("ContactBook.txt",ios::out);
    for (int i=0; i<friends.size(); i++) {
        cout<<endl;
        file<<friends[i].id<<"|";
        file<<friends[i].name<<"|";
        file<<friends[i].surname<<"|";
        file<<friends[i].phone<<"|";
        file<<friends[i].email<<"|";
        file<<friends[i].address<<"|"<<endl;
    }
    file.close();
}
void deleteContact(vector<Contact>&friends) {
    int id;
    char letter;
    cout<<"Enter the ID of a person that you want to delete: ";
    cin>>id;
    bool contactExists = false;
    for (vector<Contact>::iterator itr = friends.begin(); itr != friends.end(); itr++) {
        if (itr -> id == id) {
            contactExists = true;
            displayFriend(friends,itr);
            cout << "Do you want to delete this contact? Y/N" << endl;
            cin>>letter;
            if (letter == 'y' || letter == 'Y') {
                friends.erase(itr);
                overwritingContact(friends);
                cout << endl << "Contact has been deleted" << endl;
                Sleep(3000);
                return;
            } else if (letter == 'n' || letter == 'N') {
                return;
            }

        }

    }
    if(contactExists == false)
        cout << endl << "There is no Contact with that surname!" << endl;
    system ("pause");
}
