/**
 * @Author: Lev Vorobjev
 * @Date:   17.04.2018
 * @Email:  lev.vorobjev@rambler.ru
 * @Filename: bmp_generator.cpp
 * @Last modified by:   Lev Vorobjev
 * @Last modified time: 22.04.2018
 * @License: MIT
 * @Copyright: Copyright (c) 2018 Lev Vorobjev
 */

#include "bmp_generator.h"

#include <stdlib.h>

BmpGenerator::BmpGenerator(int nWidth, int nHeight) {
    this -> nWidth = nWidth;
    this -> nHeight = nHeight;
    dTime = 0.0;
    dAverage = 0.5;
    lpdLayers = (double*)calloc(nWidth*nHeight*N_LAYERS, sizeof(double));
    lpdOldLayers = (double*)calloc(nWidth*nHeight*N_LAYERS, sizeof(double));
}

BmpGenerator::~BmpGenerator() {
    free(lpdLayers);
    free(lpdOldLayers);
}

int BmpGenerator::getWidth() const {
    return nWidth;
}

int BmpGenerator::getHeight() const {
    return nHeight;
}

double* BmpGenerator::getData() {
    return lpdLayers;
}

double BmpGenerator::getAverage() {
    return dAverage;
}
