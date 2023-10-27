package sk.stuba.fei.uim.vsa.pr2.domain;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import sk.stuba.fei.uim.vsa.pr2.auth.Permision;

import javax.persistence.*;
import java.io.Serializable;
import java.security.Permission;
import java.security.Principal;
import java.util.ArrayList;
import java.util.List;

@Data
@Builder
@AllArgsConstructor
@Entity
@Table(name = "STUDENT")
@NamedQuery(name = Student.FIND_ALL_QUERY, query = "select s from Student s")
public class Student implements Serializable, Principal {
    private static final long serialVersionUID = -8905656348104328114L;

    public static final String FIND_ALL_QUERY = "Student.findAll";

    @Id
    private Long aisId;

    @Column(nullable = false)
    private String name;

    @Column(unique = true, nullable = false)
    private String email;

    private Integer year;
    private Integer term;
    private String studyProgramme;
    private String password;


    public Student(Long aisId, String name, String password) {
        this();
        this.aisId = aisId;
        this.name = name;
        this.password = password;
    }

    @OneToOne(fetch = FetchType.EAGER, mappedBy = "author")
    private Thesis thesis;

    public Student() {

    }



}
