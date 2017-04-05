import java.io.Serializable;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.concurrent.TimeUnit;
import com.google.api.client.util.DateTime;
import com.google.api.services.youtube.model.SearchResult;
import com.google.api.services.youtube.model.SearchResultSnippet;

public class Video implements Serializable
{
	private int index;

	private String imageURL;
	private String id;
	private String channelTitle;
	private String title;
	private DateTime publishedDate;
	private int rating;

	Video(SearchResult result, int index)
	{
		SearchResultSnippet snippet = result.getSnippet();

		this.index = index;

		this.channelTitle = snippet.getChannelTitle();
		this.imageURL = snippet.getThumbnails().getDefault().getUrl();
		this.id = result.getId().getVideoId();
		this.title = snippet.getTitle();
		this.publishedDate = snippet.getPublishedAt();
		this.rating = 0;
	}

	public String getImageURL()
	{
		return this.imageURL;
	}

	public String getNavigateURL()
	{
		return "https://www.youtube.com/watch?v=" + this.id;
	}

	public String getChannel()
	{
		return this.channelTitle;
	}

	public String getTitle()
	{
		return this.title;
	}

	public String getTime()
	{
		DateFormat dateFormat = new SimpleDateFormat("YYYY-MM-DD");
		try
		{
			Date date = dateFormat.parse(publishedDate.toString().substring(0, 9));
			Date now = new Date();
			long diffInMS = now.getTime() - date.getTime();
			long diffInDays = TimeUnit.MILLISECONDS.toDays(diffInMS);
			if (diffInDays >= 365)
			{
				return (int) (diffInDays / 365) + " years ago";
			}
			if (diffInDays >= 30.5)
			{
				return (int) (diffInDays / 30.5) + " months ago";
			}
			if (diffInDays >= 1)
			{
				return diffInDays + " days ago";
			}
			return " 0 day ago";
		}
		catch (ParseException e)
		{
		}
		return "0 day ago";
	}

	public void setRating(int rating)
	{
		this.rating = rating;
		YouTubePanelResultPanel.listViewPanels.get(this.index).updatePanel();
		YouTubePanelResultPanel.gridViewPanels.get(this.index).updatePanel();
	}

	public int getRating()
	{
		return this.rating;
	}
}
