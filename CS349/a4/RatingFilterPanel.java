import java.awt.Dimension;
import java.util.ArrayList;

import javax.swing.JPanel;

public class RatingFilterPanel extends JPanel
{
	static int MaxRating = 5;

	private Model model;
	private ArrayList<RatingStar> stars;

	RatingFilterPanel(Model model)
	{
		this.setPreferredSize(new Dimension(180, 40));

		this.model = model;
		this.stars = new ArrayList<RatingStar>();
		for (int i = 1; i <= MaxRating; i++)
		{
			RatingStar star = new RatingStar(i, 30, 28, true);
			this.stars.add(star);
			this.add(star);
		}
	}

	public void setRating(int rating)
	{
		if (rating == model.getRating())
		{
			rating = 0;
		}
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
		model.setRating(rating);
	}
}
