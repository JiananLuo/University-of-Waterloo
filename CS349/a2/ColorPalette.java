import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JComponent;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

public class ColorPalette extends JPanel implements Observer
{
	private Model model;
	private Color[] basicColors = { Color.BLACK, Color.BLUE, Color.CYAN, Color.GRAY, Color.GREEN,
			Color.LIGHT_GRAY, Color.MAGENTA, Color.ORANGE, Color.PINK, Color.RED, Color.WHITE,
			Color.YELLOW };
	private JButton colorChooserButton;

	public ColorPalette(Model model)
	{
		this.model = model;
		this.setPreferredSize(new Dimension(100, 180));
		this.setMinimumSize(new Dimension(100, 100));

		initBasicColorButton();
		initColorChooserButton();
	}

	private void initBasicColorButton()
	{
		for (int i = 0; i < basicColors.length; i++)
		{
			ColorButton basicColorButton = new ColorButton(basicColors[i], this.model);
			this.add(basicColorButton);
		}
	}

	private void initColorChooserButton()
	{
		colorChooserButton = new JButton();
		colorChooserButton.setBackground(Color.BLACK);
		colorChooserButton.setOpaque(true);
		colorChooserButton.setBorderPainted(false);
		colorChooserButton.setPreferredSize(new Dimension(85, 20));
		colorChooserButton.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e)
			{
				JColorChooser colorChooser = new JColorChooser(Color.BLACK);
				int action = JOptionPane.showConfirmDialog(null, new JComponent[] { colorChooser },
						"Color Chooser", JOptionPane.OK_CANCEL_OPTION);
				if (action == JOptionPane.OK_OPTION)
				{
					Color newColor = colorChooser.getColor();
					colorChooserButton.setBackground(newColor);
					model.setColor(newColor);
				}
			}
		});
		this.add(colorChooserButton);
	}

	@Override
	public void update(Object observable)
	{
		colorChooserButton.setBackground(model.getColor());
	}

}
