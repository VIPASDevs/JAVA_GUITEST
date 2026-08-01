#include <X11/Xlib.h> //this gives access to the X11 library
#include <X11/Xutil.h> //as the name suggests, it gives acces to utilities in X11 library
#include <iostream> //so basic I won't explain
#include <cstring> //allows strlen and other things withs strings
using namespace std;

int main() {
	//establish a connection to the graphical server
	Display* display = XOpenDisplay(NULL); //this tells the program to look at $DISPLAY and choose whatever the user is looking at
	if (display == NULL) {
		cerr << "ERROR: UNABLE TO OPEN X DISPLAY.\n";
		return 1;
	} //these past 4 lines prepares a custom error message for the software not being able to find the X display server
	
	
	int screen = DefaultScreen(display); //this searches for the active monitor screnn
	unsigned long black = BlackPixel(display, screen); //this asks for the exact binary numeric value of black as it can change
													   //depending on hardware
	
	unsigned long white = WhitePixel(display, screen); //the exact same function as white
	
	
	//'Window' is a special variable managed by X11 that gets assigned to the window
	Window window = XCreateSimpleWindow(
		display,
		RootWindow(display, screen), //this tells the program to draw it directly on the desktop not another window
		100, 100, 800, 600, 1,
		//the first 100 draws from left to top left(?)
		//the second 100 draws from top edge to top left(?)
		//800 is the default horizontal width of the window in px
		//600 is the default vertical width of the window in px
		//1 is the border width
		
		black, white
		//black is for the border
		//white is the inner colour
	);
	
	
	
	XStoreName(display, window, "C++ Window"); //this creates the name of the Window that you see at the top
	
	XSelectInput(display, window, ExposureMask | KeyPressMask | StructureNotifyMask);
	//ExposureMask tells the program when it needs to redraw
	//KeyPressMask tells the program what keys the user presses
	//StructureNotifyMask tells the program it's new sizes so it doesn't freak out when resized
	
	
	Atom wmDeleteMessage = XInternAtom(display, "WM_DELETE_WINDOW", False);
	//Atom is a unique integer identity used by X11 to represent strings
	//XInternAtom tells the window manager to give the specific ID number
	//False tells X11 to create an ID number for it if it doesnt have one
	
	
	XSetWMProtocols(display, window, &wmDeleteMessage, 1);
	//XSetWMProtocols sets a custom communication from the DE/WM and software
	//&wmDeleteMessage passes the ID.
	//1 is used since I am only using 1 protocol (WM_DELETE_WINDOW)
	
	
	XMapWindow(display, window);
	//this line simply tells it to be drawn
	
	cout << "Window initialized successfully.";
	//this prints out onto the terminal
	
	
	GC gc = XCreateGC(display, window, 0, NULL);
	//GC is a handle for something inside X11 architecture
	//gc is the name of this which must be called to use the 'paint brush'
	//0 tells the system to use the default of the system
	//NULL tells it to use a standard paintbrush which will be manually changed later
	
	
	XSetForeground(display, gc, black);
	//XSetForeground refers to what we currently are drawing
	/*by the way, X11 does thing strictly from top-bottom...
	  ...Guess X11 is a power top ;)*/
	  
	const char* windowMessage = "HELLO, WORLD!";
	//pretty self explanatory
	
	
	XEvent event;
	bool running = true;
	while (running) {
		XNextEvent(display, &event);
		
		cout << "INTERACTION HAPPENED.\n";

		switch (event.type) {
			case Expose:
				//this event fires when the window needs to redraw itself
				cout << "Window visibility refreshed." << endl;
				
				XDrawString(display, window, gc, 50, 100, windowMessage, strlen(windowMessage));
				//the 50 means draw the text 50 pixels left (X-Axis)
				//the 100 means draw the text 100 pixels down (Y-Axis)
				break;

			case ClientMessage:
				//handle the user clicking the [X] window close button
				if (event.xclient.data.l[0] == wmDeleteMessage) {
					cout << "Close button clicked." << endl;
					running = false;
				}
				break;

			case KeyPress:
				//handle the user hitting any key on their keyboard
				cout << "Key pressed inside window. Exiting application." << endl;
				running = false;
				break;
		}
	}
	
	XFreeGC(display, gc);
	XDestroyWindow(display, window);
	XCloseDisplay(display);
	//these three lines are self-explanatory
	
	cout << "FINISHED";
	return 0;
}
