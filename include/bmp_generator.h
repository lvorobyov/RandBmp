/**
 * bmp_generator.h
 *
 * Created on: 17.03.2018
 *     Author: Lev Vorobjev
 *      Email: lev.vorobjev@rambler.ru
 *
 * Copyright (C) 2018 Lev Vorobjev
 */

#ifndef BMP_GENERATOR_H
#define BMP_GENERATOR_H

#define N_LAYERS 3

typedef struct _render_data_t {
	int nWidth;
	int nHeight;
	double* lpdLayers;
	double* lpdOldLayers;
	double dTime;
} render_data_t;

class BmpGenerator {
protected:
	int nWidth;
	int nHeight;
	double* lpdLayers;
	double* lpdOldLayers;
	double dTime;
public:
	BmpGenerator(int nWidth, int nHeight);
	virtual ~BmpGenerator();
	virtual void initialize() = 0;
	virtual void step(double step) = 0;
	int getWidth() const;
	int getHeight() const;
	double* getData();
};

#endif
