
import lombok.Getter;
import lombok.Setter;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

public class Logic implements MouseListener, MouseMotionListener {

    private Surface surface;
    @Getter
    @Setter
    private Point firstClick;
    private Point distance;

    @Setter
    private Color[] color;
    private int stlaceneX;
    private int stlaceneY;
    boolean what = false;
    boolean gotPicture;
    boolean variable;
    int posunX,posunY;
 //   private Tree tree;
    @Setter
    private EnumAction enumAction;
    private Tree tree;
    private House house;
    private Objects objects;

    private Objects clickedObject;
    private Objects releasedAboveObject;
    private int i;
    @Setter
    private JLabel jLabel;


    public Logic(Surface surface) {


        enumAction = EnumAction.TREE;
        this.surface = surface;
        firstClick = new Point();
        distance = new Point();
        color = new Color[3];
        i = 0;
    }

    public void changeColor(){
        i++;
        if (i > 2)
            i = 0;
    }

    @Override
    public void mouseClicked(MouseEvent e) {

    }

    @Override
    public void mousePressed(MouseEvent e) {
        switch (enumAction) {
            case LINE:

                this.stlaceneX = e.getX();
                this.stlaceneY = e.getY();
                clickedObject = null;
                if (surface.getObject(e.getPoint()) != null){
                    clickedObject = surface.getObject(e.getPoint());

                    this.surface.getLines().add(new Line(clickedObject.getX(), clickedObject.getY(), e.getX(), e.getY()));
                }
                break;
        }
        objects.setAplhla();
        changeColor();
        jLabel.setBackground(color[i]);
        jLabel.setOpaque(true);
        what = false;
        surface.repaint();
    }


    @Override
    public void mouseReleased(MouseEvent e) {

        System.out.println("co to kurva");
        switch (enumAction) {

            case LINE:
                if (surface.getObject(e.getPoint()) != null) {
                    releasedAboveObject = surface.getObject(e.getPoint());
                    if ((clickedObject instanceof Tree) != (releasedAboveObject instanceof Tree) && ((clickedObject instanceof House) != (releasedAboveObject instanceof House))){
                        this.surface.getLines().set(this.surface.getLines().size() - 1, new Line(clickedObject.getX(), clickedObject.getY(), releasedAboveObject.getX(),releasedAboveObject.getY()));
                        surface.repaint();
                        break;

                    }else if (surface.getLines().size() != 0){
                        this.surface.getLines().remove(this.surface.getLines().size()-1);
                        System.out.println("vruh");
                        surface.repaint();
                    }


                }
                else{
                    if (surface.getLines().size() != 0){
                        this.surface.getLines().remove(this.surface.getLines().size()-1);
                        System.out.println("vruh");
                        surface.repaint();
                    }

                }

        }
    }

    @Override
    public void mouseEntered(MouseEvent e) {
        what = false;

    }

    @Override
    public void mouseExited(MouseEvent e) {
        if ( enumAction!= EnumAction.LINE ) {
            surface.getTvary().remove(surface.getTvary().size() - 1);
            what = false;
            surface.repaint();
        }
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        switch (enumAction) {

            case LINE:
                if (clickedObject != null){
                this.surface.getLines().set(this.surface.getLines().size() - 1, new Line(clickedObject.getX(), clickedObject.getY(), e.getX(), e.getY()));
                this.surface.repaint();}
                break;

        }
    }

    @Override
    public void mouseMoved(MouseEvent e) {


        if (!what && enumAction!= EnumAction.LINE) {
            System.out.println("nice");
            switch (enumAction) {
                case TREE:
                    objects = new Tree(10, 10, color[i]);
                    break;
                case HOUSE:
                    objects = new House(10, 10, color[i]);
                    break;
            }
            surface.getTvary().add(objects);
        }
        if (enumAction!= EnumAction.LINE){
        objects.setX(e.getX());
        objects.setY(e.getY());
        surface.repaint();

        what = true;}

    }
}


