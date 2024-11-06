contract StudentDB {

    struct Student {
        string name;
        uint8 age;
        string class;
        uint16 rollNumber;
    }

    Student[] public students;

    event NewStudentInserted(string name, uint16 rollNumber);

    function insertStudent(string memory _name, uint8 _age, string memory _class, uint16 _rollNumber) public {
        Student memory newStudent = Student({
            name: _name,
            age: _age,
            class: _class,
            rollNumber: _rollNumber
        });
        students.push(newStudent);
        emit NewStudentInserted(newStudent.name, newStudent.rollNumber);
    }

    function getStudent(uint16 index) public view returns(string memory, uint8, string memory) {
        Student memory student = students[index];
        return (student.name, student.age, student.class);
    }

}