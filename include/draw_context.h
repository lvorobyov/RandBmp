/**
 * draw_context.h
 *
 * Created on: 16.03.2018
 *     Author: Lev Vorobjev
 *      Email: lev.vorobjev@rambler.ru
 *
 * Copyright (C) 2018 Lev Vorobjev
 */

#ifndef DRAW_CONTEXT_H
#define DRAW_CONTEXT_H

#include "bmp_generator.h"

#include <windows.h>

class DrawContext {
public:
	virtual void draw(BmpGenerator* generator, LPBITMAP lpbm) = 0;
};

#endif
