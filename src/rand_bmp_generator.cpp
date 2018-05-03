/**
 * rand_bmp_generator.cpp
 *
 * Created on: 17.03.2018
 *     Author: Lev Vorobjev
 *      Email: lev.vorobjev@rambler.ru
 *
 * Copyright (C) 2018 Lev Vorobjev
 */

#include <rand_bmp_generator.h>

#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifdef USE_MT19937
  #include <random>
  #define RAND_GEN  urd(gen)
#else
  #define RAND_GEN  (double)rand()/(double)RAND_MAX;
#endif

#define PARAM_ALPHA 0.01
#define PARAM_A 11
#define PARAM_H 3.0

void RandBmpGenerator::initialize() {
#ifdef USE_MT19937
    static std::mt19937 gen(time(0));
    static std::uniform_real_distribution<> urd(0.0, 1.0);
#else
    srand(time(0));
#endif
    for (int i=0; i<nWidth*nHeight*N_LAYERS; i++) {
        lpdLayers[i] = RAND_GEN;
    }
}

void RandBmpGenerator::set_state(int layer) {
    int lenght = nWidth * nHeight;

	div_t d;
	int row,col;
	for (int i=layer*lenght; i<(layer+1)*lenght; i++) {
		d = div(i,nWidth);
		row = d.quot % nHeight;
		col = d.rem;

		int base = (int)fabs((double)nHeight * (1.0 - (double)(2*col) / (double)nWidth));
		lpdLayers[i] = (row > base - 10 && row < base  + 10) ? 0.0 : 1.0;
	}
}

void RandBmpGenerator::step(double step) {
    double *pTemp = lpdOldLayers;
    lpdOldLayers = lpdLayers;
    lpdLayers = pTemp;

    double dA[7];
    double dRes;
    div_t d;

    double dSum = 0.0;

    int layerSize = nWidth * nHeight;
    int lenght = layerSize * N_LAYERS;
    for (int i=0; i<lenght; i++) {
        dA[0] = lpdOldLayers[i];
        d = div(i,nWidth);
        dA[1] = lpdOldLayers[ (((d.quot%nHeight == 0) ? nHeight : d.quot)-1) * nWidth + d.rem ];
        dA[2] = lpdOldLayers[ ((d.quot%nHeight == nHeight-1) ? 0 : d.quot+1) * nWidth + d.rem ];
        dA[3] = lpdOldLayers[ d.quot * nWidth + (((d.rem == 0) ? nWidth : d.rem)-1) ];
        dA[4] = lpdOldLayers[ d.quot * nWidth + ((d.rem == nWidth-1) ? 0 : d.rem+1) ];
        dA[5] = lpdOldLayers[ (i<layerSize) ? i+(N_LAYERS-1)*layerSize : i-layerSize ];
        dA[6] = lpdOldLayers[ (i>(N_LAYERS-1)*layerSize) ? i%layerSize : i+layerSize ];

        dRes = dA[0]*dA[0] + PARAM_ALPHA * (dA[1] + dA[2] + dA[3] + dA[4] - 4*dA[0])
            + PARAM_H * (dA[5] + dA[6] - 2*dA[0]);
		dRes = -dA[0] * (2 * PARAM_A * dRes * dRes - PARAM_A * fabs(dRes) + 1);
        lpdLayers[i] = dA[0] + step * dRes;

        dSum += lpdLayers[i];
    }
    dTime += step;
    dAverage = dSum / (double)lenght;
}
