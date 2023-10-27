package sk.stuba.fei.uim.vsa.pr2.domain;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import sk.stuba.fei.uim.vsa.pr2.auth.Permision;

import javax.persistence.*;
import java.io.Serializable;
import java.security.Principal;
import java.util.List;

@Data
@Builder
@AllArgsConstructor
@Entity
@Table(name = "TEACHER")
@NamedQuery(name = Teacher.FIND_ALL_QUERY, query = "select t from Teacher t")
public class Teacher implements Serializable , Principal {
    private static final long serialVersionUID = -3294165768183131788L;

    public static final String FIND_ALL_QUERY = "Teacher.findAll";

    @Id
    private Long aisId;

    @Column(nullable = false)
    private String name;

    @Column(unique = true, nullable = false)
    private String email;
    private String password;
    private String institute;



    @Column(nullable = false)
    private String department;

    @OneToMany(mappedBy = "supervisor", cascade = {CascadeType.REMOVE}, orphanRemoval = true)
    private List<Thesis> supervisedTheses;

    public Teacher() {
    }
}
