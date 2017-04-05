YoutubeGallery
Jianan Luo
20523403

Main:
	Main class, where YoutubeGallery starts.

YouTubeView:
	The program frame. size: 800 * 600 (minSize 490 * 300)

Observer:
	Just a observer class

ModelYouTube:
	The provided class for modelling youtube result

Model:
	Where videos are stored. Save&Load logic is here.

YouTubePanel:
	Big Panel where contains the toolbar and the ResultPanel

YouTubePanelControlPanel:
	The toolbar menu where you can save&load/start a new search/change view

YouTubePanelResultPanel:
	The panel which contains all the small video panels

YouTubePanelResultPanelScroll
	Allow YouTubePanelResultPanel to scrollable

VideoPanel:
	Where contains information for each video

VideoPanelThumbnailView:
	Where the video images are and when click the image, it will navigate to the web on browser

Video:
	The video model class contains all the information we need for each video

RatingFilterPanel:
	The rating filter panel where user can filter videos using it
		
RatingPanel
	The rating panel where user can rate each video using it
			
RatingStar
	The rating stars inside rating panel, each ratingPanel contains 5 ratingStars, by click the same rating, the rating set to 0