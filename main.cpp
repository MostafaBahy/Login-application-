// FCAI – Programming 1 – 2022 - Assignment 4
// Program Name: Login Application
// Last Modification Date: 10/5/2022
// Author1 and ID and Group: Mohamed Hesham Mohamed / 20210543 / group A
// Author2 and ID and Group: Mostafa Aly Hashem / 20210394 / group A
// Author3 and ID and Group: Mostafa Bahy / 20210401 / group A
// Teaching Assistant: Eng. Abdulrahman Abdulmonem
// Purpose:..........


#include "program functions.h"

using namespace OpenXLSX;
using namespace std;


int main(){



    string choice;
    openxlfile();
    LoadTheMap();
    cout << "Welcome to ...... Log in application\n";


    while(true){



        cout << "(1) Register\n"
                "(2) Login\n"
                "(3)Change Password\n"
                "(4) Exit\n";


        // to take the user  choice
        cout << "\nPlease Enter your choice ==> ";
        getline(cin , choice);

        // to check if the choice is correct or not (defensive)
        while (true){
            if (choice.length() > 1  ){
                cin.clear();
                cout << "wrong input :( Please just select a choice form the above :- ";
                cin >> choice;
            }
            else if (choice.substr(0,1) == "1"||choice.substr(0,1) == "2"||choice.substr(0,1) == "3" ||choice.substr(0,1) == "4")
            {
                break;
            }
            else{
                cin.clear();
                cout << "wrong input :( Please just select a choice form the above:- ";
                cin >> choice;
            }
        }

        if (choice == "1"){
            email_registration();
            userName_registration();
            phoneNumber_registration();
            password_registration();
            doc.save();

        }
        if (choice == "2"){
            login();
        }
        if (choice == "3"){
            change_password();
            doc.save();

        }
        if (choice == "4"){
            break;

        }

    }

    doc.save();
    doc.close();

    return 0;
}





