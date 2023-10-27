import lombok.Getter;
import lombok.Setter;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.Ellipse2D;

public class Tree extends Objects {
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
    int roofGetX ;

    public Tree(int stlaceneX, int stlaceneY , Color color) {
        this.sirka = 50;
        this.vyska = 50;
        this.x = stlaceneX;
        this.y = stlaceneY;
        this.color = new Color(color.getRed(),color.getGreen(),color.getBlue(), 50);
    }
    @Override
    public void paintComponent(Graphics g) {
      //  super.paintComponent(g);
        g.drawLine(10,20,30,40);
        g.fillOval(x-25, y-25, sirka,  vyska/3*2);
        g.fillRect(x -25+50/3, y , sirka / 3, vyska / 2);
    }

    @Override
    public void setX(int x) {
        this.x = x;
    }

    @Override
    public void setY(int y) {
        this.y = y;

    }

    public void setAplhla(){
        this.color = new Color(color.getRed(),color.getGreen(),color.getBlue(),255);
    }


    @Override
    public Objects findContain(Point p) {
        Ellipse2D ellipse2D = new Ellipse2D.Double(x-25, y-25, sirka,  vyska/3*2);
        Rectangle rectangle = new Rectangle(x -25+50/3, y , sirka / 3, vyska / 2);
        if (ellipse2D.contains(p) || rectangle.contains(p))
            return this;
        else return null;
    }




}

