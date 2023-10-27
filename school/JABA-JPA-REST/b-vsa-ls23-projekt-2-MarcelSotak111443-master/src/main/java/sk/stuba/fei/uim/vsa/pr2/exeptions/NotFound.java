package sk.stuba.fei.uim.vsa.pr2.exeptions;

import javassist.NotFoundException;
import sk.stuba.fei.uim.vsa.pr2.web.ErrorMessage;
import sk.stuba.fei.uim.vsa.pr2.web.Message;

import javax.ws.rs.core.Response;

public class NotFound {

    public NotFound(){

    }

    public Response NotFoundException(String name){
        ErrorMessage errorMessage = new ErrorMessage("errorMessage", name + " not Found");
        Message message = new Message(404, "NOT_FOUND", errorMessage);
        return Response
                .status(Response.Status.NOT_FOUND)
                .entity(message)
                .build();
    }
}
