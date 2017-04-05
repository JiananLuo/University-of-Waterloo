import java.awt.Dimension;
import java.util.ArrayList;

import javax.swing.JPanel;

public class RatingPanel extends JPanel
{
	static int MaxRating = 5;

	private Video video;
	private ArrayList<RatingStar> stars;

	RatingPanel()
	{
		this.stars = new ArrayList<RatingStar>();

		this.setMinimumSize(new Dimension(130, 30));
		this.setMaximumSize(new Dimension(130, 30));
		this.setPreferredSize(new Dimension(130, 30));

		for (int i = 1; i <= MaxRating; i++)
		{
			RatingStar star = new RatingStar(i, 20, 18, false);
			this.stars.add(star);
			this.add(star);
		}
	}

	public void setVideo(Video video)
	{
		this.video = video;
		updateRating(video.getRating());
	}

	public void setRating(int rating)
	{
		if (rating == video.getRating())
		{
			rating = 0;
		}
		video.setRating(rating);
	}

	public void updateRating(int rating)
	{
		// set empty star
		for (int i = 0; i < rating; i++)
		{
			stars.get(i).setRated(true);
		}
		// set full star
		for (int i = rating; i < MaxRating; i++)
		{
			stars.get(i).setRated(false);
		}
	}
}