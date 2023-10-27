package sk.stuba.fei.uim.vsa.pr2.web.response.factory;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
public class MessageDto {

    private String message;
    private boolean error;

    public static MessageDto buildError(String message) {
        return new MessageDto(message, true);
    }
}
