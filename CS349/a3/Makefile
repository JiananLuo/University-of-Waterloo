JFLAGS = -g
JC = javac -encoding UTF-8
JAVA = java
.SUFFIXES: .java .class
.java.class:
	$(JC) $(JFLAGS) $*.java

CLASSES = \
	PaperDolls.java Observer.java Model.java PaperDollView.java \
        MenuBar.java DollPanel.java Sprite.java ImageSprite.java \

default: classes

classes: $(CLASSES:.java=.class)

clean:
	$(RM) *.class

run: default
	$(JAVA) -cp . PaperDolls
