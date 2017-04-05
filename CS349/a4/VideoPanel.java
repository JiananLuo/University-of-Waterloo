import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.GridLayout;

import javax.swing.BorderFactory;
import javax.swing.BoxLayout;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;

public class VideoPanel extends JPanel
{
	private Video video;

	private VideoPanelThumbnailView videoThumbnail;
	private JLabel label_title;
	private JLabel label_time;
	private RatingPanel ratingPanel;

	public VideoPanel(int panelType)
	{
		videoThumbnail = new VideoPanelThumbnailView(null, null);
		label_title = new JLabel("");
		label_time = new JLabel("");
		ratingPanel = new RatingPanel();

		JPanel rating_panel = new JPanel(new BorderLayout());
		rating_panel.add(ratingPanel, BorderLayout.WEST);

		if (panelType == YouTubePanelResultPanel.LIST_VIEW)
		{
			this.setLayout(new BorderLayout());
			this.setMaximumSize(new Dimension(Integer.MAX_VALUE, 120));

			label_title.setBorder(new EmptyBorder(1, 8, 1, 0));
			label_time.setBorder(new EmptyBorder(1, 8, 1, 0));
			JPanel videoInfo = new JPanel(new GridLayout(3, 1));
			videoInfo.add(rating_panel);
			videoInfo.add(label_title);
			videoInfo.add(label_time);

			this.add(videoThumbnail, BorderLayout.WEST);
			this.add(videoInfo, BorderLayout.CENTER);
		}
		else if (panelType == YouTubePanelResultPanel.GRID_VIEW)
		{
			this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
			this.setPreferredSize(new Dimension(240, 180));
			this.setMaximumSize(new Dimension(400, 180));

			label_title.setBorder(new EmptyBorder(2, 0, 2, 0));
			label_time.setBorder(new EmptyBorder(2, 0, 2, 0));
			JPanel infoPanel = new JPanel(new GridLayout(2, 1));
			infoPanel.add(label_title);
			infoPanel.add(label_time);

			this.add(rating_panel);
			this.add(videoThumbnail);
			this.add(infoPanel);
		}
		this.setVisible(false);
	}

	void clearRating()
	{
		this.ratingPanel.updateRating(0);
	}

	int getRating()
	{
		if (this.video != null)
		{
			return this.video.getRating();
		}
		return 0;
	}

	void setInfo(Video video)
	{
		this.video = video;
		this.setBorder(BorderFactory.createTitledBorder(video.getChannel()));
		videoThumbnail.setURL(video.getImageURL(), video.getNavigateURL());
		label_title.setText(video.getTitle());
		label_time.setText(video.getTime());
		ratingPanel.setVideo(video);

		this.setVisible(true);
	}

	void setTime(String time)
	{
		this.label_time.setText(time);
	}

	public void updatePanel()
	{
		if (video != null)
		{
			this.videoThumbnail.setURL(video.getImageURL(), video.getNavigateURL());
			this.label_title.setText(video.getTitle());
			this.label_time.setText(video.getTime());
			this.ratingPanel.updateRating(video.getRating());
			YouTubePanelResultPanel parent = (YouTubePanelResultPanel) this.getParent();
			if (parent != null && parent.getFilterRate() > this.video.getRating())
			{
				parent.update(this);
			}
		}
	}
}
