/*
 * Copyright 2012-2025 John Scipione. All rights reserved.
 * Copyright 1999, Be Incorporated. All rights reserved.
 *
 * This file may be used under the terms of the Be Sample Code License.
 */


#include "PencilPicker.h"

#include <Alignment.h>
#include <Bitmap.h>
#include <ControlLook.h>
#include <InterfaceDefs.h>
#include <LayoutBuilder.h>
#include <PickerProtocol.h>
#include <Rect.h>
#include <SpaceLayoutItem.h>

#include "Pencil.h"
#include "SelectedPencil.h"


static const rgb_color kRed = make_color(255, 0, 0, 255);


PencilPicker::PencilPicker()
	:
	BView("colored pencil color picker", B_WILL_DRAW),
	fColor(kRed),
	fSelectedColor(NULL),
	fPencilCount(kMaxPencilCount),
	fMouseOffset(B_ORIGIN),
	fMouseDown(false)
{
	fSelectedColor = new SelectedPencil(fColor);

	// add a bunch of colored pencils
	for (int32 i = 0; i < fPencilCount; i++)
		fPencilList[i] = new Pencil;

	BLayoutBuilder::Group<>(this, B_HORIZONTAL, 0)
		.AddGlue()
		.Add(fSelectedColor)
		.Add(BSpaceLayoutItem::CreateHorizontalStrut(
			B_USE_SMALL_SPACING))
		.AddGroup(B_VERTICAL, 0)
			.AddGroup(B_HORIZONTAL, 0)
				.Add(fPencilList[0])
				.Add(fPencilList[1])
				.Add(fPencilList[2])
				.Add(fPencilList[3])
				.Add(fPencilList[4])
				.Add(fPencilList[5])
				.Add(fPencilList[6])
				.Add(fPencilList[7])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(B_USE_SMALL_SPACING))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(B_USE_SMALL_SPACING))
				.Add(fPencilList[8])
				.Add(fPencilList[9])
				.Add(fPencilList[10])
				.Add(fPencilList[11])
				.Add(fPencilList[12])
				.Add(fPencilList[13])
				.Add(fPencilList[14])
				.Add(fPencilList[15])
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(fPencilList[16])
				.Add(fPencilList[17])
				.Add(fPencilList[18])
				.Add(fPencilList[19])
				.Add(fPencilList[20])
				.Add(fPencilList[21])
				.Add(fPencilList[22])
				.Add(fPencilList[23])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(B_USE_SMALL_SPACING))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(B_USE_SMALL_SPACING))
				.Add(fPencilList[24])
				.Add(fPencilList[25])
				.Add(fPencilList[26])
				.Add(fPencilList[27])
				.Add(fPencilList[28])
				.Add(fPencilList[29])
				.Add(fPencilList[30])
				.Add(fPencilList[31])
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(fPencilList[32])
				.Add(fPencilList[33])
				.Add(fPencilList[34])
				.Add(fPencilList[35])
				.Add(fPencilList[36])
				.Add(fPencilList[37])
				.Add(fPencilList[38])
				.Add(fPencilList[39])
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(B_USE_SMALL_SPACING))
			.End()
			.AddGroup(B_HORIZONTAL, 0)
				.Add(BSpaceLayoutItem::CreateHorizontalStrut(B_USE_SMALL_SPACING))
				.Add(fPencilList[40])
				.Add(fPencilList[41])
				.Add(fPencilList[42])
				.Add(fPencilList[43])
				.Add(fPencilList[44])
				.Add(fPencilList[45])
				.Add(fPencilList[46])
				.Add(fPencilList[47])
			.End()
		.End()
		.AddGlue()
	.End();
}


PencilPicker::~PencilPicker()
{
}


void
PencilPicker::AttachedToWindow()
{
	fSelectedColor->SetTarget(this);
	for (int32 i = 0; i < fPencilCount; i++)
		fPencilList[i]->SetTarget(this);

	SetColor(fColor);

	fPencilList[0]->SetColor(make_color(128, 0, 0));
	fPencilList[1]->SetColor(make_color(128, 128, 0));
	fPencilList[2]->SetColor(make_color(0, 128, 0));
	fPencilList[3]->SetColor(make_color(0, 128, 128));
	fPencilList[4]->SetColor(make_color(0, 0, 128));
	fPencilList[5]->SetColor(make_color(128, 0, 128));
	fPencilList[6]->SetColor(make_color(119, 119, 119));
	fPencilList[7]->SetColor(make_color(128, 128, 128));

	fPencilList[8]->SetColor(make_color(128, 64, 0));
	fPencilList[9]->SetColor(make_color(64, 128, 0));
	fPencilList[10]->SetColor(make_color(0, 128, 64));
	fPencilList[11]->SetColor(make_color(0, 64, 128));
	fPencilList[12]->SetColor(make_color(64, 0, 128));
	fPencilList[13]->SetColor(make_color(128, 0, 64));
	fPencilList[14]->SetColor(make_color(95, 95, 95));
	fPencilList[15]->SetColor(make_color(150, 150, 150));

	fPencilList[16]->SetColor(make_color(255, 0, 0));
	fPencilList[17]->SetColor(make_color(255, 255, 0));
	fPencilList[18]->SetColor(make_color(0, 255, 0));
	fPencilList[19]->SetColor(make_color(0, 255, 255));
	fPencilList[20]->SetColor(make_color(0, 0, 255));
	fPencilList[21]->SetColor(make_color(255, 0, 255));
	fPencilList[22]->SetColor(make_color(77, 77, 77));
	fPencilList[23]->SetColor(make_color(178, 178, 178));

	fPencilList[24]->SetColor(make_color(255, 128, 0));
	fPencilList[25]->SetColor(make_color(128, 255, 0));
	fPencilList[26]->SetColor(make_color(0, 255, 128));
	fPencilList[27]->SetColor(make_color(0, 128, 255));
	fPencilList[28]->SetColor(make_color(128, 0, 255));
	fPencilList[29]->SetColor(make_color(255, 0, 128));
	fPencilList[30]->SetColor(make_color(41, 41, 41));
	fPencilList[31]->SetColor(make_color(192, 192, 192));

	fPencilList[32]->SetColor(make_color(255, 102, 102));
	fPencilList[33]->SetColor(make_color(255, 255, 102));
	fPencilList[34]->SetColor(make_color(102, 255, 102));
	fPencilList[35]->SetColor(make_color(102, 255, 255));
	fPencilList[36]->SetColor(make_color(102, 102, 255));
	fPencilList[37]->SetColor(make_color(255, 102, 255));
	fPencilList[38]->SetColor(make_color(28, 28, 28));
	fPencilList[39]->SetColor(make_color(221, 221, 221));

	fPencilList[40]->SetColor(make_color(255, 204, 102));
	fPencilList[41]->SetColor(make_color(204, 255, 102));
	fPencilList[42]->SetColor(make_color(102, 255, 204));
	fPencilList[43]->SetColor(make_color(102, 204, 255));
	fPencilList[44]->SetColor(make_color(204, 102, 255));
	fPencilList[45]->SetColor(make_color(255, 102, 204));
	fPencilList[46]->SetColor(make_color(0, 0, 0));
	fPencilList[47]->SetColor(make_color(255, 255, 255));

	for (int32 i = 0; i < fPencilCount; i++)
		fPencilList[i]->Invalidate();
}


void
PencilPicker::MessageReceived(BMessage* message)
{
	char* name;
	type_code type;
	rgb_color* color;
	ssize_t size;
	if (message->GetInfo(B_RGB_COLOR_TYPE, 0, &name, &type) == B_OK
		&& message->FindData(name, type, (const void**)&color, &size) == B_OK) {
		SetColor(*color);

		if (!message->IsSourceRemote())
			Window()->PostMessage(message);
	} else
		BView::MessageReceived(message);
}


void
PencilPicker::MouseDown(BPoint where)
{
	fMouseOffset = where;
	fMouseDown = true;

	if (Window() == NULL)
		return BView::MouseDown(where);

	Window()->Activate();

	SetMouseEventMask(B_POINTER_EVENTS, B_NO_POINTER_HISTORY
		| B_SUSPEND_VIEW_FOCUS | B_LOCK_WINDOW_FOCUS);

	BView::MouseDown(where);
}


void
PencilPicker::MouseMoved(BPoint where, uint32 code,
	const BMessage* dragMessage)
{
	if (Window() == NULL || Window()->CurrentMessage() == NULL)
		return BView::MouseMoved(where, code, dragMessage);

	uint32 buttons = Window()->CurrentMessage()->GetInt32("buttons", 0);
	if (fMouseDown && buttons == B_PRIMARY_MOUSE_BUTTON) {
		BPoint windowPosition = Window()->Frame().LeftTop();
		Window()->MoveTo(windowPosition.x + where.x - fMouseOffset.x,
			windowPosition.y + where.y - fMouseOffset.y);
	} else
		BView::MouseMoved(where, code, dragMessage);
}


void
PencilPicker::MouseUp(BPoint where)
{
	fMouseOffset = B_ORIGIN;
	fMouseDown = false;

	BView::MouseUp(where);
}


void
PencilPicker::SetColor(rgb_color color)
{
	color.alpha = 255;
	if (fColor == color)
		return;

	fColor = color;
	fSelectedColor->SetColor(color);
}
