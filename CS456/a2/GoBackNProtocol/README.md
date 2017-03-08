CS456 Assignment 2

Jianan Luo
j43luo
20523403

Compile and run:
	make
	./nEmulator <emulator's receiving UDP port number in the forward (sender) direction>, <receiver’s network address>, <receiver’s receiving UDP port number>, <emulator's receiving UDP port number in the backward (receiver) direction>, <sender’s network address>, <sender’s receiving UDP port number>, <maximum delay of the link in units of millisecond>, <packet discard probability>, <verbose-mode>
	java Receiver <emulator hostName> <receive UDP Port number> <send UDP Port number> <name of the file to be written>
	java Sender <emulator hostName> <receive UDP Port number> <send UDP Port number> <name of the file to be transferred>

Built and tested on: 
	ubuntu1404-002.student.cs.uwaterloo.ca (nEmulator)
	ubuntu1404-004.student.cs.uwaterloo.ca (Receiver)
	ubuntu1404-008.student.cs.uwaterloo.ca (Sender)

Make Version:
	GNU Make 3.81

Compiler Version: 
	javac 1.8.0_112