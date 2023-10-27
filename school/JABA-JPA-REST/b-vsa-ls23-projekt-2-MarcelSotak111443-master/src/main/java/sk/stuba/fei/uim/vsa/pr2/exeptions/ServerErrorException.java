package sk.stuba.fei.uim.vsa.pr2.exeptions;

import sk.stuba.fei.uim.vsa.pr2.web.ErrorMessage;
import sk.stuba.fei.uim.vsa.pr2.web.Message;


import javax.ws.rs.core.Response;

public class ServerErrorException {

    public ServerErrorException() {

    }
    public Response responseCode(Exception e){
        ErrorMessage errorMessage = new ErrorMessage("errorMessage",e.toString());
        Message message = new Message(500,"SERVER_ERROR",errorMessage);
        return Response
                .status(Response.Status.INTERNAL_SERVER_ERROR)
                .entity(message)
                .build();
    }
}
