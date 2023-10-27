package sk.stuba.fei.uim.vsa.pr2.web.response;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import lombok.extern.slf4j.Slf4j;
import sk.stuba.fei.uim.vsa.pr2.auth.Permision;
import sk.stuba.fei.uim.vsa.pr2.auth.Secured;
import sk.stuba.fei.uim.vsa.pr2.domain.Student;
import sk.stuba.fei.uim.vsa.pr2.domain.Teacher;
import sk.stuba.fei.uim.vsa.pr2.domain.Thesis;
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
import java.util.Arrays;
import java.util.List;

@Slf4j
@Path("/theses")
public class ThesisResource {


    @Context
    SecurityContext securityContext;

    private final ThesisService service = new ThesisService();
    private final ObjectMapper json = new ObjectMapper();

    @GET
    @Secured()
    @Produces(MediaType.APPLICATION_JSON)
    public Response getlAll() {
        try {
            List<Thesis> theses = service.getTheses();
            return new Ok().Ok(theses);
        } catch (Exception e) {

            return new ServerErrorException().responseCode(e);
        }

    }

    @GET
    @Secured()
    @Path("/{id}")
    @Produces(MediaType.APPLICATION_JSON)
    public Response getThesisById(@PathParam("id") Long id) throws JsonProcessingException {
        Thesis thesis = new Thesis();
        try {
            thesis = service.getThesis(id);
            if (thesis == null) {
                return new NotFound().NotFoundException("Thesis");
            }
        } catch (Exception e) {
            return new ServerErrorException().responseCode(e);

        }
        return new Ok().Ok(thesis);
    }
    @POST
    @Produces(MediaType.APPLICATION_JSON)
    @Consumes(MediaType.APPLICATION_JSON)
    @Secured()
    public Response createThesis(String body){

        Principal principal = securityContext.getUserPrincipal();
        if (principal instanceof Student){
            return new NotPermision().notPermisionException();
        }
        Teacher teacher = (Teacher) principal;
        try {
            log.info("1");
            JsonNode jsonNode = json.readTree(body);
            String registrationNumber = jsonNode.get("registrationNumber").asText();
            String title = jsonNode.get("title").asText();
            String description = jsonNode.get("description").asText();
            String type = jsonNode.get("type").asText();

            log.info("2");
// Assuming you have a method to create a Teacher object with the given parameters
            Thesis thesis = service.createThesis(registrationNumber, title,type, description,  teacher);

            log.info("3");
            service.updateThesis(thesis);
            log.info("4");
            return new Ok().Ok(thesis);
        } catch (JsonProcessingException e) {
            return new ServerErrorException().responseCode(e);
        }
    }


    @DELETE
    @Path("/{id}")
    @Secured

    @Produces(MediaType.APPLICATION_JSON)
    public Response deleteThesis(@PathParam("id") long id) throws JsonProcessingException {

        Thesis thesis = new Thesis();

        Principal principal = securityContext.getUserPrincipal();
        if (principal instanceof Student) {
            return new NotPermision().notPermisionException();

        }
        Teacher teacher = (Teacher) principal;
        Thesis thesis1 = service.getThesis(id);
        if (thesis1 == null) {
            return new NotFound().NotFoundException("Thesis");
        }
            if (!thesis1.getSupervisor().equals(teacher)){
                return new NotPermision().notPermisionException();
            }


        try {
            thesis = service.deleteThesis(id);
        }
         catch (Exception e) {
            return new ServerErrorException().responseCode(e);
        }
        return new Ok().Ok(thesis);
    }


    @POST
    @Path("/{id}/assign")
    @Secured()
    @Produces(MediaType.APPLICATION_JSON)
    public Response assignThesis(@PathParam("id") long id , String body) throws JsonProcessingException {

        Thesis thesis = new Thesis();

        try {
            thesis = service.getThesis(id);
            if (thesis == null){
                return new NotFound().NotFoundException("Thesis");
            }
            Principal principal = securityContext.getUserPrincipal();
        if (principal instanceof Student) {
            service.assignThesis(id,((Student) principal).getAisId());
        }
        if ((principal instanceof Teacher)){
            JsonNode jsonNode = json.readTree(body);
            Long studentId = jsonNode.get("studentId").asLong();
            Student student = service.getStudent(studentId);
            if (student == null){
                return new NotFound().NotFoundException("thesis");
            }
            service.assignThesis(id,studentId);

        } }catch (Exception e){
            return new ServerErrorException().responseCode(e);
        }
        return new Ok().Ok(thesis);
    }
    @POST
    @Secured()
    @Path("/{id}/submit")
    @Produces(MediaType.APPLICATION_JSON)
    public Response submitThesis(@PathParam("id") long id , String body) throws JsonProcessingException {
        Thesis thesis = new Thesis();
        try {
            thesis = service.getThesis(id);

            if (thesis == null){
                return new NotFound().NotFoundException("Thesis");
            }
            log.info("find thesis");
            Principal principal = securityContext.getUserPrincipal();
        if (principal instanceof Student) {
            log.info("instance of student");
            if (thesis.getAuthor().equals(principal)){
                log.info("student is eaual to thesis");
                service.submitThesis(thesis.getId());
                log.info("nah");
            }else{
                return new NotPermision().notPermisionException();
            }
        }
        if ((principal instanceof Teacher)){
            log.info("teacher is loged");
            JsonNode jsonNode = json.readTree(body);
            Long studentId = jsonNode.get("studentId").asLong();
            Student student = service.getStudent(studentId);

            if (student == null){
                return new NotFound().NotFoundException("Thesis");
            }
            log.info("student found by body");

            if (!student.equals(thesis.getAuthor())){
                log.info("student doest equal");
                return new NotFound().NotFoundException("Thesis");
            }
            service.submitThesis(id);
        }}catch (Exception e){
            return new ServerErrorException().responseCode(e);
        }
        return new Ok().Ok(thesis);
    }
}
