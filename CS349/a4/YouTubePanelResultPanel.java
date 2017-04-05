import javax.swing.JPanel;

import java.awt.GridLayout;
import java.util.ArrayList;

public class YouTubePanelResultPanel extends JPanel implements Observer
{
	static int MAX_RESULT = 25;
	static int LIST_VIEW = 0;
	static int GRID_VIEW = 1;

	private Model model;
	int panelType;
	static ArrayList<VideoPanel> listViewPanels;
	static ArrayList<VideoPanel> gridViewPanels;

	public YouTubePanelResultPanel(Model model)
	{
		this.model = model;
		this.panelType = model.getPanelType();
		this.setLayout(new GridLayout(MAX_RESULT, 1));

		listViewPanels = new ArrayList<VideoPanel>();
		gridViewPanels = new ArrayList<VideoPanel>();

		for (int i = 0; i < MAX_RESULT; i++)
		{
			VideoPanel videoPanelListView = new VideoPanel(LIST_VIEW);
			listViewPanels.add(videoPanelListView);

			VideoPanel videoPanelGridView = new VideoPanel(GRID_VIEW);
			gridViewPanels.add(videoPanelGridView);
		}
		model.addObserver(this);
		model.setChanged(false);
	}

	public void kickPanelout(VideoPanel videlPanel)
	{
		this.remove(videlPanel);
	}

	public int getFilterRate()
	{
		return model.getRating();
	}

	public void setCol(int col)
	{
		GridLayout ma = (GridLayout) this.getLayout();
		if (col != ma.getColumns())
		{
			ma.setColumns(col);
			ma.setRows(0);
			this.revalidate();
		}
	}

	@Override
	public void update(Object observable)
	{
		this.panelType = model.getPanelType();
		this.removeAll();
		if (panelType == LIST_VIEW)
		{
			this.setLayout(new GridLayout(MAX_RESULT, 1));
		}
		else if (panelType == GRID_VIEW)
		{
			this.setLayout(new GridLayout(0, 3));
		}
		if (model.isChanged())
		{
			model.setChanged(false);
			ArrayList<Video> videos = model.getVideos();
			for (int i = 0; i < videos.size(); i++)
			{
				Video video = videos.get(i);
				listViewPanels.get(i).setInfo(video);
				gridViewPanels.get(i).setInfo(video);
			}
			for (VideoPanel videoPanel : (this.panelType == LIST_VIEW) ? listViewPanels
					: gridViewPanels)
			{
				this.add(videoPanel);
			}
		}
		else
		{
			for (VideoPanel videoPanel : (this.panelType == LIST_VIEW) ? listViewPanels
					: gridViewPanels)
			{
				if (videoPanel.getRating() >= model.getRating())
				{
					this.add(videoPanel);
				}
			}
		}
		this.revalidate();
		this.repaint();
	}
}
