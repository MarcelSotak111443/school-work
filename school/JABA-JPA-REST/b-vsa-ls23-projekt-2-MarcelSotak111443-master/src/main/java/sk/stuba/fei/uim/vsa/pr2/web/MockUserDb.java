package sk.stuba.fei.uim.vsa.pr2.web;


import sk.stuba.fei.uim.vsa.pr2.domain.Student;

import java.util.Arrays;
import java.util.List;
import java.util.Objects;
import java.util.Optional;

public class MockUserDb {


    private List<Student> students;

    public Optional<Student> getStudentByName(String username) {
        return students.stream()
                .filter(u -> Objects.equals(username, u.getName()))
                .findFirst();
    }

    public MockUserDb(){
        students = Arrays.asList(new Student(1L,"milan","password"));
    }

}
