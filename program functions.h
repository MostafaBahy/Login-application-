// log in app finished functions
// Created by dell on 5/12/2022.
#ifndef LOG_IN_APP_PROGRAM_FUNCTIONS_H
#define LOG_IN_APP_PROGRAM_FUNCTIONS_H


#include <iostream>
#include <string>
#include <map>
#include <conio.h>
#include <stdlib.h>
#include "OpenXLSX.hpp"
using namespace OpenXLSX;
using namespace std;


// map for login
map<string, string> username_password_map;

//map for the emails
map<string, int> email_cellColumn_map;

// map for change password
map<string, int> password_cellColumn_map;

struct user_info{
    string email ;
    string password;
    string username;
    string phone_number;
};

user_info userInfoLoad,userInfotake;


int row_number = 1 + username_password_map.size(), column_number= 1;

XLDocument doc;


// openxlfile() is responsible for openning the database file (the file that contains the users data) for the program to work on
void openxlfile(){

//    string xl_file_name;
//    cout << "please enter the name of the file you want to use as the database exel file \n"
//            " note: the name should be with full path and it should contain (.xlsx) the end of its name\n"
//            "enter the name here:-  ";
//    getline (cin,xl_file_name);
//    doc.open(xl_file_name);

//    doc.create("users_data.xlsx");

    doc.open("C:\\Users\\dell\\CLionProjects\\log in app\\cmake-build-debug\\users_data.xlsx");
    auto wks = doc.workbook().worksheet("Sheet1");
    auto A1cell = wks.cell("A1");
    auto B1cell = wks.cell("B1");
    auto C1cell = wks.cell("C1");
    auto D1cell = wks.cell("D1");
    A1cell.value() = "Emails:";
    B1cell.value() = "Usernames:";
    C1cell.value() = "Phone numbers:";
    D1cell.value() = "Passwords:";

}


// LoadTheMap() is responsible for loading the data of the users who have already before from the data file into the maps
// at the beginning of the program
void LoadTheMap(){

    auto wks = doc.workbook().worksheet("Sheet1");
    auto rowsNumberInfile = wks.rowCount();

    for(int i = 1; i<= rowsNumberInfile;i++){

        auto SearchUsernameCellS = wks.cell(i,2);
        auto SearchPasswordsCellS = wks.cell(i,4);
        auto SearchEmailsCellS = wks.cell(i,1);

        username_password_map[string(SearchUsernameCellS.value())] = string(SearchPasswordsCellS.value());
        password_cellColumn_map[string(SearchPasswordsCellS.value())] = i;
        email_cellColumn_map[SearchEmailsCellS.value()] = i;

    }
}



// coverpassword() is responsible for to convert the password to * while taking it as an input
//char coverpassword(string password) {
//    char a;
//    int i = 0;
//    while (0 == 0) {
//        a = getch();
//        if ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || (a >= '0' && a <= '9')) {
//            password[i] = a;
//            ++i;
//            cout << "*";
//        }
//        if (a == '\b' && i >= 1) //if user typeed back space .
//            //i should be greater than .
//        {
//            cout << "\b \b";//run the char behind the cursor.
//            --i;
//        }
//
//        if (a == '\r') // if enter pressed
//        {
//            password[i] = '\0'; // null means end of string.
//            break;
//        }
//
//
//    }
//    return 0;
//}






// email_registration() is responsible for taking the email ,checking if it was not used in any registration before,
// checking what if it follows the correct email format and then save it in the database file
void email_registration(){
    auto wks = doc.workbook().worksheet("Sheet1");
    int counter = 0;

    //  registration : email section.
    cout << "please enter yor email:-  ";
    getline(cin,userInfoLoad.email);


    // Checking if the email is previously stored in the file
    while(true){
        if(email_cellColumn_map[userInfoLoad.email] != 0){
            cout << "invalid email its used before "
                    "please enter another one\n"
                    "please enter a valid email here:- ";
            cin.clear();
            getline(cin,userInfoLoad.email);

        }
        else{
            break;
        }
    }

    // checking for a correct domain name in the email name
    while(true){

        if (userInfoLoad.email.find("@gmail.com") == string::npos
            & userInfoLoad.email.find("@yahoo.com") == string::npos
            & userInfoLoad.email.find("@hotmail.com") == string::npos){
            cout << "invalid email the domain name i.e:(which is the @ character and what follows it ex: @gmail.com ) should"
                    "be written correctly\n"
                    "please enter your valid  email here:- ";
            cin.clear();
            getline(cin,userInfoLoad.email);
        }
        else{
            break;
        }


    }


    //  checking for a correct local name length and making the counter for the local name
    while(true){

        // to make a counter to count the local name characters
        for (int i = 0;i < userInfoLoad.email.length(); i++){
            counter += 1;
            if (userInfoLoad.email[i] == '@'){
                counter -= 1;
                break;
            }
        }

        // To make sure that the user name is not formed from more then 64 characters.
        if(counter > 10 ){
            cout << "invalid email the  local name i.e: (which is what is before the @ character in your email name) should be less than 64 character\n"
                    "please enter your valid  email here:-  ";
            cin.clear();
            getline(cin,userInfoLoad.email);
            counter = 0;

        }
        else{
            break;
        }
    }

    auto cell = wks.cell(row_number,column_number);
    cell.value() = userInfoLoad.email;
    column_number+=1;
}


// phoneNumber_registration() is responsible for  taking the phone number
// checking what if it follows the correct egyptian phone number format and then save it in the database file
void phoneNumber_registration(){

    auto wks = doc.workbook().worksheet("Sheet1");
    // registration : phone number section.
    cout << "please enter your Egyptian phone number:-  ";
    getline(cin, userInfoLoad.phone_number);
    while (true){

        if (userInfoLoad.phone_number.substr(2,1) != "0" && userInfoLoad.phone_number.substr(2,1) != "1"
            && userInfoLoad.phone_number.substr(2,1) != "2" && userInfoLoad.phone_number.substr(2,1) != "5"){
            cout << "Invalid number you should enter an Egyptian number (starts with 010 or 011 or 012 or 015)\n";
            cout << "please enter your Egyptian phone number:-  ";
            cin.clear();
            getline(cin, userInfoLoad.phone_number);
        }

        else if (userInfoLoad.phone_number.substr(0,2) != "01"){
            cout << "Invalid number you should enter an Egyptian number (starts with 01)\n";
            cout << "please enter your Egyptian phone number:-  ";
            cin.clear();
            getline(cin, userInfoLoad.phone_number);
        }

        else if (userInfoLoad.phone_number.length() != 11){
            cout << "Invalid number you should enter an Egyptian number (should be just 11 digits)\n";
            cout << "please enter your Egyptian phone number:-  ";
            cin.clear();
            getline(cin, userInfoLoad.phone_number);
        }

        else{
            break;
        }
    }




    email_cellColumn_map[userInfoLoad.email] = (email_cellColumn_map.size()) + 1;
    auto cell4 = wks.cell(row_number,column_number);
    cell4.value() = userInfoLoad.phone_number;
    column_number+=1;
}



//  userName_registration() is responsible for taking the username
// checking what if it follows the correct username format and then save it in the database file
void userName_registration(){
    auto wks = doc.workbook().worksheet("Sheet1");

    //  registration : username section.
    cout << "please enter your username:-  ";
    getline(cin ,userInfoLoad.username);

    // checking for the correct user name format
    while (userInfoLoad.username.find_first_not_of("_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")!= string::npos){
        cout << "invalid username it can only contain: (–) or letters, but not spaces, digits or other special characters\n"
                "please enter your valid username:-  ";
        cin.clear();
        getline(cin,userInfoLoad.username);
    }



    auto cell3 = wks.cell(row_number,column_number);
    cell3.value() = userInfoLoad.username;
    column_number+=1;
}

void password_registration (){

    auto wks = doc.workbook().worksheet("Sheet1");

    string password_check;

    //  registration : password section.
    cout << "characteristics of strong password :\n"<<"1- it should be at least 12 characters.\n"
         <<"2-it should have lower and upper case letters\n"<<"3-it should be formed from letters and number\ns"
         <<"4-it should not have spaces or special characters\n";

    cout << "please enter your password:-  ";

    getline(cin, userInfoLoad.password);


    //checking for all the strong passwords rules
    while (true) {
        if (userInfoLoad.password.find_first_of("abcdefghijklmnopqrstuvwxyz") != string::npos and
            userInfoLoad.password.find_first_of("0123456789") != string::npos and
            userInfoLoad.password.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos and userInfoLoad.password.length() > 12 ){
            break;

        }
        else{
            cout << "your password should just have at least 1 lowercase, 1 uppercase and 1 digit in it\n"
                    "and it should be more than 12 letters\n"
                    "please enter a valid password:  ";
            getline(cin, userInfoLoad.password);
        }
    }




    cout << "please enter your password again for verification:-  ";
    getline(cin,password_check);

    //  checking for the password verification
    while(password_check != userInfoLoad.password){
        cout << " wrong password they are not the same :(\n"
                "please enter your password again for verification:-  ";
        getline(cin,password_check);
    }



    username_password_map[userInfoLoad.username] = userInfoLoad.password;
    password_cellColumn_map[userInfoLoad.password] = (password_cellColumn_map.size()) + 1;


    // for storing the password in the file encrypted
    for (int i =0; i < userInfoLoad.password.length();i++){
        userInfoLoad.password[i] += 1;
    }

    auto cell2 = wks.cell(row_number,column_number);
    cell2.value() =userInfoLoad.password;

    column_number+=1;

    row_number = 1 + username_password_map.size();
    column_number= 1;


}

// login is responsible for the login function
void login(){


    int counter = 0,test = 0;


    cout << "please enter your id to log in :-  ";
    getline(cin ,userInfotake.username);

    cout << "please enter your password to log in:-  ";
    getline(cin, userInfotake.password);

    // checking for just three times if the user entered an incorrect data then it prevents the user from the login in
    while(true){

        // checks if this username and this password stored in the system database or not
        if (username_password_map[userInfotake.username] != 0 and password_cellColumn_map[userInfotake.password] != 0  ){
            test += 1;
        }

        //if the test that checks if this username and this password stored in the system database succeed then login success
        if(test > 0){
            cout << "Login success"<< " Welcome :) " + userInfotake.username;
            break;
        }

        // if the test failed then login failed
        else if( test==0 ){
            cout << " :( log in failed Wrong id or password please try again\n";

            cout << "please enter your username:-  ";
            getline(cin ,userInfotake.username);

            cout << "please enter your password:-  ";
            getline(cin, userInfotake.password);
            counter+=1;
        }

        // checks if the user entered an incorrect data for three times or not and if so it prevents the user from the log in
        if(counter == 2){
            cout << "\nAccess denied :(";
            break;
        }
    }


}



// change_password() is responsible for changing the user password if the user had personal information on the system database
void change_password(){

    auto wks = doc.workbook().worksheet("Sheet1");
    int cell_number_of_new_pasword;


    string current_password ,new_password, password_check;


    login();

    cout << "please enter the current password:- ";
    getline(cin,current_password);

    // checks if the password was not existed in the system database
    while (true){

        if (password_cellColumn_map[current_password] == 0) {
            cout << "Wrong password :(\n"
                    "please enter the current password:- ";
            getline(cin,current_password);
        }
        else{
            break;
        }
    }

    cout << "characteristics of strong password :\n"<<"1- it should be at least 12 characters.\n"
         <<"2-it should have lower and upper case letters\n"<<"3-it should be formed from letters and number\ns"
         <<"4-it should not have spaces or special characters\n";

    cout << "please enter your new password:-  ";

    getline(cin, new_password);

    //checking for all the strong passwords rules
    while (true) {
        if (new_password.find_first_of("abcdefghijklmnopqrstuvwxyz") != string::npos and
            new_password.find_first_of("0123456789") != string::npos and
            new_password.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") != string::npos and new_password.length() > 12 ){
            break;

        }
        else{
            cout << "your password should just have at least 1 lowercase, 1 uppercase, 1 digit in it\n"
                    "and it should be more than 12 letters\n"
                    "please enter a valid password:  ";
            getline(cin, new_password);
        }
    }



    cout << "please enter your password again for verification:-  ";
    getline(cin,password_check);

    //  checking for the new password verification
    while(password_check != new_password){
        cout << " wrong password they are not the same :(\n"
                "please enter your password again for verification:-  ";
        getline(cin,password_check);
    }


    username_password_map[userInfotake.username] = new_password ;
    cell_number_of_new_pasword = password_cellColumn_map[current_password];
    password_cellColumn_map.erase(current_password);
    password_cellColumn_map[new_password] = cell_number_of_new_pasword;

    // for password encryption before storing in the database file
    for (int i =0; i < new_password.length();i++){

        new_password[i] += 1;
    }
    auto cell2 = wks.cell(password_cellColumn_map[current_password],4);
    cell2.value() = new_password;
}

#endif  //LOG_IN_APP_PROGRAM_FUNCTIONS_H