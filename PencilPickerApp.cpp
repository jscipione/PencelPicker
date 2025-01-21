/*
 * Copyright 2012-2025 John Scipione. All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include "PencilPickerApp.h"

#include <LayoutBuilder.h>
#include <PickerProtocol.h>
#include <Window.h>

#include "PencilPicker.h"


const char* kSignature = "application/x-vnd.Haiku-PencilPicker";


using BPrivate::BColorPickerPanel;


//	#pragma mark - PencilPickerPanel


PencilPickerPanel::PencilPickerPanel(PencilPicker* view, BMessage* message)
	:
	BColorPickerPanel((PencilPicker*)view, message,
		BColorPickerPanel::B_CELLS_4x10, "Pick a color")
{
}


PencilPickerPanel::~PencilPickerPanel()
{
}


//	#pragma mark - PencilPickerApp


PencilPickerApp::PencilPickerApp()
	:
	BApplication(kSignature),
	fPanel(NULL)
{
}


PencilPickerApp::~PencilPickerApp()
{
}


void
PencilPickerApp::MessageReceived(BMessage* message)
{
	if (message->what == B_PICKER_INITIATE_CONNECTION) {
		// This is the initial open message that ModuleProxy::Invoke
		// is sending us. Pass it on to the new color picker dialog
		// where all the details will be found.
		fPanel = new PencilPickerPanel(new PencilPicker(), message);
	}

	BApplication::MessageReceived(message);
}


void
PencilPickerApp::ReadyToRun()
{
	if (fPanel != NULL)
		fPanel->Show();
	else {
		// create a window if run directly
		BWindow* window = new BWindow(BRect(100, 100, 100, 100),
			"Pick a color", B_TITLED_WINDOW, B_NOT_ZOOMABLE
				| B_NOT_RESIZABLE | B_QUIT_ON_WINDOW_CLOSE
				| B_AUTO_UPDATE_SIZE_LIMITS);

		BLayoutBuilder::Group<>(window, B_VERTICAL, 0)
			.Add(new PencilPicker())
			.SetInsets(B_USE_DEFAULT_SPACING)
			.End();
		window->Show();
	}
}


extern "C" BColorPickerPanel*
instantiate_color_picker(BView* view, BMessage* message,
	BColorPickerPanel::color_cell_layout layout, const char* name,
	window_look look, window_feel feel, uint32 flags, uint32 workspace)
{
	return new PencilPickerPanel((PencilPicker*)view, message);
}


int
main()
{
	new PencilPickerApp();
	be_app->Run();
	delete be_app;

	return 0;
}
