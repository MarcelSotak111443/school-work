import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class UI implements ActionListener {

    private JButton tree;
    private JButton house;
    private JButton line;


    private Surface surface;
    private Logic logic;
    private Color color;
    private JLabel label;
    private JButton buttonChanceColor;
    private Color[] colorsPaletter;

    private EnumAction enumAction;
    private int i;


    public UI() {

        i = 0;
        surface = new Surface();
        logic = new Logic(surface);
        enumAction = EnumAction.TREE;

        colorsPaletter = new Color[3];
        colorsPaletter[0] = Color.RED;
        colorsPaletter[1] = Color.CYAN;
        colorsPaletter[2] = Color.GRAY;

        logic.setColor(colorsPaletter);




        JFrame jFrame = new JFrame();
        jFrame.setSize(800, 800);
        jFrame.setResizable(true);
        jFrame.setFocusable(true);
        jFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        jFrame.setLayout(new BorderLayout());

        //3 buttony
        JPanel jpanelTop = new JPanel(new GridLayout(1, 4));
        tree = new JButton("TREE");
        house = new JButton("HOUSE");
        line = new JButton("LINE");

        label = new JLabel("Vyber", SwingConstants.CENTER);
        label.setOpaque(true);
        label.setBackground(Color.red);
        logic.setJLabel(label);
        label.setOpaque(true);

        jpanelTop.add(tree);
        jpanelTop.add(house);
        jpanelTop.add(line);
        jpanelTop.add(label);



        tree.addActionListener(this);
        house.addActionListener(this);
        line.addActionListener(this);


        jFrame.add(surface);

        jFrame.add(jpanelTop, BorderLayout.NORTH);
        surface.addMouseMotionListener(logic);
        surface.addMouseListener(logic);
        surface.setFocusable(true);

           jFrame.setFocusable(true);
        jFrame.setVisible(true);

    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource().equals(tree)){

            enumAction = EnumAction.TREE;
        }
        if (e.getSource().equals(house)){

            enumAction = EnumAction.HOUSE;
        }
        if (e.getSource().equals(line)){

            enumAction = EnumAction.LINE;
        }


        logic.setEnumAction(enumAction);
    }
}