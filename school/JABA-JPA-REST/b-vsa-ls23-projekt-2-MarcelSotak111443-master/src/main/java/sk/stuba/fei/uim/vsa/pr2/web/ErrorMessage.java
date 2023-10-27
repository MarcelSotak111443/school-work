package sk.stuba.fei.uim.vsa.pr2.web;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;

import javax.ws.rs.DELETE;
import javax.ws.rs.core.Response;

@Data
@NoArgsConstructor
//@EqualsAndHashCode(callSuper = true)
public class ErrorMessage {
    private String type;
    private String trace;

    public ErrorMessage(String type, String trace) {
        this.type = type;
        this.trace = trace;
    }

    // Getters and setters for type and trace
}
