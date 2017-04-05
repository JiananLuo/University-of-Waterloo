import java.awt.Color;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;

import javax.swing.BorderFactory;
import javax.swing.JScrollPane;

public class YouTubePanelResultPanelScroll extends JScrollPane implements Observer
{
	private YouTubePanelResultPanel resultPanel;

	YouTubePanelResultPanelScroll(Model model, YouTubePanelResultPanel resultPanel)
	{
		super(resultPanel);
		this.setBorder(BorderFactory.createLineBorder(Color.RED));
		this.setHorizontalScrollBarPolicy(HORIZONTAL_SCROLLBAR_NEVER);
		this.getVerticalScrollBar().setUnitIncrement(16);

		this.resultPanel = resultPanel;
		initResizeListener();

		model.addObserver(this);
	}

	private void initResizeListener()
	{
		this.addComponentListener(new ComponentAdapter() {
			public void componentResized(ComponentEvent e)
			{
				int newWidth = e.getComponent().getWidth();
				setResultPanelCol(newWidth);
			}
		});
	}

	private void setResultPanelCol(int width)
	{
		if (resultPanel.panelType == YouTubePanelResultPanel.GRID_VIEW)
		{
			if (width > 1250)
			{
				resultPanel.setCol(5);
			}
			else if (width > 1000)
			{
				resultPanel.setCol(4);
			}
			else if (width > 750)
			{
				resultPanel.setCol(3);
			}
			else if (width > 500)
			{
				resultPanel.setCol(2);
			}
			else
			{
				resultPanel.setCol(1);
			}
		}
	}

	@Override
	public void update(Object observable)
	{
		setResultPanelCol(this.getWidth());
	}
}
