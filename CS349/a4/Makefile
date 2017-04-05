JFLAGS = -g
JC = javac
JAVA = java
.SUFFIXES: .java .class
.java.class:
	$(JC) -cp "libs/*" $(JFLAGS) *.java

CLASSES = ModelYouTube.java Main.java Model.java Observer.java \
		RatingFilterPanel.java RatingPanel.java RatingStar.java \
		Video.java VideoPanel.java VideoPanelThumbnailView.java \
		YouTubePanel.java YouTubePanelControlPanel.java YouTubePanelResultPanel.java \
		YouTubePanelResultPanelScroll.java YouTubeView.java

default: classes

classes: $(CLASSES:.java=.class)

ifeq ($(OS),Windows_NT)
run: default
	$(JAVA) -cp "libs/*;" Main
clean:
	del *.class
else
run: default
	$(JAVA) -cp ":libs/*" Main
clean:
	rm *.class
endif

