import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import javax.swing.JButton;
import javax.swing.JColorChooser;
import javax.swing.JComponent;
import javax.swing.JOptionPane;

public class ColorButton extends JButton
{
	private Color color;

	public ColorButton(Color color, Model model)
	{
		this.color = color;
		this.setBackground(color);
		this.setOpaque(true);
		this.setBorderPainted(false);
		this.setPreferredSize(new Dimension(40, 20));

		this.addMouseListener(new MouseAdapter() {
			public void mousePressed(MouseEvent e)
			{
				if (e.getButton() == 3)
				{
					JColorChooser colorChooser = new JColorChooser(Color.BLACK);
					int action = JOptionPane.showConfirmDialog(null, new JComponent[] { colorChooser },
							"Color Chooser", JOptionPane.OK_CANCEL_OPTION);
					if (action == JOptionPane.OK_OPTION)
					{
						Color newColor = colorChooser.getColor();
						ColorButton.this.color = newColor;
						ColorButton.this.setBackground(newColor);
					}
				}
				else
				{
					model.setColor(ColorButton.this.color);
				}
			}
		});
	}

	public Color getColor()
	{
		return this.color;
	}
}
