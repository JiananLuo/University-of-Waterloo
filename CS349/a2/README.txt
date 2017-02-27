Doodle
Jianan Luo
20523403

Doodle:
	Main class, where doodle starts and all panels are generated here.

DoodleView:
	The program frame.

Observer:
	Just a observer class

Model:
	Where datas are stored. Methods here are mostly set&get the data in the model. Most of the setValue methods will call notifyObservers() to update the view

DoodlePanel:
	The biggest panel fit the entire window where contains all other objects(panels/buttons/slider) to display

Menubar:
	The North Menubar of DoodlePanel
		where allows users to:
			New: clean draw panel (will ask save if theres unsave stuff. in binary format .bin extension)
			Save: save the file (in binary format .bin extension, this button is disabled when nothing to save)
			Load: load up a file (will ask save if theres unsave stuff. in binary format .bin extension)
			Quit: end the program (will ask save if theres unsave stuff. in binary format .bin extension)

FunctionPanel:
	The West FunctionalPanel of DoodlePanel
		where user can choose color and thickness here. There's also a dot model. Shows the color & thichkness for the current drawing

DrawPanel:
	The Center DrawPanel of DoodlePanel
		where user could draw things here.

FramePanel:
	The South FramePanel of DoodlePanel
		where user could play with the slider and buttons to see the animation they've created/loaded.
			"<<": play animation backward, this button is disabled when current frame is in the beginning
			">>": play animation forward, this button is disabled when current frame is in the end
			"start": set the current frame to the beginning, this button is disabled when current frame is in the beginning
			"end": set the crrent frame to the end, this button is disabled when current frame is in the end

Color Palette:
	The North ColorPalette of FunctionPanel
		where user could select the color they want to use for the following drawing
			2*6 basic colorButton gives basic colors for users, right-click on them could invoke colorChooer to customize their default color
			last button displays the current selected color, and will invoke colorChooser when click it to select more color user want

ColorButton:
	Just a colorButton class

StrokeThickness:
	The Center StrokeThicknessPanel of FunctionPanel
		which contains a silder to select the thichness user want to draw for following drawing

DotModel:
	The South DotModel of FunctionPanel
		which its a dot model. Shows the current selected color & thichkness for the current drawing
Stroke:
	Just a stroke class, where contains information for each stroke



Enhancement:
	- Accurate representation of time. It should take an amount of time to play back a stroke that is proportional to how long it took to draw, and the tick-marks on the playback bar should be spaced appropriately. (10 marks)

	- Ability to play animations both forward and backward (5 marks).
		("<<" play backward && ">>" play forward)

	- Customizable color palette, as in you can wholly or partially customize color buttons in palette (5 marks).
		(Right click on every colorButton, colorChooser will be invoke. Selected color will replace the original color)

