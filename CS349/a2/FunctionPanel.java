import java.awt.BorderLayout;
import java.awt.Color;
import javax.swing.BorderFactory;
import javax.swing.JPanel;

public class FunctionPanel extends JPanel
{
	public FunctionPanel(ColorPalette colorPalette, StrokeThickness strokeThickness, DotModel dotModel)
	{
		this.setLayout(new BorderLayout());
		this.setBorder(BorderFactory.createLineBorder(Color.GRAY));
		this.add(colorPalette, BorderLayout.NORTH);
		this.add(strokeThickness, BorderLayout.CENTER);
		this.add(dotModel, BorderLayout.SOUTH);
	}
}
