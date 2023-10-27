import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class UI implements ActionListener {

    private JButton buttonCross;
    private JButton buttonLine;
    private final JComboBox<String> nastavenieVelkostiPola;
    private EnumChosenObject enumChosenObject;
    private Surface surface;
    private Logic logic;
    private Color color;
    private JLabel label;
    private JButton buttonChanceColor;
    private EnumActivity enumActivity;


    public UI() {
        enumChosenObject = EnumChosenObject.CROSS;
        enumActivity = EnumActivity.DEFAULT;

        surface = new Surface();
        logic = new Logic(surface);

        JFrame jFrame = new JFrame();
        jFrame.setSize(800, 800);
        jFrame.setResizable(true);
        jFrame.setFocusable(true);
        jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jFrame.setLayout(new BorderLayout());

       //3 buttony
        JPanel jpanelTop = new JPanel(new GridLayout(1, 5));
        buttonCross = new JButton("CROSS");
        buttonLine = new JButton("LINE");
        buttonChanceColor = new JButton("CHANGE COLOR");

        String[] zoznamRozmerov = {"RED", "YELLOW", "GREED", "BLACK"};
        nastavenieVelkostiPola = new JComboBox<>(zoznamRozmerov);

        label = new JLabel("Color", SwingConstants.CENTER);
        label.setBackground(Color.red);
        label.setOpaque(true);

        jpanelTop.add(buttonCross);
        jpanelTop.add(buttonLine);
        jpanelTop.add(nastavenieVelkostiPola);
        jpanelTop.add(label);
        jpanelTop.add(buttonChanceColor);

        nastavenieVelkostiPola.addActionListener(this);
        buttonCross.addActionListener(this);
        buttonLine.addActionListener(this);
        buttonChanceColor.addActionListener(this);

        jFrame.add(surface);

        jFrame.add(jpanelTop, BorderLayout.NORTH);
        surface.addMouseMotionListener(logic);
        surface.addMouseListener(logic);
        surface.setFocusable(true);

     //   jFrame.setFocusable(true);
        jFrame.setVisible(true);

    }
    public void actionPerformed(ActionEvent e) {

        if (e.getSource().equals(buttonCross)){
            enumChosenObject = EnumChosenObject.CROSS;
            enumActivity = EnumActivity.DEFAULT;
        }

        if (e.getSource().equals(buttonLine)){
            enumChosenObject = EnumChosenObject.LINE;
            enumActivity = EnumActivity.DEFAULT;
        }

        if (e.getSource().equals(buttonChanceColor)){
            enumActivity = EnumActivity.CHANGECOLOR;

        }

        logic.setEnumActivity(enumActivity);
        logic.setEnumChosenObject(enumChosenObject);

        if (e.getSource() == nastavenieVelkostiPola){
            enumActivity = EnumActivity.DEFAULT;
            JComboBox<String> comboBox = (JComboBox<String>) e.getSource();
     //       comboBox.setFocusable(false);
            switch (comboBox.getSelectedIndex()){
                case 0:
                    color = Color.RED;
                    System.out.println("1");
                    break;
                case 1:
                    color = Color.YELLOW;
                    System.out.println("2");
                    break;
                case 2:
                    color = Color.GREEN;
                    System.out.println("3");
                    break;
                case 3:
                    color = Color.BLACK;
                    System.out.println("4");
                    break;


            }
            logic.setColor(color);
            label.setBackground(color);
        }

       // surface.setLineOrTreeOrHouse(lineOrTreeOrHouse);
    }
}
