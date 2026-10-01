#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
};

int main() {
    std::vector<STUDENT_DATA> students;

    std::ifstream file("StudentData.txt");
    if (!file.is_open()) {
        std::cerr << "Error: could not open StudentData.txt" << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        size_t comma = line.find(',');
        if (comma == std::string::npos) continue;   // skip malformed lines

        STUDENT_DATA student;
        student.lastName = line.substr(0, comma);

        std::string first = line.substr(comma + 1);
        size_t start = first.find_first_not_of(' ');
        student.firstName = (start == std::string::npos) ? "" : first.substr(start);

        students.push_back(student);
    }
    file.close();

    return 1;
}