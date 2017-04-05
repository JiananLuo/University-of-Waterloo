import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

import javax.swing.BorderFactory;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import static javax.swing.ScrollPaneConstants.*;

public class YouTubePanel extends JPanel
{
	public YouTubePanel(Model model)
	{
		this.setLayout(new BorderLayout());
		this.setBorder(BorderFactory.createLineBorder(Color.RED));
		this.setPreferredSize(new Dimension(800, 600));

		YouTubePanelControlPanel controlPanel = new YouTubePanelControlPanel(model);
		YouTubePanelResultPanel resultPanel = new YouTubePanelResultPanel(model);
		YouTubePanelResultPanelScroll scrollableResultPanel = new YouTubePanelResultPanelScroll(
				model, resultPanel);

		this.add(controlPanel, BorderLayout.NORTH);
		this.add(scrollableResultPanel, BorderLayout.CENTER);
	}
}
