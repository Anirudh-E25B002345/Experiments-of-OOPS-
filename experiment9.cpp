
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;

int main() {
    vector<int> marks = {75, 85, 60, 90, 70};

    // Sort marks
    sort(marks.begin(), marks.end());

    // Display sorted marks
    cout << "Sorted Marks: ";
    for (int m : marks)
        cout << m << " ";

    // Find a mark greater than 80
    auto it = find_if(marks.begin(), marks.end(),
                      [](int m) { return m > 80; });

    if (it != marks.end())
        cout << "\nFirst mark above 80: " << *it;

    // Increase all marks by 5
    transform(marks.begin(), marks.end(), marks.begin(),
              [](int m) { return m + 5; });

    cout << "\nUpdated Marks: ";
    for (int m : marks)
        cout << m << " ";

    // Using map
    map<string, int> students = {
        {"Amit", 75}, {"Ravi", 85}, {"Neha", 90}
    };

    cout << "\n\nStudent Marks:\n";
    for (auto s : students)
        cout << s.first << ": " << s.second << endl;

    // Using unordered_map
    unordered_map<string, int> result;
    result["Amit"] = 75;
    result["Ravi"] = 85;
    result["Neha"] = 90;

    cout << "\nTotal Students: " << result.size();

    return 0;
}
