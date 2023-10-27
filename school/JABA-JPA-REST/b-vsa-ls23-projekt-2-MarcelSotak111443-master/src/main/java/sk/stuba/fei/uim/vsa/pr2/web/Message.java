package sk.stuba.fei.uim.vsa.pr2.web;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;


@Data
@Builder

public class Message {
    private int code;
    private String message;
    private ErrorMessage error;

    public Message() {
    }

    public Message(int code, String message, ErrorMessage error) {
        this.code = code;
        this.message = message;
        this.error = error;
    }
}
