import lombok.Getter;
import lombok.Setter;

import java.awt.*;

public class Line {
    @Setter
            @Getter
    Color color;
    @Setter
            @Getter
    int x, y;
    @Getter
            @Setter
    int lastClickX,lastClickY;

    public Line(int x, int y ,int lastClickX, int lastClickY,  Color color){
        this.x = x;
        this.y = y;
        this.lastClickX = lastClickX;
        this.lastClickY = lastClickY;
        this.color = color;
    }
}
