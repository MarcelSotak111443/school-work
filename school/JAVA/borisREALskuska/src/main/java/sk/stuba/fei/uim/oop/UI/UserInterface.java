package sk.stuba.fei.uim.oop.UI;

import sk.stuba.fei.uim.oop.logic.UniversalAdapter;
import sk.stuba.fei.uim.oop.objects.ObjectEnum;

import javax.swing.*;
import javax.swing.event.ChangeEvent;
import java.awt.*;
import java.awt.event.ActionEvent;

public class UserInterface extends UniversalAdapter {


    private JSlider jSliderLenght;
    private JSlider jSliderSpacing;
    private JSlider jSliderRadius;
    private Surface surface;
    private ObjectEnum objectEnum;

    public UserInterface()  {
        super();


        surface = new Surface();
        objectEnum = ObjectEnum.CIRCLE;


        JFrame jFrame = new JFrame();
        jFrame.setSize(1000, 1000);
        jFrame.setResizable(true);
        jFrame.setFocusable(true);
        jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        jFrame.setLayout(new BorderLayout());

        JPanel panelLeft = new JPanel();
        BorderLayout borderLayout = new BorderLayout();
        panelLeft.setLayout(borderLayout);
        panelLeft.setBackground(Color.RED);

        JPanel panelTop = new JPanel();
        JLabel jLabelLenght = new JLabel("lenght");
        JLabel jLabelradius = new JLabel("radius");
        JLabel jLabelspacing = new JLabel("spacing");
        panelTop.add(jLabelLenght , BorderLayout.LINE_START);
        panelTop.add(jLabelradius , BorderLayout.CENTER);
        panelTop.add(jLabelspacing, BorderLayout.LINE_END);

        jSliderLenght = new JSlider(JSlider.VERTICAL, 0, 200, 10);
        jSliderLenght.setFocusable(false);
        jSliderLenght.setPaintTicks(true);
        jSliderLenght.setPaintLabels(true);
        jSliderLenght.setMinorTickSpacing(1);
        jSliderLenght.setMajorTickSpacing(10);
        jSliderLenght.setValue(50);
        jSliderLenght.setMinimum(20);

        jSliderRadius = new JSlider(JSlider.VERTICAL, 0, 20, 4);
        jSliderRadius.setFocusable(false);
        jSliderRadius.setFocusable(false);
        jSliderRadius.setPaintTicks(true);
        jSliderRadius.setPaintLabels(true);
        jSliderRadius.setMinorTickSpacing(1);
        jSliderRadius.setMajorTickSpacing(1);
        jSliderRadius.setMinimum(1);
        jSliderRadius.setValue(5);
        jSliderSpacing = new JSlider(JSlider.VERTICAL, 0, 20, 4);
        jSliderSpacing.setFocusable(false);
        jSliderSpacing.setFocusable(false);
        jSliderSpacing.setPaintTicks(true);
        jSliderSpacing.setPaintLabels(true);
        jSliderSpacing.setMinorTickSpacing(1);
        jSliderSpacing.setMajorTickSpacing(1);
        jSliderSpacing.setMinimum(1);
        jSliderSpacing.setValue(5);

        jSliderLenght.addChangeListener(this);
        jSliderRadius.addChangeListener(this);
        jSliderSpacing.addChangeListener(this);


        String[] zoznamRozmerov = {"CIRCLE", "RECT", "HOURGLASS"};
        JComboBox comboBox = new JComboBox<>(zoznamRozmerov);

        comboBox.addActionListener(this);

        JPanel  leftTop = new JPanel(new BorderLayout());


        GridLayout gridLayout = new GridLayout(1,3);
        JPanel gridPanel = new JPanel(gridLayout);

        gridPanel.add(jSliderLenght);
        gridPanel.add(jSliderRadius);
        gridPanel.add(jSliderSpacing);

        leftTop.add(panelTop, BorderLayout.NORTH);
        leftTop.add(comboBox, BorderLayout.SOUTH);
        leftTop.add(gridPanel );

        panelLeft.add(leftTop);


        jFrame.add(panelLeft, BorderLayout.LINE_START);

        surface.addMouseMotionListener(surface);
        jFrame.add(surface);
        jFrame.setVisible(true);

    }
    @Override
    public void stateChanged(ChangeEvent e) {
       if (((JSlider) e.getSource()) == jSliderLenght){
           surface.setLenght(((JSlider) e.getSource()).getValue());
           System.out.println(((JSlider) e.getSource()).getValue());
       }
        if (((JSlider) e.getSource()) == jSliderRadius){
            surface.setRadius(((JSlider) e.getSource()).getValue());
            System.out.println(((JSlider) e.getSource()).getValue());

        }
        if (((JSlider) e.getSource()) == jSliderSpacing){
            surface.setSpacing(((JSlider) e.getSource()).getValue());
            System.out.println(((JSlider) e.getSource()).getValue());
        }
        surface.repaint();
    }

    @Override
    public void actionPerformed(ActionEvent e) {

        JComboBox<String> comboBox = (JComboBox<String>) e.getSource();
        switch (comboBox.getSelectedIndex()){
            case 0:
                objectEnum = ObjectEnum.CIRCLE;
                break;
            case 1:
                objectEnum = ObjectEnum.RECT;
                break;
            case 2:
                objectEnum = ObjectEnum.HOURGLASS;
                break;
        }

        surface.setObjectEnum(objectEnum);
    }
    }

