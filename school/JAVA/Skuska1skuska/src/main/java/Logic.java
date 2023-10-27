import lombok.Getter;
import lombok.Setter;

import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;

import static java.lang.Math.round;

public class Logic implements MouseListener, MouseMotionListener {

    private Surface surface;
    @Getter
    @Setter
    private EnumChosenObject enumChosenObject;
    private Cross cross;
    private Point firstClick;
    private Point distance;
    @Setter
    private Color color;
    private int stlaceneX;
    private int stlaceneY;

    boolean gotPicture;
    boolean variable;
    int posunX,posunY;
    @Getter
    @Setter
    private EnumActivity enumActivity;


    public Logic(Surface surface) {

        this.surface = surface;
        enumChosenObject = EnumChosenObject.CROSS;
        enumActivity = EnumActivity.DEFAULT;
        firstClick = new Point();
        distance = new Point();
        color = Color.RED;


    }

    @Override
    public void mouseClicked(MouseEvent e) {


    }

    @Override
    public void mousePressed(MouseEvent e) {
        if (enumActivity == EnumActivity.CHANGECOLOR) {
            System.out.println(enumActivity);
            if (surface.getCross(e.getPoint()) != null) {
                cross = surface.getCross(e.getPoint());
                cross.setColor(color);
                surface.repaint();
            }
        } else {

            if (enumChosenObject == EnumChosenObject.LINE ) {

                this.stlaceneX = e.getX();
                this.stlaceneY = e.getY();
                this.surface.getLines().add(new Line(this.stlaceneX, this.stlaceneY, e.getX(), e.getY(), color));
            }

            if (surface.getCross(e.getPoint()) != null && enumChosenObject != EnumChosenObject.LINE) {
                enumChosenObject = EnumChosenObject.MOVING;
                cross = surface.getCross(e.getPoint());
                this.posunX = e.getX() - this.cross.getX();
                this.posunY = e.getY() - this.cross.getY();
            }
            if (surface.getCross(e.getPoint()) == null && enumChosenObject == EnumChosenObject.CROSS) {
                //kresli kriz
                this.stlaceneX = e.getX();
                this.stlaceneY = e.getY();
                this.surface.getCrosses().add(new Cross(this.stlaceneX, this.stlaceneY, e.getX(), e.getY(), color));
            }

        }
    }


    //neviem
    @Override
    public void mouseReleased(MouseEvent e) {
        if (enumChosenObject == EnumChosenObject.MOVING)
        enumChosenObject = EnumChosenObject.CROSS;
       /* surface.crosses();
        switch (enumChosenObject) {
            case CROSS:
                if (gotPicture) {
                    surface.getCrosses().add(cross);
                    surface.repaint();
                    variable = false;
                    surface.getCrosses().remove(surface.getCrosses().size() - 1);
                    break;
                }
        }*/
    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    //AK VYKRESLUJES TIEN
    @Override
    public void mouseExited(MouseEvent e) {


       /* switch (enumChosenObject) {
            case CROSS:
                if (surface.WTF() != 0)
                surface.getCrosses().remove(surface.getCrosses().size() - 1);
                surface.repaint();
                variable = false;
                break;
        }*/
    }

    @Override
    public void mouseDragged(MouseEvent e) {

        if (enumActivity != EnumActivity.CHANGECOLOR) {
            switch (enumChosenObject) {
                case CROSS:
                /*if (variable)
                    surface.getCrosses().remove(surface.getCrosses().size() - 1);*/

                    this.surface.getCrosses().set(this.surface.getCrosses().size() - 1, new Cross(this.stlaceneX, this.stlaceneY, e.getX(), e.getY(), color));
                    this.surface.repaint();
                    //variable =false;
                    break;

                case MOVING:
                    this.cross.setX(e.getX() - this.posunX);
                    this.cross.setY(e.getY() - this.posunY);
                    this.surface.repaint();


                    break;
                case LINE:
                    this.surface.getLines().set(this.surface.getLines().size() - 1, new Line(this.stlaceneX, this.stlaceneY, e.getX(), e.getY(), color));
                    this.surface.repaint();


            }

        }
    }



    //AK CHCES NECHAVAT TIEN
    @Override
    public void mouseMoved(MouseEvent e) {

      /*  gotPicture = true;
        switch (enumChosenObject) {
            case CROSS:
                cross = new Cross(new Point(e.getX()-15, e.getY()-15) , color); //new Trees(e.getPoint());
                if (variable)
                    surface.getCrosses().remove(surface.getCrosses().size() - 1);
                cross.setX(e.getX()-15);
                cross.setY(e.getY()-15);
                surface.getCrosses().add(cross);
                surface.repaint();
                variable = true;
                break;*/
                /*
            case LINE:
                houses = new Houses(e.getPoint());
                if (variable)
                    surface.getHouses().remove(surface.getHouses().size()-1);
                houses.setX(e.getX());
                houses.setY(e.getY());
                surface.getHouses().add(houses);
                break;
            default:

        }
        surface.repaint();
        variable = true;


    }*/
        }
    }


