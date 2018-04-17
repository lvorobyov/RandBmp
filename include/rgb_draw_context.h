/**
 * rgb_draw_context.h
 *
 * Created on: 17.03.2018
 *     Author: Lev Vorobjev
 *      Email: lev.vorobjev@rambler.ru
 *
 * Copyright (C) 2018 Lev Vorobjev
 */

#ifndef RGB_DRAW_CONTEXT_H
#define RGB_DRAW_CONTEXT_H

#include "draw_context.h"

class RgbDrawContext : public DrawContext {
public:
	virtual void draw(BmpGenerator* generator, LPBITMAP lpbm);
};

#endif
