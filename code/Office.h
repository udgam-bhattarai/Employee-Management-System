#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "Employee.h"

using namespace std;

// function to convert string to boolean
inline bool stringToBool(const string& str) {
    if (str == "1") {
        return true;
    } 
    return false;
}

// Office class to store data about all the employees and perform operations on them
class Office{
    private:
        string filename; // to store the file where all the information is stored
        string header; // the header of the file so it's easier to write to the file later
        vector<Employee*> employeeList; // list of all the employees from the file
    public:
        // constructor
        Office(string filename_in){
            filename = filename_in;

            // placeholder for input read from the file
            string temp;
            string line;

            // opening a filestream for the given file
            ifstream istream;
            istream.open(filename);

            // getting the header and storing it
            getline(istream, header);

            // loop while there is information to be read in the file
            while(getline(istream, line)){
                // defining a stringstream for each line in the file so its easier to extract information
                stringstream ss(line);

                // placeholder for information read from the file
                string name, password, position, admin_access, department, type;

                // extracting comma separated information from each line
                getline(ss, name, ',');
                getline(ss, password, ',');
                getline(ss, position, ',');
                getline(ss, admin_access, ',');
                getline(ss, department, ',');
                getline(ss, type, ',');

                // once the type is extracted, extract other information from the file based on the type of the employee
                if (type == "Salaried"){
                    // placeholder
                    string salary;

                    // extracting data
                    getline(ss, salary, ',');

                    // defining the specific Employee object and adding it to the list of employees
                    employeeList.push_back(new SalariedEmployee(name, password, position, department, stod(salary), stringToBool(admin_access)));
                }
                else if (type == "Hourly"){
                    string hourly_rate, hours_worked;

                    // ignoring values for employees of other type
                    getline(ss, temp, ',');

                    // extracting data
                    getline(ss, hourly_rate, ',');
                    getline(ss, hours_worked, ',');

                    // defining the specific Employee object and adding it to the list of employees
                    employeeList.push_back(new HourlyEmployee(name, password, position, department, stod(hourly_rate), stoi(hours_worked), stringToBool(admin_access)));
                }
                else {
                    // placeholder
                    string base_salary, commission_rate, num_sales;

                    // ignoring values for employees of other type
                    getline(ss, temp, ',');
                    getline(ss, temp, ',');
                    getline(ss, temp, ',');

                    // extracting data
                    getline(ss, base_salary, ',');
                    getline(ss, commission_rate, ',');
                    getline(ss, num_sales, ',');

                    // defining the specific Employee object and adding it to the list of employees
                    employeeList.push_back(new CommissionedEmployee(name, password, position, department, stod(base_salary), stod(commission_rate), stoi(num_sales), stringToBool(admin_access)));
                }
            }

            // closing the filestream
            istream.close();
        }

        // function for adding a new employee
        void addEmployee(){
            // placeholders 
            int temp;
            string name, password, position, department, admin;

            // asking for user input for information about the new employee
            cout << "Name: ";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            getline(cin, name); // using getline because the name might contain spaces

            cout << "Password: ";
            cin >> password;

            cout << "Position: ";
            cin >> position;

            cout << "Department: ";
            cin >> department;

            cout << "Admin Access (0/1): ";
            cin >> admin;

            // asking the user to ask what kind of employee they want the new employee to be
            cout << "What type of employee do you want to add? " << endl;
            cout << "(1) Salaried Employee \t  (2) Commissioned Employee \t  (3) Hourly Employee" << endl;

            // looping until the user selects a valid option
            while(1){
                cout << endl << "Enter your selection: ";
                cin >> temp;

                // if the user input is within the reange of options
                if (temp > 0 && temp < 4){
                    switch(temp){
                        case 1: //Salaried Employee
                            // placeholder
                            double salary;

                            // taking input
                            cout << "Salary: ";
                            cin >> salary;

                            // creating new specific type of employee based on the user's selections
                            employeeList.push_back(new SalariedEmployee(name, password, position, department, salary, stringToBool(admin))); // Add the employee to the list
                            break; 
                        
                        case 2:  // Commissioned Employee
                            // placeholder
                            double baseSalary, commissionRate;
                            int numSales;

                            // taking input
                            cout << "Base Salary: ";
                            cin >> baseSalary;
                            cout << "Commission Rate: ";
                            cin >> commissionRate;
                            cout << "Number of Sales: ";
                            cin >> numSales;

                            // creating new specific type of employee based on the user's selections
                            employeeList.push_back(new CommissionedEmployee(name, password, position, department, baseSalary, commissionRate, numSales, stringToBool(admin)));
                            break;

                        case 3:  // Hourly Employee
                            //placeholder
                            double hourlyRate, hoursWorked;

                            // taking input
                            cout << "Hourly Rate: ";
                            cin >> hourlyRate;
                            cout << "Hours Worked: ";
                            cin >> hoursWorked;

                            // creating new specific type of employee based on the user's selections
                            employeeList.push_back(new HourlyEmployee(name, password, position, department, hourlyRate, hoursWorked, stringToBool(admin)));
                            break;
                    }
                    cout << "Employee " << name << " added.";
                    break;

                }
                
                // Error message for invalid input
                cout << "Invalid Input. Please try again.";
            }
        }


        // function to check if the user can log in successfully or not based on the username and password they input
        Employee* login(string user, string password){
            // defining a pair to store the username and password
            pair<string, string> credentials = make_pair(user, password);

            // iterating through all the employees
            for (Employee* employee: employeeList){
                if (*employee == credentials){
                    // if the credentials match return the pointer to the matched employee
                    return employee;
                }
            }

            // if the credentials don't match any employee, return a null pointer
            return nullptr;
        }

        // function to print information about all the employees
        void viewEmployeeList(){
            for (Employee* c: employeeList){
                c->printInfo();
            }
        }

        // function to print information about all the employees matching the department specified by the user
        void viewEmployeeListbyDepartment(string department){
            string department_in_casein = department;
            // case sensitivity handling (1)
            transform(department.begin(), department.end(), department.begin(), ::tolower);
            for (Employee* c: employeeList){
                string department_employee = c->department;
                // case sensitivity handling (2)
                transform(department_employee.begin(), department_employee.end(), department_employee.begin(), ::tolower);
                if (department_in_casein == department_employee){
                    c->printInfo();
                }
            }
        }

        // function to print information about all the employees matching the position specified by the user
        void viewEmployeeListbyPosition(string position){
            string position_in_casein = position;
            // case sensitivity handling (1)
            transform(position_in_casein.begin(), position_in_casein.end(), position_in_casein.begin(), ::tolower); // Convert user input to lowercase

            vector<Employee*>::iterator it;
            for (it = employeeList.begin(); it != employeeList.end(); ++it) {
                string position_employee = (*it)->position;
                // case sensitivity handling (2)
                transform(position_employee.begin(), position_employee.end(), position_employee.begin(), ::tolower); // Convert employee's position to lowercase

                if (position_employee == position_in_casein) { // Compare the converted lowercase positions
                    (*it)->printInfo();
                }
            }
        }


        // function to print information about all the employees matching the type of employment specified by the user
        void viewEmployeeListbyEmploymentType(string type){
            string type_in_casein = type;
            // case sensitivity handling (1)
            transform(type_in_casein.begin(), type_in_casein.end(), type_in_casein.begin(), ::tolower);
            for (Employee* c: employeeList){
                string type_employee = c->type;
                // case sensitivity handling (2)
                transform(type_employee.begin(), type_employee.end(), type_employee.begin(), ::tolower);
                if (type_employee == type_in_casein){
                    c->printInfo();
                }
            }
        }


        // function to find and return the employee matching the name given by the user
        Employee* findEmployee(string name){
            // iterating through the list of all employees
            for (Employee* employee: employeeList){
                if (name == employee->getName()){
                    // if the name input by user matches that of any employee return the pointer to the object of that employee
                    return employee;
                }
            }

            // if the name doesn't match any employee, return a null pointer
            return nullptr;
        }

        // Destructor for the class
       ~Office(){
            // output stream to write to the file
            ofstream ofile;
            ofile.open("temp.csv");
            
            // writing the header to the file
            ofile << header << endl;

            // writing information about the employee individually to the file
            for (Employee* employee : employeeList) {
                employee->writeToCSV(ofile);
            }

            // closing the file stream
            ofile.close();
            
            // renaming the file
            if (remove(filename.c_str()) != 0) {
                cerr << "Error deleting file: " << filename << endl;
            }

            if (rename("temp.csv", filename.c_str()) != 0) {
                cerr << "Error renaming file to: " << filename << endl;
            }
            
        }

};
