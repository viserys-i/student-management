#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Student {
private:
    string id;
    string name;
    float gpa;

public:
    Student() {}
    Student(string _id, string _name, float _gpa) : id(_id), name(_name), gpa(_gpa) {}

    void input() {
        cout << "Nhap ma sinh vien: ";
        cin >> id;
        cin.ignore();
        cout << "Nhap ho ten: ";
        getline(cin, name);
        cout << "Nhap GPA: ";
        cin >> gpa;
    }

    void display() const {
        cout << left << setw(15) << id 
             << setw(30) << name 
             << setw(10) << fixed << setprecision(2) << gpa << endl;
    }

    string getId() const { return id; }
    string getName() const { return name; }
    float getGpa() const { return gpa; }
};

class StudentManager {
private:
    vector<Student> students;
    const string filename = "students.txt";

public:
    void addStudent() {
        Student s;
        s.input();
        students.push_back(s);
        cout << "Them sinh vien thanh cong!\n";
    }

    void displayList() {
        if (students.empty()) {
            cout << "Danh sach trong!\n";
            return;
        }
        
        cout << left << setw(15) << "Ma SV" 
             << setw(30) << "Ho ten" 
             << setw(10) << "GPA" << endl;
        cout << string(55, '-') << endl;
        
        for (const auto& s : students) {
            s.display();
        }
    }

    void searchStudent() {
        string searchId;
        cout << "Nhap ma sinh vien can tim: ";
        cin >> searchId;

        bool found = false;
        for (const auto& s : students) {
            if (s.getId() == searchId) {
                cout << "\nThong tin sinh vien:\n";
                cout << left << setw(15) << "Ma SV" 
                     << setw(30) << "Ho ten" 
                     << setw(10) << "GPA" << endl;
                cout << string(55, '-') << endl;
                s.display();
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Khong tim thay sinh vien voi ma " << searchId << endl;
        }
    }

    void deleteStudent() {
        string deleteId;
        cout << "Nhap ma sinh vien can xoa: ";
        cin >> deleteId;

        auto it = students.begin();
        bool found = false;
        while (it != students.end()) {
            if (it->getId() == deleteId) {
                it = students.erase(it);
                found = true;
                cout << "Xoa sinh vien thanh cong!\n";
                break;
            } else {
                ++it;
            }
        }
        if (!found) {
            cout << "Khong tim thay sinh vien voi ma " << deleteId << endl;
        }
    }

    void saveToFile() {
        ofstream outFile(filename);
        if (!outFile) {
            cout << "Loi mo file de ghi!\n";
            return;
        }

        for (const auto& s : students) {
            outFile << s.getId() << endl;
            outFile << s.getName() << endl;
            outFile << s.getGpa() << endl;
        }
        outFile.close();
        cout << "Luu file thanh cong!\n";
    }

    void readFromFile() {
        ifstream inFile(filename);
        if (!inFile) {
            cout << "Loi mo file de doc!\n";
            return;
        }

        students.clear();
        string id, name;
        float gpa;
        
        while (inFile >> id) {
            inFile.ignore();
            getline(inFile, name);
            inFile >> gpa;
            students.push_back(Student(id, name, gpa));
        }
        inFile.close();
        cout << "Doc file thanh cong!\n";
    }
};

int main() {
    StudentManager manager;
    int choice;

    do {
        cout << "\n=== QUAN LY SINH VIEN ===\n";
        cout << "1. Them sinh vien\n";
        cout << "2. Hien thi danh sach\n";
        cout << "3. Tim kiem sinh vien\n";
        cout << "4. Xoa sinh vien\n";
        cout << "5. Ghi vao file\n";
        cout << "6. Doc tu file\n";
        cout << "0. Thoat\n";
        cout << "Nhap lua chon: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager.addStudent();
                break;
            case 2:
                manager.displayList();
                break;
            case 3:
                manager.searchStudent();
                break;
            case 4:
                manager.deleteStudent();
                break;
            case 5:
                manager.saveToFile();
                break;
            case 6:
                manager.readFromFile();
                break;
            case 0:
                cout << "Tam biet!\n";
                break;
            default:
                cout << "Lua chon khong hop le!\n";
        }
    } while (choice != 0);

    return 0;
}a\
