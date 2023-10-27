package sk.stuba.fei.uim.vsa.pr2.exeptions;

import sk.stuba.fei.uim.vsa.pr2.web.ErrorMessage;
import sk.stuba.fei.uim.vsa.pr2.web.Message;

import javax.ws.rs.core.Response;

public class NotPermision {

    public NotPermision(){

    }

    public Response notPermisionException(){

        ErrorMessage errorMessage = new ErrorMessage("errorMessage", "Not permision");
        Message message = new Message(403, "NOT_PERMISION", errorMessage);
        return Response
                .status(Response.Status.FORBIDDEN)
                .entity(message)
                .build();
    }
}
