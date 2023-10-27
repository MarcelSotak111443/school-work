package sk.stuba.fei.uim.vsa.pr2.web.response;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonMappingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import lombok.extern.slf4j.Slf4j;


import org.eclipse.persistence.jpa.rs.exceptions.ErrorResponse;
import sk.stuba.fei.uim.vsa.pr2.auth.Permision;
import sk.stuba.fei.uim.vsa.pr2.auth.Secured;
import sk.stuba.fei.uim.vsa.pr2.domain.Student;
import sk.stuba.fei.uim.vsa.pr2.domain.Teacher;
import sk.stuba.fei.uim.vsa.pr2.exeptions.*;
import sk.stuba.fei.uim.vsa.pr2.exeptions.ServerErrorException;
import sk.stuba.fei.uim.vsa.pr2.services.ThesisService;
import sk.stuba.fei.uim.vsa.pr2.web.ErrorMessage;
import sk.stuba.fei.uim.vsa.pr2.web.Message;
import sk.stuba.fei.uim.vsa.pr2.web.response.factory.MessageDto;

import javax.print.attribute.standard.Media;
import javax.ws.rs.*;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import javax.ws.rs.core.SecurityContext;
import java.security.Principal;
import java.util.ArrayList;
import java.util.Base64;
import java.util.List;
import java.util.Objects;
import java.util.logging.Level;
import java.util.logging.Logger;

@Slf4j
@Path("/students")
public class StudentResource {


    private final ThesisService service = new ThesisService();
    private final ObjectMapper json = new ObjectMapper();

    @Context
    SecurityContext securityContext;

    @GET
    @Secured()
    @Produces(MediaType.APPLICATION_JSON)
    public Response getlAll() {
        try {
            List<Student> students = service.getStudents();
            return new Ok().Ok(students);
        } catch (Exception e) {
            return new ServerErrorException().responseCode(e);
        }

    }
    @GET
    @Secured()
    @Path("/{id}")
    @Produces(MediaType.APPLICATION_JSON)
    public Response getStudentById(@PathParam("id") Long id) throws JsonProcessingException {
        Student student = new Student();
        try {
            student = service.getStudent(id);
            if (student == null) {
                return new NotFound().NotFoundException("Student");
            }
        } catch (Exception e) {
            return new ServerErrorException().responseCode(e);

        }
        return new Ok().Ok(student);
    }

    @POST
    @Produces(MediaType.APPLICATION_JSON)
    @Consumes(MediaType.APPLICATION_JSON)
    public Response createStudent(String body) {
        try {
            JsonNode jsonNode = json.readTree(body);
            Long AISID = jsonNode.get("aisId").asLong();
            String email = jsonNode.get("email").asText();
            String name = jsonNode.get("name").asText();
            String password = jsonNode.get("password").asText();
            int year = jsonNode.get("year").asInt();
            int term = jsonNode.get("term").asInt();
            String programme = jsonNode.get("programme").asText();
            Student student = service.createStudent(AISID, name, email, password, year, term, programme);
            return new Ok().Ok(student);
        } catch (JsonProcessingException e) {
            return new ServerErrorException().responseCode(e);
        }
    }
    @DELETE
    @Path("/{id}")
    @Secured
    @Produces(MediaType.APPLICATION_JSON)
    public Response deleteStudent(@PathParam("id") long id) throws JsonProcessingException {

        Student student = new Student();

        log.info("tu som1");
        Principal principal = securityContext.getUserPrincipal();
        if (principal instanceof Student) {
            log.info("student");
            Student student2 = (Student) principal;
            if (!student2.getAisId().equals(id)) {
                return new NotPermision().notPermisionException();
            }
        }
        log.info("tu som2");

        try {
            student = service.deleteStudent(id);
            if (student == null) {
                return new NotFound().NotFoundException("Student");
            }
        } catch (Exception e) {
            return new ServerErrorException().responseCode(e);

        }
        return new Ok().Ok(student);

    }

}








