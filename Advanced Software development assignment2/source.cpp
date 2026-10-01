#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct STUDENT_DATA {
    std::string firstName;
    std::string lastName;
#ifdef PRE_RELEASE
    std::string email;
#endif
};

int main() {
#ifdef PRE_RELEASE
    std::cout << "Running PRE-RELEASE version" << std::endl;
    const std::string fileName = "StudentData_Emails.txt";
#else
    std::cout << "Running STANDARD version" << std::endl;
    const std::string fileName = "StudentData.txt";
#endif

    std::vector<STUDENT_DATA> students;

    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: could not open " << fileName << std::endl;
        return -1;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        size_t comma = line.find(',');
        if (comma == std::string::npos) continue;   // skip malformed lines

        STUDENT_DATA student;
        student.lastName = line.substr(0, comma);
        std::string rest = line.substr(comma + 1);

#ifdef PRE_RELEASE
        size_t comma2 = rest.find(',');
        if (comma2 == std::string::npos) continue;
        student.email = rest.substr(comma2 + 1);
        rest = rest.substr(0, comma2);
#endif

        size_t start = rest.find_first_not_of(' ');
        student.firstName = (start == std::string::npos) ? "" : rest.substr(start);

        students.push_back(student);
    }
    file.close();

#ifdef _DEBUG
    std::cout << "[DEBUG] Loaded " << students.size() << " students:" << std::endl;
    for (const STUDENT_DATA& s : students) {
        std::cout << s.firstName << " " << s.lastName;
#ifdef PRE_RELEASE
        std::cout << " - " << s.email;
#endif
        std::cout << std::endl;
    }
#endif

    return 1;
}