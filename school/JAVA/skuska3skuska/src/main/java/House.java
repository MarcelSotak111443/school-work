import lombok.Getter;
import lombok.Setter;

import javax.swing.*;
import java.awt.*;

public class House extends Objects {
    @Getter
    @Setter
    private int x;
    @Getter
    @Setter
    private int y;
    @Getter
    private  int sirka;
    @Getter
    private  int vyska;
    @Getter
    @Setter
    private Color color;



    public House(int stlaceneX, int stlaceneY ,Color color) {
        this.sirka = 50;
        this.vyska = 50;
        this.x = stlaceneX;
        this.y = stlaceneY;
        this.color = new Color(color.getRed(),color.getGreen(),color.getBlue(), 50);




}
@Override
    public void paintComponent(Graphics g) {
      //  super.paintComponent(g);
        g.fillPolygon(new int[]{x+50/4-25,x,x+50/4*3-25}, new int[]{y+25-25,y-25,y},3);
        g.fillRect(x+50/4-25,y,50/4*2,50-25);
    }

    public void setAplhla(){
        this.color = new Color(color.getRed(),color.getGreen(),color.getBlue(),255);
    }

    @Override
    public Objects findContain(Point p) {
        Polygon polygon = new Polygon(new int[]{x+50/4-25,x,x+50/4*3-25}, new int[]{y+25-25,y-25,y},3);
        Rectangle rectangle = new Rectangle(x+50/4-25,y,50/4*2,50-25);
        if (polygon.contains(p) || rectangle.contains(p))
            return this;
        else return null;
    }

    @Override
    public void setX(int x) {
        this.x = x;
    }

    @Override
    public void setY(int y) {
        this.y = y;

    }
}

