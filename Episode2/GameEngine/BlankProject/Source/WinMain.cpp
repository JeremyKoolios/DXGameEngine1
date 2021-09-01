#include <windows.h>

#define MAX_NAME_STRING 256											//#define is a macro the replaces all occurences with something
#define HInstance() GetModuleHandle(NULL)							//returns current hInstance

WCHAR WindowClass[MAX_NAME_STRING];
WCHAR WindowTitle[MAX_NAME_STRING];

INT WindowWidth;
INT WindowHeight;

																	//entry point
																	//WinMain declaration is pretty much windows boilerplate code to get the program to work

																	//hInstance is basically a representation of the entire project that is running
																	//hInstance is something called a "handle to an instance" or "handle to a module." The operating system uses this value to identify the executable (EXE) when it is loaded in memory. The instance handle is needed for certain Windows functions—for example, to load icons or bitmaps.

																	//hPrevInstance has no meaning.It was used in 16 - bit Windows, but is now always zero.

																	//lpCmdLine allows us to put different commands into our program at runtime

																	//nCmdShow commands to choose whether to show the window at the beginning or not
																	//nCmdShow is a flag that says whether the main application window will be minimized, maximized, or shown normally.
int CALLBACK WinMain(HINSTANCE, HINSTANCE, LPSTR, INT) 
{
	//INITIALIZE GLOBAL VARIABLES

	wcscpy_s(WindowClass, TEXT("Window1Class"));					//Copy Wide String function works with character arrays
	wcscpy_s(WindowTitle, TEXT("First Window"));
	WindowWidth = 1366;
	WindowHeight = 768;

	//CREATE WINDOW CLASS

	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);								//set the size of class to itself. like initializing itself.
	wcex.style = CS_HREDRAW | CS_VREDRAW;							//Horizontal and vertical redraw. These are always the same. These are flags (flags are represented as bitfields)
	wcex.cbClsExtra = 0;											//These 2 variables allow us to allocate exta memory at runtime
	wcex.cbWndExtra = 0;

	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);					//sets cursor and background styles. Directx can take care of these.
	wcex.hbrBackground = (HBRUSH)GetStockObject(NULL_BRUSH);

	wcex.hIcon = LoadIcon(0, IDI_APPLICATION);						//icon to appear on window. IDI_APPLICATION is basic default image for all applications
	wcex.hIconSm = LoadIcon(0, IDI_APPLICATION);					//icon to appear on taskbar

	wcex.lpszClassName = WindowClass;

	wcex.lpszMenuName = nullptr;									//These menus refer to windows submenus and stuff

	wcex.hInstance = HInstance();

	wcex.lpfnWndProc = DefWindowProc;								//setting it to just basic windows process for now

	RegisterClassEx(&wcex);

	//CREATE AND DISPLAY OUR WINDOW
	HWND hWnd = CreateWindow(WindowClass, WindowTitle, WS_OVERLAPPEDWINDOW, 
		CW_USEDEFAULT, 0, WindowWidth, WindowHeight, nullptr, nullptr, HInstance(), nullptr);	//hWnd is a representation of our window
	
	if (!hWnd)														//exception throwing
	{
		MessageBox(0, L"Failed to Create Window.", 0, 0);			//L before the string means wchar_t
		return 0;
	}
	ShowWindow(hWnd, SW_SHOW);										//SW_SHOW makes window visible

	//LISTEN FOR MESSAGE EVENTS. (The operating system communicates with your application window by passing messages to it. A message is simply a numeric code that designates a particular event. For example, if the user presses the left mouse button, the window receives a message that has the following message code.)
	MSG msg = { 0 };
	while (msg.message != WM_QUIT)									//prevents application from instantly turning off
	{
		//if there are window messages then process them
		if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))					//returns true if message is detected. non-blocking command. lets doesn't get in the way of game engine
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);									//send message to window
		}
	}

	return 0;
}