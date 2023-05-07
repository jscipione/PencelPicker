/*
 * Copyright 2012-2023 John Scipione All rights reserved.
 * Distributed under the terms of the MIT License.
 */
#ifndef SELECTED_PENCIL_H
#define SELECTED_PENCIL_H


#include "Pencil.h"


class BBitmap;
class BRect;

class SelectedPencil : public Pencil {
public:
								SelectedPencil(rgb_color color);
	virtual						~SelectedPencil();

	virtual	void				AttachedToWindow();
};


#endif	// SELECTED_PENCIL_H
