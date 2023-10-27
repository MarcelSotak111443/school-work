package sk.stuba.fei.uim.vsa.pr2.exeptions;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;

import javax.ws.rs.core.Response;

public class Ok {
    private final ObjectMapper json = new ObjectMapper();

    public Ok(){

    }
    public Response Ok(Object o) throws JsonProcessingException {


        return Response
                .status(Response.Status.OK)
                .entity(json.writeValueAsString(o))
                .build();
    }
}
