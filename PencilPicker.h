/*
 * Copyright 2012-2025 John Scipione. All rights reserved.
 * Copyright 1999, Be Incorporated. All rights reserved.
 *
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
	virtual	void				MouseDown(BPoint where);
	virtual	void				MouseMoved(BPoint where, uint32 code,
									const BMessage* dragMessage);
	virtual	void				MouseUp(BPoint where);

			rgb_color			Color() const { return fColor; };
			void				SetColor(rgb_color color);

private:
			rgb_color			fColor;
			SelectedPencil*		fSelectedColor;
			int32				fPencilCount;
			Pencil*				fPencilList[kMaxPencilCount];
			BPoint				fMouseOffset;
			bool				fMouseDown : 1;
};


#endif	// PENCIL_PICKER_H
