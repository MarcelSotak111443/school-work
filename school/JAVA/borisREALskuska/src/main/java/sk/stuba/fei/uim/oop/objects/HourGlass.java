package sk.stuba.fei.uim.oop.objects;

import java.awt.*;

public class HourGlass {

    private Point p;
    private int radius;
    private Color color;
   public HourGlass(Point p, int radius , Color color){
        this.p = p;
        this.radius = radius;
        this.color = color;
    }

    public void draw(Graphics g) {
        g.setColor(color);
        g.fillPolygon(new int[]{p.x-radius,p.x + radius *2 -radius ,p.x}, new int[]{p.y-radius,p.y-radius,p.y },3);
        g.fillPolygon(new int[]{p.x+radius,p.x - radius *2 +radius ,p.x}, new int[]{p.y+radius,p.y+radius,p.y },3);

    }


}
