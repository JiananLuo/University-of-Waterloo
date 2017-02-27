import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import javax.swing.BorderFactory;
import javax.swing.JPanel;

public class DoodlePanel extends JPanel
{
	public DoodlePanel(Model model, MenuBar menuBar, FunctionPanel functionPanel, FramePanel framePanel,
			DrawPanel drawPanel)
	{
		this.setLayout(new BorderLayout());
		this.setBorder(BorderFactory.createLineBorder(Color.BLUE));
		this.setPreferredSize(new Dimension(800, 600));

		this.add(menuBar, BorderLayout.NORTH);
		this.add(functionPanel, BorderLayout.WEST);
		this.add(framePanel, BorderLayout.SOUTH);
		this.add(drawPanel, BorderLayout.CENTER);
	}
}
