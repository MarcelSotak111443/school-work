import lombok.Getter;
import lombok.Setter;

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
    private Color color;
    private int stlaceneX;
    private int stlaceneY;

    boolean gotPicture;
    boolean variable;
    int posunX,posunY;
    private Tree tree;
    @Setter
    private EnumAction enumAction;


    public Logic(Surface surface) {

        enumAction = EnumAction.TREE;
        this.surface = surface;
        firstClick = new Point();
        distance = new Point();
        color = Color.RED;



    }

    @Override
    public void mouseClicked(MouseEvent e) {

    }

    @Override
    public void mousePressed(MouseEvent e) {

        switch (enumAction){
            case TREE:
                this.stlaceneX = e.getX();
                this.stlaceneY = e.getY();
                this.surface.getTrees().add(new Tree(this.stlaceneX, this.stlaceneY, e.getX(), e.getY(), color));
                break;
            case MOVING:
                if (surface.getTrees(e.getPoint())!= null){

                    enumAction = EnumAction.MOVING;
                    tree = surface.getTrees(e.getPoint());
                    this.posunX = e.getX() - this.tree.getX();
                    this.posunY = e.getY() - this.tree.getY();
                }
                break;
        }
    }
    @Override
    public void mouseReleased(MouseEvent e) {

    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }

    @Override
    public void mouseDragged(MouseEvent e) {

        switch (enumAction) {
            case TREE:


                this.surface.getTrees().set(this.surface.getTrees().size() - 1, new Tree(this.stlaceneX, this.stlaceneY, e.getX(), e.getY(), color));
                this.surface.repaint();
                //variable =false;
                break;

            case MOVING:
                if (surface.getTrees(e.getPoint())!= null) {
                    this.tree.setX(e.getX() - this.posunX);
                    this.tree.setY(e.getY() - this.posunY);
                    this.surface.repaint();
                    break;
                }
        }
    }

    @Override
    public void mouseMoved(MouseEvent e) {

    }
}
