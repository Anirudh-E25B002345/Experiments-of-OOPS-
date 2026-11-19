#include <iostream>
#include <iomanip>
#include <vector>
#include <memory>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <stdexcept>
using namespace std;

class Employee {
protected:
    int id; string name; double ded;
public:
    Employee(int i, string n, double d) : id(i), name(move(n)), ded(d) {
        if (id <= 0 || ded < 0) throw invalid_argument("Invalid ID/deduction.");
    }
    virtual ~Employee() = default;
    int getId() const { return id; }
    string getName() const { return name; }
    virtual double salary() const = 0;
    virtual string type() const = 0;
    virtual void update(double v1, double v2, double d) = 0;
    virtual void display() const = 0;
    virtual string toCsv() const = 0;
};

class FullTime : public Employee {
    double basic, allow;
public:
    FullTime(int i, string n, double b, double a, double d) : Employee(i, move(n), d), basic(b), allow(a) {
        if (b < 0 || a < 0) throw invalid_argument("Pay/allowance cannot be negative.");
    }
    double salary() const override { return basic + allow - ded; }
    string type() const override { return "Full-Time"; }
    void update(double b, double a, double d) override {
        if (b < 0 || a < 0 || d < 0) throw invalid_argument("Values cannot be negative.");
        basic = b; allow = a; ded = d;
    }
    void display() const override {
        cout << left << setw(8) << id << setw(20) << name << setw(12) << type() << right << fixed << setprecision(2) << setw(10) << basic << setw(10) << allow << setw(10) << ded << setw(10) << salary() << '\n';
    }
    string toCsv() const override { return "F," + to_string(id) + "," + name + "," + to_string(basic) + "," + to_string(allow) + "," + to_string(ded); }
};

class PartTime : public Employee {
    double rate, hrs;
public:
    PartTime(int i, string n, double r, double h, double d) : Employee(i, move(n), d), rate(r), hrs(h) {
        if (r < 0 || h < 0 || h > 744) throw invalid_argument("Invalid rate or hours (0-744).");
    }
    double salary() const override { return rate * hrs - ded; }
    string type() const override { return "Part-Time"; }
    void update(double r, double h, double d) override {
        if (r < 0 || h < 0 || h > 744 || d < 0) throw invalid_argument("Invalid values.");
        rate = r; hrs = h; ded = d;
    }
    void display() const override {
        cout << left << setw(8) << id << setw(20) << name << setw(12) << type() << right << fixed << setprecision(2) << setw(10) << rate << setw(10) << hrs << setw(10) << ded << setw(10) << salary() << '\n';
    }
    string toCsv() const override { return "P," + to_string(id) + "," + name + "," + to_string(rate) + "," + to_string(hrs) + "," + to_string(ded); }
};

class PayManager {
    vector<unique_ptr<Employee>> emps;
    Employee* find(int id) const {
        auto it = find_if(emps.begin(), emps.end(), [id](const auto& e) { return e->getId() == id; });
        return it == emps.end() ? nullptr : it->get();
    }
    template<typename T> static T readNum(const string& p, bool nonNeg = true) {
        T v;
        while (cout << p && (!(cin >> v) || (nonNeg && v < 0))) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
        }
        return v;
    }
    void save() const {
        ofstream out("employees.csv");
        out << "type,id,name,v1,v2,ded\n";
        for (const auto& e : emps) out << e->toCsv() << '\n';
    }
public:
    void load() {
        ifstream in("employees.csv"); string line, t, i, n, v1, v2, d; getline(in, line);
        while (getline(in, line)) {
            stringstream ss(line);
            if (!getline(ss, t, ',') || !getline(ss, i, ',') || !getline(ss, n, ',') || !getline(ss, v1, ',') || !getline(ss, v2, ',') || !getline(ss, d)) continue;
            try {
                if (t == "F") emps.push_back(make_unique<FullTime>(stoi(i), n, stod(v1), stod(v2), stod(d)));
                else if (t == "P") emps.push_back(make_unique<PartTime>(stoi(i), n, stod(v1), stod(v2), stod(d)));
            } catch (...) {}
        }
    }
    void add() {
        int id = readNum<int>("ID: ", false), t;
        if (id <= 0 || find(id)) { cout << "ID must be positive & unique.\n"; return; }
        cout << "Name: "; string name; getline(cin >> ws, name); replace(name.begin(), name.end(), ',', ' ');
        if ((t = readNum<int>("Type (1=Full, 2=Part): ")) != 1 && t != 2) { cout << "Invalid type.\n"; return; }
        double v1 = readNum<double>(t == 1 ? "Basic: " : "Rate: "), v2 = readNum<double>(t == 1 ? "Allowance: " : "Hours (0-744): "), d = readNum<double>("Deduction: ");
        if (t == 1) emps.push_back(make_unique<FullTime>(id, name, v1, v2, d));
        else emps.push_back(make_unique<PartTime>(id, name, v1, v2, d));
        save(); cout << "Added.\n";
    }
    void list() const {
        if (emps.empty()) { cout << "No employees.\n"; return; }
        cout << '\n' << left << setw(8) << "ID" << setw(20) << "Name" << setw(12) << "Type" << right << setw(10) << "Pay/Rate" << setw(10) << "Allow/Hr" << setw(10) << "Deduct" << setw(10) << "Net Pay" << '\n' << string(80, '-') << '\n';
        for (const auto& e : emps) e->display();
    }
    void search() const {
        if (auto* e = find(readNum<int>("Search ID: ", false))) cout << e->getName() << " (" << e->type() << ") | Net: " << fixed << setprecision(2) << e->salary() << '\n';
        else cout << "Not found.\n";
    }
    void update() {
        auto* e = find(readNum<int>("Update ID: ", false));
        if (!e) { cout << "Not found.\n"; return; }
        bool isF = e->type() == "Full-Time";
        e->update(readNum<double>(isF ? "New Basic: " : "New Rate: "), readNum<double>(isF ? "New Allowance: " : "New Hours: "), readNum<double>("New Deduction: "));
        save(); cout << "Updated. New net: " << fixed << setprecision(2) << e->salary() << '\n';
    }
    void del() {
        int id = readNum<int>("Delete ID: ", false);
        auto it = remove_if(emps.begin(), emps.end(), [id](const auto& e) { return e->getId() == id; });
        if (it == emps.end()) { cout << "Not found.\n"; return; }
        emps.erase(it, emps.end()); save(); cout << "Deleted.\n";
    }
    void report() const {
        double tot = 0; cout << "\nPAYROLL REPORT\n";
        for (const auto& e : emps) { cout << e->getId() << " | " << e->getName() << " | " << fixed << setprecision(2) << e->salary() << '\n'; tot += e->salary(); }
        cout << "Total Payroll: " << fixed << setprecision(2) << tot << '\n';
    }
};

int main() {
    PayManager pm; pm.load();
    while (true) {
        cout << "\n1.Add 2.List 3.Search 4.Update 5.Delete 6.Report 7.Exit\nChoice: "
        int c;
        if (!(cin >> c)) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); continue; }
        try {
            if (c == 1) pm.add(); else if (c == 2) pm.list(); else if (c == 3) pm.search();
            else if (c == 4) pm.update(); else if (c == 5) pm.del(); else if (c == 6) pm.report();
            else if (c == 7) break; else cout << "Invalid choice.\n";
        } catch (const exception& ex) { cout << "Error: " << ex.what() << '\n'; }
    }
}