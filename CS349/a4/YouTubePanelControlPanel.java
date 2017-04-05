import java.awt.Color;
import java.awt.Dimension;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.List;

import javax.imageio.ImageIO;
import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JSeparator;
import javax.swing.JTextField;
import javax.swing.JToggleButton;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;

import com.google.api.services.youtube.model.SearchResult;

public class YouTubePanelControlPanel extends JPanel
{
	private Model model;

	private JToggleButton listViewButton;
	private JToggleButton gridViewButton;
	static JTextField searchField;

	private JButton searchButton;

	private JButton saveButton;
	private JButton loadButton;

	private RatingFilterPanel ratingFilterPanel;

	public YouTubePanelControlPanel(Model model)
	{
		this.model = model;
		this.setLayout(new BoxLayout(this, BoxLayout.X_AXIS));
		this.setPreferredSize(new Dimension(800, 60));
		this.setBorder(BorderFactory.createLineBorder(Color.RED));

		initListGirdViewButton(model);
		this.add(new JSeparator(SwingConstants.VERTICAL));
		initSearchField();
		this.add(new JSeparator(SwingConstants.VERTICAL));
		initSearchButton(model);
		this.add(new JSeparator(SwingConstants.VERTICAL));
		initSaveLoadButton(model);
		this.add(new JSeparator(SwingConstants.VERTICAL));
		initRatingFilterPanel(model);
	}

	private void initListGirdViewButton(Model model)
	{
		listViewButton = new JToggleButton();
		gridViewButton = new JToggleButton();
		try
		{
			listViewButton.setIcon(
					new ImageIcon(ImageIO.read(getClass().getResource("listViewButton.png"))));
			gridViewButton.setIcon(
					new ImageIcon(ImageIO.read(getClass().getResource("gridViewButton.png"))));
		}
		catch (IOException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		listViewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e)
			{
				model.setView(YouTubePanelResultPanel.LIST_VIEW);
				gridViewButton.setSelected(false);
			}
		});
		gridViewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e)
			{
				model.setView(YouTubePanelResultPanel.GRID_VIEW);
				listViewButton.setSelected(false);
			}
		});

		this.add(listViewButton);
		this.add(gridViewButton);
	}

	private void initSearchField()
	{
		searchField = new JTextField();
		searchField.setPreferredSize(new Dimension(240, 40));
		this.add(searchField);
	}

	private void initSearchButton(Model model)
	{
		searchButton = new JButton();
		try
		{
			searchButton.setIcon(
					new ImageIcon(ImageIO.read(getClass().getResource("searchButton.png"))));
		}
		catch (IOException e)
		{
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		searchButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e)
			{
				Runnable task = new Runnable() {
					@Override
					public void run()
					{
						List<SearchResult> results = Main.youtubeModel
								.searchVideos(searchField.getText());
						ratingFilterPanel.setRating(0);
						for (int i = 0; i < 25; i++)
						{
							YouTubePanelResultPanel.listViewPanels.get(i).clearRating();
							YouTubePanelResultPanel.gridViewPanels.get(i).clearRating();
						}
						model.setSearchField(searchField.getText());
						model.setVideos(results);
					}
				};
				Thread thread = new Thread(task);
				thread.start();
			}
		});
		this.add(searchButton);

	}

	private void initSaveLoadButton(Model model)
	{
		initSaveButton(model);
		initLoadButton(model);
		JPanel saveLoadPanel = new JPanel();
		saveLoadPanel.setLayout(new BoxLayout(saveLoadPanel, BoxLayout.Y_AXIS));
		saveLoadPanel.add(saveButton);
		saveLoadPanel.add(loadButton);
		this.add(saveLoadPanel);
	}

	private void initSaveButton(Model model)
	{
		saveButton = new JButton("Save");
		saveButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e)
			{
				model.showSaveDialog();
			}
		});
	}

	private void initLoadButton(Model model)
	{
		loadButton = new JButton("Load");
		loadButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e)
			{
				model.showLoadDialog();
			}
		});
	}

	private void initRatingFilterPanel(Model model)
	{
		ratingFilterPanel = new RatingFilterPanel(model);
		ratingFilterPanel.setBorder(new EmptyBorder(8, 0, 0, 0));
		this.add(ratingFilterPanel);
	}
}
