/**
 * rand_bmp_generator.h
 *
 * Created on: 17.03.2018
 *     Author: Lev Vorobjev
 *      Email: lev.vorobjev@rambler.ru
 *
 * Copyright (C) 2018 Lev Vorobjev
 */

#ifndef RAND_BMP_GENERATOR_H
#define RAND_BMP_GENERATOR_H

#include "bmp_generator.h"

class RandBmpGenerator : public BmpGenerator {
public:
	RandBmpGenerator(int nWidth, int nHeight)
		: BmpGenerator(nWidth, nHeight) { }
	virtual ~RandBmpGenerator() { }
	void initialize();
	void set_state(int layer);
	void step(double step);
};

#endif
