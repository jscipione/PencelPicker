/*
 * Copyright 2012-2023 John Scipione All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef PENCIL_PICKER_APP_H
#define PENCIL_PICKER_APP_H


#include <Application.h>


extern const char* kSignature;


class PencilPickerPanel;

class PencilPickerApp : public BApplication {
public:
								PencilPickerApp();
								~PencilPickerApp();

	virtual	void				MessageReceived(BMessage* message);
	virtual	void				ReadyToRun();

private:
			PencilPickerPanel*	fPanel;
};


#endif	// PENCIL_PICKER_APP_H
