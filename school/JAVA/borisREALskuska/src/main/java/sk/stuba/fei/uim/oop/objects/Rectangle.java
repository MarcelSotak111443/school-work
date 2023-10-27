package sk.stuba.fei.uim.oop.objects;

import javax.swing.*;
import java.awt.*;

public class Rectangle extends JPanel {

    private Point p;
    private int radius;
    private Color color;
    public Rectangle(Point p, int radius ,Color  color){
        this.p = p;
        this.radius = radius;
        this.color = color;
    }

    public void draw(Graphics g) {
        g.setColor(color);
        g.fillRect(p.x - radius, p.y - radius, 2*radius , 2 * radius);
    }

}
