package sk.stuba.fei.uim.vsa.pr2.web.response;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import lombok.extern.slf4j.Slf4j;

import sk.stuba.fei.uim.vsa.pr2.auth.Permision;
import sk.stuba.fei.uim.vsa.pr2.auth.Secured;
import sk.stuba.fei.uim.vsa.pr2.domain.Student;
import sk.stuba.fei.uim.vsa.pr2.domain.Teacher;
import sk.stuba.fei.uim.vsa.pr2.exeptions.NotFound;
import sk.stuba.fei.uim.vsa.pr2.exeptions.NotPermision;
import sk.stuba.fei.uim.vsa.pr2.exeptions.Ok;
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
import java.util.List;

@Slf4j
@Path("/teachers")
public class TeacherResource {


    @Context
    SecurityContext securityContext;


    private final ThesisService service = new ThesisService();
    private final ObjectMapper json = new ObjectMapper();
    @GET
    @Secured()
    @Produces(MediaType.APPLICATION_JSON)
    public Response getlAll() {


        try {
            List<Teacher> teachers= service.getTeachers();
            return new Ok().Ok(teachers);
        } catch (Exception e) {

            return new ServerErrorException().responseCode(e);
        }

    }

    @GET
    @Secured()
    @Path("/{id}")
    @Produces(MediaType.APPLICATION_JSON)
    public Response getTeachertById(@PathParam("id") Long id) throws JsonProcessingException {
        Teacher teacher = new Teacher();
        try {
            teacher = service.getTeacher(id);
            if (teacher == null) {
                return new NotFound().NotFoundException("teacher");
            }
        }catch (Exception e){
            return new ServerErrorException().responseCode(e);

        }
        return new Ok().Ok(teacher);
    }
    @POST
    @Produces(MediaType.APPLICATION_JSON)
    @Consumes(MediaType.APPLICATION_JSON)
    public Response createTeacher(String body){
        try {
            JsonNode jsonNode = json.readTree(body);
            Long aisId = jsonNode.get("aisId").asLong();
            String name = jsonNode.get("name").asText();
            String email = jsonNode.get("email").asText();
            String password = jsonNode.get("password").asText();
            String institute = jsonNode.get("institute").asText();
            String department = jsonNode.get("department").asText();

            Teacher teacher = service.createTeacher(aisId, name, email, password, institute, department);

            return new Ok().Ok(teacher);
        } catch (JsonProcessingException e) {
            return new ServerErrorException().responseCode(e);
        }
    }
    @DELETE
    @Path("/{id}")
    @Secured
    @Produces(MediaType.APPLICATION_JSON)
    public Response deleteTeacher(@PathParam("id") long id) throws JsonProcessingException {

        Teacher teacher = new Teacher();

        Principal principal = securityContext.getUserPrincipal();
        if (principal instanceof Student) {
            return new NotPermision().notPermisionException();
        }
        if (principal instanceof Teacher){
            Teacher teacher1 = (Teacher) principal;
            if (!teacher1.getAisId().equals(id)){
                return new NotPermision().notPermisionException();
            }
        }
        try {
            teacher = service.deleteTeacher(id);
            if (teacher == null) {
                return new NotFound().NotFoundException("teacher");
            }
        } catch (Exception e) {
            return new ServerErrorException().responseCode(e);

        }
        return new Ok().Ok(teacher);

    }

}
