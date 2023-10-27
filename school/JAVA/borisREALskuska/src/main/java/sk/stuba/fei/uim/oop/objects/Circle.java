package sk.stuba.fei.uim.oop.objects;

import java.awt.*;

public class Circle {

    private Point p;
    private int radius;
    private Color color;

    public Circle(Point p, int radius ,Color color){
        this.p = p;
        this.radius = radius;
        this.color = color;
    }

    public void draw(Graphics g) {
        g.setColor(color);
        g.fillOval(p.x - radius, p.y - radius, 2*radius , 2 * radius);
    }

}

