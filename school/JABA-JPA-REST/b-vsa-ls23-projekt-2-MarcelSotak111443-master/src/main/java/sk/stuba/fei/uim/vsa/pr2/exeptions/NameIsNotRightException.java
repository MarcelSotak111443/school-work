package sk.stuba.fei.uim.vsa.pr2.exeptions;

import sk.stuba.fei.uim.vsa.pr2.web.ErrorMessage;
import sk.stuba.fei.uim.vsa.pr2.web.Message;

import javax.ws.rs.WebApplicationException;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;

public class NameIsNotRightException extends WebApplicationException {
    public NameIsNotRightException(String wrongName) {
        super(Response
                .status(Response.Status.BAD_REQUEST)
                .type(MediaType.APPLICATION_JSON)
             /*   .entity(Message.builder()
                        .code(Response.Status.BAD_REQUEST.getStatusCode())
                        .message("Baddd")
                        .build()  )*/
             //   .entity(new ErrorMessage(Response.Status.BAD_REQUEST, "hi"))
                .build()
        );
    }
}

