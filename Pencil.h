/*
 * Copyright 2012-2021 2023 John Scipione All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef _PENCIL_H
#define _PENCIL_H


#include <Control.h>


class BBitmap;
class BMessage;
class BPoint;
class BRect;

class Pencil : public BControl {
public:
								Pencil();
								Pencil(rgb_color color);
								~Pencil();

	virtual	void				AttachedToWindow();
	virtual	void				Draw(BRect updateRect);
	virtual status_t			Invoke(BMessage* message = NULL);
	virtual	void				MouseDown(BPoint where);

			rgb_color			Color() const;
			void				SetColor(rgb_color color);

protected:
			rgb_color			fColor;
			BBitmap*			fIcon;
};


#endif	// _PENCIL_H
