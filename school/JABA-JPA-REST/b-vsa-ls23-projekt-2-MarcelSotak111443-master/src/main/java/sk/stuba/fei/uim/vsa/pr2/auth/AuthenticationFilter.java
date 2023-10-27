package sk.stuba.fei.uim.vsa.pr2.auth;


import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import lombok.extern.slf4j.Slf4j;
import sk.stuba.fei.uim.vsa.pr2.BCryptService;

import sk.stuba.fei.uim.vsa.pr2.domain.Student;
import sk.stuba.fei.uim.vsa.pr2.domain.Teacher;
import sk.stuba.fei.uim.vsa.pr2.services.ThesisService;
import sk.stuba.fei.uim.vsa.pr2.web.ErrorMessage;
import sk.stuba.fei.uim.vsa.pr2.web.Message;


import javax.annotation.Priority;
import javax.ws.rs.Priorities;
import javax.ws.rs.container.ContainerRequestContext;
import javax.ws.rs.container.ContainerRequestFilter;
import javax.ws.rs.core.HttpHeaders;
import javax.ws.rs.core.Response;
import javax.ws.rs.core.SecurityContext;
import javax.ws.rs.ext.Provider;
import java.io.IOException;
import java.security.Principal;
import java.util.Base64;
import java.util.Objects;
import java.util.Optional;
import java.util.logging.Logger;

@Slf4j
@Secured
@Provider
@Priority(Priorities.AUTHENTICATION)
public class AuthenticationFilter implements ContainerRequestFilter {


    public static final Logger LOGGER = Logger.getLogger(AuthenticationFilter.class.getName());
    private final ObjectMapper json = new ObjectMapper();
    private Principal p = null;
    @Override
    public void filter(ContainerRequestContext request) throws IOException {


        String authHeader = request.getHeaderString(HttpHeaders.AUTHORIZATION);

        if (authHeader == null ||  !authHeader.contains("Basic")){

            reject(request);
            return;
        }

        String [] credentials = extracktfromAuthHeader(authHeader);

        log.info("Received credentials: "+credentials[0]+ ", "+ credentials[1]);

        ThesisService service = ThesisService.getInstance();
        log.info("got after service");

        Student studentOptional =  service.getStudentByName(credentials[0]);
        Teacher teacherOptional = service.getTeacherByName(credentials[0]);

        log.info("studenf found" + studentOptional);
        log.info("teacher" + teacherOptional);
        log.info("got after service get student");
        Principal p;

        if(teacherOptional==null || !BCryptService.verify(credentials[1] ,teacherOptional.getPassword())){
            log.info("got here");

            if(studentOptional==null || !BCryptService.verify(credentials[1] , studentOptional.getPassword())) {
                log.info("got here2");
                reject(request);
                return;
            }else {

                p = studentOptional;
            }
        }else{
           p = teacherOptional;
        }
        final SecurityContext securityContext = request.getSecurityContext();
        BasicSecurityContext context = new BasicSecurityContext(p);

        context.setSecure(securityContext.isSecure());
        request.setSecurityContext(context);
        log.info("1");



    }
    private void reject(ContainerRequestContext request) throws JsonProcessingException {
        log.info("retuned");
        ErrorMessage errorMessage = new ErrorMessage("errorMessage","Unathorized");
        Message message = new Message(401,"UNAUTHORIZED",errorMessage);

        Response response = Response
                .status(Response.Status.UNAUTHORIZED)
                .entity(message)
                .build();

        request.abortWith(response);
    }

    private String[] extracktfromAuthHeader(String authHeader){

        return  new String(Base64.getDecoder()
                .decode(authHeader
                        .replace("Basic","")
                        .trim()))
                .split(":");

    }
}
