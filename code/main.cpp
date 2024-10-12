#include <iostream>
#include <vector>
#include <string>
#include "Office.h"


int main() {
    // boolean variable to check if the user wants the program to run
    bool run = false;

    // defining a placeholder object for the Employee pointer for the employee that logs in
    Employee* loggedEmployee = nullptr;

    // boolean variable to check if any user has been logged in
    bool loggedIn = false;

    // placeholder for the user inputs to username and password
    string userName;
    string password;

    // defining the Office object that gets data from Office.csv file
    Office* office = new Office("Office.csv");

    // placeholder variable for user selection
    int sel;

    cout << "-------------------- WELCOME TO EMPLOYEE MANAGEMENT SYSTEM ------------------------" << endl;

    // looping until the user decides to terminate the program
    do {
        cout << endl << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ MAIN MENU ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl << endl;
        cout << "(1) Login \t\t\t\t\t (2) Exit" << endl << endl << "Enter your selection: ";

        cin >> sel;

        if (cin.fail()) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore invalid input
            cout << "Invalid selection. Please enter a valid number." << endl;
            continue;
        }

        // do nothing if the user decides to login (this is handled by the rest of the program)
        if (sel == 1){

        } 
        else if (sel == 2){
            // set run to false and exit the loop
            run = false;
            break;
        }
        else{
            // if the input isn't one of the given options, prompt the user to retry
            cout << endl << "Invalid Input." << endl;
            continue;
        }

        // loop to get user input if the user decides to login but hasn't logged in yet
        while (!loggedIn) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clearing input buffer
            cout << endl <<  "User Name: ";
            getline(cin, userName); // using getline because the user names can contain spaces
            cout << "Password: ";
            cin >> password;

            // if the login information matches and is valid, recieves the pointer to the Employee object
            loggedEmployee = office->login(userName, password);
            
            // if loop if the information doesn't match any employee
            if (loggedEmployee != nullptr) {
                // sets loggedIn to true so the post login menu can be accessed
                loggedIn = true; 
                cout << endl << "------------------- You have logged in as " << loggedEmployee->getName() << " ------------------" << endl;
            } else {
                // if the input isn't valid
                cout << "Invalid credentials. Please try again." << endl;
            }
        }

        // accessing the logged in menu once the user has successfully logged in
        while (loggedIn) {
            // placeholder for user selection
            int selection;

            cout << endl << endl << "What do you want to do today?" << endl << endl;
            cout << "(1) View Personal Details" << endl;
            cout << "(2) Edit Personal Information" << endl;
            cout << "(3) Check Compensation Due" << endl;
            
            // display additional menu items if the user has admin access
            if (loggedEmployee->getAccess()) { // getAccess() checks for admin privileges
                cout << "(4) View Employee List" << endl;
                cout << "(5) Edit Employee Information" << endl;
                cout << "(6) Add New Employee" << endl;
            }

            cout << "(-1) to logout" << endl;

            cout << endl << "Enter your selection: ";
            cin >> selection;

            if (cin.fail()) {  // If the input is not a valid integer
                cin.clear();  // Clear error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
                cout << "Invalid selection. Please enter a valid number." << endl;
                continue;  // Return to the start of the loop
            }

            cout << endl;

            // performs operations based on the user selection
            switch (selection) {
                case -1:
                    // logs the user out and goes back to the main menu if the user input is -1
                    loggedIn = false;
                    break;
                case 1:
                    // displays information about the user 
                    loggedEmployee->viewInfo();
                    break;
                case 2:
                    // allows the user to edit personal information about themselves
                    loggedEmployee->personalInfoMenu();
                    break;
                case 3: 
                    // calculates and displays compensation due 
                    cout << endl << "Compensation Due: $" << loggedEmployee->calculatePay() << endl;
                    break;
                default:
                // if the user input doesn't match any of the options in the default user menu, check if they're an admin and have selected any options from the admin menu
                    if (loggedEmployee->getAccess()) {
                        switch (selection) {
                            case 4:
                                // place holder for user input
                                int view_option;
                                cout << "(1) View all Employees" << endl;
                                cout << "(2) View by Employment Type" << endl;
                                cout << "(3) View by Department" << endl;
                                cout << "(4) View by Position" << endl;

                                // loop until the user provides a valid input
                                while(1){ 
                                    int view_option;

                                    cout << endl << "Enter your selection: ";
                                    cin >> view_option;

                                     if (cin.fail()) {  // If the input is not a valid integer
                                        cin.clear();  // Clear error flag
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore invalid input
                                        cout << "Invalid selection. Please enter a valid number." << endl;
                                        continue;  // Return to the start of the loop
                                    }

                                    switch(view_option){
                                        case 1:
                                            // views all the employees
                                            office->viewEmployeeList();
                                            break;
                                        case 2:
                                            // views employees matching the employment type input by the user
                                            {
                                                string emp_type;
                                                cout << endl << "Employment Type: ";
                                                cin >> emp_type;
                                                office->viewEmployeeListbyEmploymentType(emp_type);
                                                break;
                                            }

                                        case 3:
                                            // views employees matching the department input by the user
                                            {
                                                string dep;
                                                cout << endl << "Department: ";
                                                cin >> dep;
                                                office->viewEmployeeListbyDepartment(dep);
                                                break;
                                            }
                                        
                                        case 4:
                                            // views employees matching the position input by the user
                                            {
                                                string position;
                                                cout << endl <<  "Position: ";
                                                cin >> position;
                                                office->viewEmployeeListbyPosition(position);
                                                break;
                                            }
                                        default:
                                            // error message if the input is invalid
                                            cout << "Invalid Input." << endl << endl;
                                            continue;
                                    }  
                                    break;
                                }
                                break;
                            case 5: {
                                // placeholder for user input
                                string temp;

                                // loop until the user provides a valid input
                                while(1){

                                    cout << "Name of Employee: ";
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    getline(cin, temp); // getline because the user input might contain spaces

                                    // recieves the employee matching the name input by the user
                                    Employee* employeeToEdit = office->findEmployee(temp);

                                    // if loop to check if the name matches a valid employee
                                    if (employeeToEdit != nullptr) {
                                        // if the user input matches a valid employee, display their information and allow the user to edit their personal information with admin access
                                        employeeToEdit->viewInfo();
                                        employeeToEdit->personalInfoMenu(true);
                                        break;
                                    } else {
                                        // error message if the employee is not found
                                        cout << "Employee not found." << endl;
                                    }
                                }
                                break;
                            }
                            case 6:
                                // allows the user to add an employee
                                office->addEmployee();
                                break;
                            default:
                                // error message if the selection is invalid
                                cout << "Invalid selection." << endl;
                                break;
                            
                        }
                    } else {
                        cout << "Invalid selection." << endl;
                    }

                    cout << endl;
            }
        }
    } while (!run);

    // deleting the office pointer which also writes all the updated information to file
    delete office;

    return 0;
}