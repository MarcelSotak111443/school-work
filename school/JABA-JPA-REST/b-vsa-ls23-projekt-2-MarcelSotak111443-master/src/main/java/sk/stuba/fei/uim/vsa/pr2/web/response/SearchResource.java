package sk.stuba.fei.uim.vsa.pr2.web.response;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.ObjectMapper;
import lombok.extern.slf4j.Slf4j;
import sk.stuba.fei.uim.vsa.pr2.domain.Student;
import sk.stuba.fei.uim.vsa.pr2.domain.Thesis;
import sk.stuba.fei.uim.vsa.pr2.exeptions.Ok;
import sk.stuba.fei.uim.vsa.pr2.exeptions.ServerErrorException;
import sk.stuba.fei.uim.vsa.pr2.services.ThesisService;
import sk.stuba.fei.uim.vsa.pr2.web.ErrorMessage;
import sk.stuba.fei.uim.vsa.pr2.web.Message;

import javax.ws.rs.POST;
import javax.ws.rs.Path;
import javax.ws.rs.Produces;
import javax.ws.rs.core.Context;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import javax.ws.rs.core.SecurityContext;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;


@Slf4j
@Path("/search")
public class SearchResource {


    private final ThesisService service = new ThesisService();
    private final ObjectMapper json = new ObjectMapper();

    @Context
    SecurityContext securityContext;


    @POST

    @Path("/theses")
    @Produces(MediaType.APPLICATION_JSON)
    public Response searchTheses(String body) throws JsonProcessingException {
        Thesis thesis = new Thesis();
        log.info("Wtf");

        JsonNode jsonNode = json.readTree(body);


        long id;
        List<Thesis> theses = new ArrayList<>();
            if (jsonNode.hasNonNull("teacherId")) {
                id = jsonNode.get("teacherId").asLong();
                theses = service.getThesesByTeacher(id);


            }
            if (jsonNode.hasNonNull("studentId")) {
                id = jsonNode.get("studentId").asLong();

                if (service.getStudent(id).getThesis() != null)
                theses.add(service.getStudent(id).getThesis());

            }


        return new Ok().Ok(theses);
    }

}