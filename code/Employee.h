#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// class to store information about each Employee and perform operations on them
class Employee{
    protected:
    // protected so the derived classes can inherit them
        string name;
        string password;
        string position;
        string department;
        string type;
        vector<string> features; // features vector stores all the features that each employee has so its easier to print in menus
        bool admin_access;

    // office defined as a friend class because it has operations that might need access to protected variables in employee
    friend class Office;

    public:
        // constructor
        Employee(string name_in, string password_in, string position_in, string department_in, bool admin_access_in = false) 
        : name(name_in), password(password_in), position(position_in), department(department_in), admin_access(admin_access_in) {
            // adding features
            features.push_back("Name");
            features.push_back("Position");
            features.push_back("Department");

            // setting type (although no employee will ever be standard)
            type = "Standard";
        }

        // function to edit personal information about an employee based on selection from personalInfoMenu() and admin_access of the user trying to edit
        // virtual cause each derived class has different attributes and features to edit
        void virtual editPersonalInfo(int selection, bool admin_access) {
            // placeholder for user input
            string temp;

            // edit personal information based on user selection
            switch (selection){
                case 1:
                    cout << "What do you want the new name to be?" << endl;
                    getline(cin, temp); // getline cause the name might have spaces
                    this->name = temp;
                    cout << "Name changed." << endl;
                    break;
                case 2:
                    cout << "What do you want the new position to be?" << endl;
                    cin >> temp;
                    this->position = temp;
                    cout << "Position changed." << endl;
                    break;
                case 3:
                    cout << "What do you want the new department to be?" << endl;
                    cin >> temp;
                    this->department = temp;
                    cout << "Department changed." << endl;
                    break;
                default:
                    // error message if the input is invalid
                    cout << "Invalid input." << endl;
            }
        }

        // purely virtual function because no employee will ever be declared as just Employee
        
        virtual double calculatePay() const = 0;

        // function to view employee information
        // virtual cause each derived class has different attributes and features to view
        virtual void viewInfo() {
            cout << "Name: " << name << endl;
            cout << "Position: " << position << endl;
            cout << "Department: " << department << endl;
        }

        // function to allow the user to pick what personal information they want to edit
        void personalInfoMenu(bool admin_access_in = false) {
            // placeholder
            int selection;
            char temp;
            
            // either the external user accessing this function has to have admin access or the employee themselves
            bool admin_access_internal = (this->admin_access || admin_access_in);

            cout << "What personal information do you want to edit?" << endl << endl;

            // print out of the list of features that the user can pick to edit by looping through all the editable features as stored in the vector
            int i = 0;
            for (const string& feature : features) {
                cout << (++i) << ") " << feature << endl;
            }
            
            // looping until the user provides a valid input
            while (1) {
                cout << endl << "Enter your selection: ";
                cin >> selection;
                
                // checking if the selection is valid and within range
                if (selection > 0 && selection <= features.size()) {
                    editPersonalInfo(selection, admin_access); // edit employee information accordingly
                    
                    // check if the user wants to continue editing information
                    cout << "Do you want to edit another feature? (Y/N)" << endl;
                    cin >> temp;

                    // if the user wants to continue editing employee information, rerun the loop
                    if (toupper(temp) == 'Y') {
                        cout << "What other information do you want to edit?" << endl;
                        continue;
                    } else {
                        // if the user wants to exit, break from the loop
                        break;
                    }
                } else {
                    // error message for invalid input
                    cout << "Invalid Input. Please try again." << endl;
                }
            }
        }

        // gettters
        string getName() const {
            return name;
        }

        bool getAccess() const {
            return admin_access;
        }

         string getType(){
            return type;
        };

        // overloading the operator == 
        bool operator==(const pair<string, string>& credentials) const {
            // check if the name and password match the first and second element of the pair accordingly
            return (this->name == credentials.first && this->password == credentials.second);
        }


        // function to print information about the employee
        // virtual cause each derived class has different attributes and features to print
        void virtual printInfo() const{
            cout << endl << endl << "Name: " << " " << name
             << " , " << "Position: " <<  " " << position
             << " , " << "Department: " << " " << department
             << " , " << "Type: " << " " << type;
        }

        // function to write information about the employee to given stream
        // virtual cause each derived class has different attributes and features to write
        void virtual writeToCSV(ofstream &outfile) const {
            outfile << name << ',' << password << ',' << position << ',' << ((admin_access) ? 1:0) << ',' << department << ',';
        }
};

// derived class for Hourly Employees
class HourlyEmployee : public Employee {
    private:
        // additional variables specific to the employee type
        int hourlyRate;
        double hoursWorked;
    public:
        // Constructor
        HourlyEmployee(string name_in, string password_in, string position_in, string department_in, int hourlyRate_in, double hoursWorked_in = 0, bool admin_access_in = false)
        : Employee(name_in, password_in, position_in, department_in, admin_access_in), hourlyRate(hourlyRate_in), hoursWorked(hoursWorked_in) {
            // adding features specific to the employee type
            features.push_back("Hourly Rate");
            features.push_back("Hours Worked");

            // setting the employee type
            type = "Hourly";
        }

        // overriding the viewInfo() from the parent class
        void viewInfo()  {
            Employee::viewInfo(); // calling the function from the parent class to print the basic shared information

            // printing additional information specific to the employee type
            cout << "Hourly Rate: " << hourlyRate << endl;
            cout << "Hours Worked: " << hoursWorked << endl << endl;
        }

        // overriding the editPersonalInfo() from the parent class to edit information specific to the employee type
        void editPersonalInfo(int selection, bool admin_access_in) {

            // placeholder
            string temp;
            double num;
            int num_int;

            // same purpose as that in the parent class
            bool admin_in = (this->admin_access || admin_access_in);

            // allowing the user to edit specific information based on their selection
            switch (selection){
                case 1:
                    cout << "What do you want the new name to be?" << endl;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                    getline(cin, temp);
                    this->name = temp;
                    cout << "Name changed." << endl;
                    break;
                case 2:
                    cout << "What do you want the new position to be?" << endl;
                    cin >> temp;
                    this->position = temp;
                    cout << "Position changed." << endl;
                    break;
                case 3:
                    cout << "What do you want the new department to be?" << endl;
                    cin >> temp;
                    this->department = temp;
                    cout << "Department changed." << endl;
                    break;
                case 4:
                    // can only edit this information if the user editing has admin access
                    if (admin_in) {
                        cout << "What do you want the new hourly rate to be?" << endl;
                        cin >> num;
                        this->hourlyRate = num;
                        cout << "Hourly Rate changed." << endl;
                    } else {
                        // user can't edit if they don't have admin access
                        cout << "Admin access required to edit hourly rate." << endl;
                    }
                    break;
                case 5:
                    cout << "How many hours do you want to add?" << endl;
                    cin >> num_int;
                    this->hoursWorked += num_int;
                    cout << "Hours logged." << endl;
                    break;
                default:
                    // error message for invalid input
                    cout << "Invalid input." << endl << endl;
            }
        }

        // overriding calculatePay() function from the parent class
        double calculatePay() const {
            return (hourlyRate * hoursWorked);
        }

        // overriding the printInfo() from the parent class
        void printInfo() const{
            Employee::printInfo(); // calling the function from the parent class to print the basic shared information
            cout << " , " << "Hourly Rate: " <<  " " << hourlyRate
             << " , " << "Hours Worked: " << " " << hoursWorked
             << " , " << "Compensation Due: " << " " << calculatePay() << endl;
        }

        // overriding the writeToCSV() from the parent class
        void writeToCSV(ofstream &outfile) const {
            Employee::writeToCSV(outfile); // calling the function from the parent class to write the basic shared information
            outfile << type << ",," << hourlyRate << "," << hoursWorked << ",,," << endl;
        }
};

// derived class for Salaried Employees
class SalariedEmployee : public Employee {
    private:
        // additional variables specific to the employee type
        double salary;
    public:
        // Constructor
        SalariedEmployee(string name_in, string password_in, string position_in,  string department_in, double salary_in = 0, bool admin_access_in = false)
        : Employee(name_in, password_in, position_in, department_in,  admin_access_in), salary(salary_in) {
            // adding features specific to the employee type
            features.push_back("Salary");

            // setting the employee type
            type = "Salaried";
        }

        // overriding the viewInfo() from the parent class
        void viewInfo(){
            Employee::viewInfo(); // calling the function from the parent class to view the basic shared information
            cout << "Salary: " << salary << endl;
        }

        // overriding the editPersonalInfo() from the parent class to edit information specific to the employee type
        void editPersonalInfo(int selection, bool admin_access_in){
            // placeholder
            string temp;
            double num;

            // same purpose as that in the parent class
            bool admin_in = (this->admin_access || admin_access_in);

            // allowing the user to edit specific information based on their selection
            switch (selection){
                case 1:
                    cout << "What do you want the new name to be?" << endl;
                    getline(cin, temp);
                    this->name = temp;
                    cout << "Name changed." << endl;
                    break;
                case 2:
                    cout << "What do you want the new position to be?" << endl;
                    cin >> temp;
                    this->position = temp;
                    cout << "Position changed." << endl;
                    break;
                case 3:
                    cout << "What do you want the new department to be?" << endl;
                    cin >> temp;
                    this->department = temp;
                    cout << "Department changed." << endl;
                    break;
                case 4:
                    // can only edit this information if the user editing has admin access
                    if (admin_in) {
                        cout << "What do you want the new salary to be?" << endl;
                        cin >> num;
                        this->salary = num;
                        cout << "Salary changed." << endl;
                    } else {
                        // user can't edit if they don't have admin access
                        cout << "Admin access required to edit salary." << endl;
                    }
                    break;
                default:
                    cout << "Invalid input." << endl;
            }
            
        }

        // overriding calculatePay() function from the parent class
        double calculatePay() const   {
            return salary;
        }

        // overriding the printInfo() from the parent class
        void printInfo() const{
            Employee::printInfo(); // calling the function from the parent class to print the basic shared information
            cout << " , " << "Salary: " << " " << salary
             << " , " << "Compensation Due: " << " " << calculatePay() << endl;
        }

         // overriding the writeToCSV() from the parent class
        void writeToCSV(ofstream &outfile) const {
            Employee::writeToCSV(outfile); // calling the function from the parent class to write the basic shared information
            outfile << type << "," << salary << ",,,,," << endl;
        }
};

// derived class for Commissioned Employees
class CommissionedEmployee : public Employee {
    private:
        // additional variables specific to the employee type
        double baseSalary;
        double commissionRate;
        int numSales;
    public:
        // Constructor
        CommissionedEmployee(string name_in, string password_in, string position_in, string department_in, double baseSalary_in, double commissionRate_in, int numSales_in = 0, bool admin_access_in = false)
        : Employee(name_in, password_in, position_in, department_in, admin_access_in), baseSalary(baseSalary_in), commissionRate(commissionRate_in), numSales(numSales_in) {
            // adding features specific to the employee type
            features.push_back("Base Salary");
            features.push_back("Commission Rate");
            features.push_back("Number of Sales");

            // setting the type of employment
            type = "Commissioned";
        }

        // overriding the viewInfo() from the parent class
        void viewInfo()   {
            Employee::viewInfo();  // calling the function from the parent class to write the basic shared information
            cout << "Base Salary: " << baseSalary << endl;
            cout << "Commission Rate: " << commissionRate << endl;
            cout << "Number of Sales: " << numSales << endl;
        }

         // overriding the editPersonalInfo() from the parent class to edit information specific to the employee type
        void editPersonalInfo(int selection, bool admin_access_in){
            // placeholder
            string temp;
            double num;
            int num_int;

            // same purpose as that in the parent function
            bool admin_in = (this->admin_access || admin_access_in);

            // allowing the user to edit specific information based on their selection
            switch (selection){
                case 1:
                    cout << "What do you want the new name to be?" << endl;
                    cin >> temp;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, temp);
                    cout << "Name changed." << endl;
                    break;
                case 2:
                    cout << "What do you want the new position to be?" << endl;
                    cin >> temp;
                    this->position = temp;
                    cout << "Position changed." << endl;
                    break;
                case 3:
                    cout << "What do you want the new department to be?" << endl;
                    cin >> temp;
                    this->department = temp;
                    cout << "Department changed." << endl;
                    break;
                case 4:
                    // can only edit this information if the user editing has admin access
                    if (admin_in) {
                        cout << "What do you want the new base salary to be?" << endl;
                        cin >> num;
                        this->baseSalary = num;
                        cout << "Base Salary changed." << endl;
                    } else {
                        // user can't edit if they don't have admin access
                        cout << "Admin access required to edit base salary." << endl;
                    }
                    break;
                case 5:
                    // can only edit this information if the user editing has admin access
                    if (admin_in) {
                        cout << "What do you want the new commission rate to be?" << endl;
                        cin >> num;
                        this->commissionRate = num;
                        cout << "Commission Rate changed." << endl;
                    } else {
                        // user can't edit if they don't have admin access
                        cout << "Admin access required to edit commission rate." << endl;
                    }
                    break;
                case 6:
                    cout << "How many sales do you want to add?" << endl;
                    cin >> num_int;
                    this->numSales += num_int;
                    cout << "Sales added." << endl;
                    break;
                default:
                    // error message for invalid input
                    cout << "Invalid input or you need admin privileges to make these changes." << endl;
            }
        }

        // overriding calculatePay() function from the parent class
        double calculatePay() const   {
            return (baseSalary + (commissionRate * numSales));
        }

        // overriding the printInfo() from the parent class
        void printInfo() const{
            Employee::printInfo();  // calling the function from the parent class to print the basic shared information
            cout << " , " << "Base Salary: " << " " << baseSalary
             << " , " << "Commission Rate: " << " " << commissionRate
             << " , " << "Compensation Due: " << " " << calculatePay() << endl;
        }

        // overriding the writeToCSV() from the parent class
        void writeToCSV(ofstream &outfile) const {
            Employee::writeToCSV(outfile); // calling the function from the parent class to write the basic shared information
            outfile << type << ",,,," << baseSalary << "," << commissionRate << "," << numSales << endl;
        }
};

               