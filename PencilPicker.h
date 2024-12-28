/*
 * Copyright 1999, Be Incorporated. All rights reserved.
 * Copyright 2012-2023 John Scipione All rights reserved.
 * This file may be used under the terms of the Be Sample Code License.
 */
#ifndef PENCIL_PICKER_H
#define PENCIL_PICKER_H


#include <View.h>


const int32 kMaxPencilCount = 48;


class BBitmap;
class Pencil;
class SelectedPencil;


class PencilPicker : public BView {
public:
								PencilPicker();
	virtual						~PencilPicker();

	virtual	void				AttachedToWindow();
	virtual	void				MessageReceived(BMessage* message);

			rgb_color			Color() const { return fColor; };
			void				SetColor(rgb_color color);

private:
			rgb_color			fColor;
			int32				fPencilCount;
			SelectedPencil*		fSelectedColor;
			Pencil*				fPencilList[kMaxPencilCount];
};


#endif	// PENCIL_PICKER_H
