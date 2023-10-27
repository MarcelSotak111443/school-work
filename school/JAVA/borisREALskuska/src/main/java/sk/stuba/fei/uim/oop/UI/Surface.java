package sk.stuba.fei.uim.oop.UI;

import lombok.Getter;
import lombok.Setter;
import sk.stuba.fei.uim.oop.logic.UniversalAdapter;
import sk.stuba.fei.uim.oop.objects.Circle;
import sk.stuba.fei.uim.oop.objects.HourGlass;
import sk.stuba.fei.uim.oop.objects.ObjectEnum;
import sk.stuba.fei.uim.oop.objects.Rectangle;


import java.awt.*;

import java.awt.event.MouseEvent;
import java.util.ArrayList;
import java.util.List;


public class Surface extends UniversalAdapter {

    @Getter
    @Setter
    private  List<Point> points;


    @Setter
    private int lenght;
    @Setter
    private int radius;
    @Setter
    private int spacing;
    @Setter
    private ObjectEnum objectEnum;
    @Setter
    private int numberOfobjects;
    private int colorNumber;

    public Surface(){
        objectEnum = ObjectEnum.CIRCLE;
        lenght = 50;
        radius = 5;
        spacing = 5;
        points = new ArrayList<>();
        numberOfobjects = 0;
        colorNumber = 0;



    }
    @Override
    protected void paintComponent(Graphics g) {
        super.paintComponent(g);
        numberOfobjects = 0;
        colorNumber = 0;
        for (int i = 0; i < points.size();i++) {
            if (numberOfobjects < lenght)
            if (i % spacing == 0){
                switch (objectEnum){
                    case CIRCLE:
                        Circle circle = new Circle(points.get(i) , radius , new Color(1,1+colorNumber,1+colorNumber));
                        circle.draw(g);
                        break;
                    case RECT:
                        sk.stuba.fei.uim.oop.objects.Rectangle rectangle = new Rectangle(points.get(i) , radius,new Color(1,1+colorNumber,1+colorNumber));
                        rectangle.draw(g);
                        break;
                    case HOURGLASS:
                        HourGlass hourGlass = new HourGlass(points.get(i) , radius,new Color(1,1+colorNumber,1+colorNumber));
                        hourGlass.draw(g);
                        break;
                }
                colorNumber++;
                numberOfobjects++;
            }
            if (i> 0){
                g.setColor(Color.orange);
                g.drawLine(points.get(i-1).x,points.get(i-1).y,points.get(i).x,points.get(i).y);
            }
        }
    }


    @Override
    public void mouseMoved(MouseEvent e)
    {
        points.add(e.getPoint());
        this.repaint();
    }

}


