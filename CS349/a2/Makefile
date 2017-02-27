JFLAGS = -g
JC = javac -encoding UTF-8
JAVA = java
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	Doodle.java Model.java DoodleView.java DoodlePanel.java \
	MenuBar.java FunctionPanel.java DrawPanel.java FramePanel.java \
	ColorPalette.java ColorButton.java DotModel.java StrokeThickness.java \
Stroke.java Observer.java

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class

run: default
	$(JAVA) -cp . Main
