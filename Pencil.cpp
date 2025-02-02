/*
 * Copyright 2012-2023 John Scipione All rights reserved.
 * Distributed under the terms of the MIT License.
 *
 * Authors:
 *		John Scipione, jscipione@gmail.com
 */


#include "Pencil.h"

#include <Bitmap.h>
#include <InterfaceDefs.h>
#include <Message.h>
#include <PickerProtocol.h>
#include <Rect.h>


static const int32 kPencilWidth = 20;
static const int32 kPencilHeight = 45;


static const unsigned char kPencilBits[] = {
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x09,0x09,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x09,0xff,0xff,0x09,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x09,0xff,0xff,0xff,0xff,0x09,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x09,0xff,0xff,0xff,0xff,0x09,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x09,0xff,0xff,0xff,0xff,0x09,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x09,0x5b,0xff,0xff,0xff,0xff,0xff,0xff,0x5b,0x09,0x1b,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x09,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x09,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x09,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x09,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x09,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x09,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x09,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x09,0x1b,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x09,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x09,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x09,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x09,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x1b,0x09,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x09,0x1b,0x1b,0x1b,
	0x1b,0x1b,0x09,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x09,0x1b,0x1b,
	0x1b,0x1b,0x09,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x09,0x1b,0x1b,
	0x1b,0x09,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x09,0x1b,
	0x1b,0x09,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x5b,0x09,0x1b,
	0x1b,0x09,0x5b,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x5b,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x09,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0x09,0x1b,
	0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b,0x1b
};


//	#pragma mark - Pencil


Pencil::Pencil()
	:
	BControl(BRect(0, 0, kPencilWidth - 1, kPencilHeight - 1),
		"Pencil", "", new BMessage(B_VALUE_CHANGED), B_FOLLOW_NONE,
		B_WILL_DRAW),
	fColor((rgb_color) { 0, 0, 0 }),
	fIcon(NULL),
	fMouseDownMessage(NULL)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
}


Pencil::Pencil(rgb_color color)
	:
	BControl(BRect(0, 0, kPencilWidth - 1, kPencilHeight - 1), "Pencil", "",
		new BMessage(B_VALUE_CHANGED), B_FOLLOW_NONE, B_WILL_DRAW),
	fColor(color),
	fIcon(NULL),
	fMouseDownMessage(NULL)
{
	SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
}


Pencil::~Pencil()
{
	delete fIcon;
}


void
Pencil::AttachedToWindow()
{
	fIcon = new BBitmap(Bounds(), B_CMAP8, false, false);
	fIcon->SetBits(kPencilBits, kPencilWidth * kPencilHeight, 0, B_CMAP8);
}


void
Pencil::Draw(BRect updateRect)
{
	BRect frame(Bounds());

	PushState();
	SetHighColor(fColor);
	SetLowColor(ViewColor());
	FillRect(frame);
	if (fIcon != NULL) {
		SetDrawingMode(B_OP_OVER);
		DrawBitmapAsync(fIcon, frame);
	}
	PopState();
}


status_t
Pencil::Invoke(BMessage* message)
{
	if (message == NULL)
		message = new BMessage(B_VALUE_CHANGED);

	message->AddData("RGBColor", B_RGB_COLOR_TYPE, &fColor, sizeof(fColor));

	return BControl::Invoke(message);
}


void
Pencil::MouseDown(BPoint where)
{
	fMouseDownMessage = new BMessage(B_VALUE_CHANGED);
	Invoke(fMouseDownMessage);

	BControl::MouseDown(where);
}


void
Pencil::MouseUp(BPoint where)
{
	delete fMouseDownMessage;
	fMouseDownMessage = NULL;

	BControl::MouseUp(where);
}


rgb_color
Pencil::Color() const
{
	return fColor;
}


void
Pencil::SetColor(rgb_color color)
{
	color.alpha = 255;
	fColor = color;
	if (Window() != NULL)
		Invalidate(Bounds());
}
