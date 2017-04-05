PaperDolls
Jianan Luo
20523403

PaperDolls:
	Main class, where Paperdolls starts and the sprite is generated here.

PaperDollView:
	The program frame. size: 1280 * 800 (not resizable)

Observer:
	Just a observer class

Model:
	Where sprites are stored. Save&Load logic is here.

DollPanel:
	The panel which contains the main sprite to display

Menubar:
	The North Menubar of DoodlePanel
		where allows users to:
			Reset: reset the main sprite (Control + R)
			Save: save the file (in binary format .bin extension, this button is disabled when nothing to save) (Control + S)
			Load: load up a file (will ask save if theres unsave stuff. in binary format .bin extension) (Control + L)
			Quit: end the program (will ask save if theres unsave stuff. in binary format .bin extension) (Control + Q)

Sprite:
	Parent sprite class, where contains most of the information of the sprite

ImageSprite:
	A child class under Sprite, handles some of the sprite logic



Enhancement:
	- Image (5 marks)

	- Save & Load (5 marks).