package sk.stuba.fei.uim.oop.objects;

import lombok.Getter;
import lombok.Setter;

import java.awt.*;

public class Line {
    @Setter
    @Getter
    private Color color;
    @Setter
    @Getter
    private int x, y;
    @Getter
    @Setter
    private int lastClickX,lastClickY;

    public Line(int x, int y ,int lastClickX, int lastClickY,Color color){
        this.x = x;
        this.y = y;
        this.lastClickX = lastClickX;
        this.lastClickY = lastClickY;
        this.color = color;
    }

}