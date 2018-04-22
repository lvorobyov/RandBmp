/**
 * rgb_draw_context.cpp
 *
 * Created on: 17.03.2018
 *     Author: Lev Vorobjev
 *      Email: lev.vorobjev@rambler.ru
 *
 * Copyright (C) 2018 Lev Vorobjev
 */

#include <rgb_draw_context.h>
#include <math.h>

void RgbDrawContext::draw(BmpGenerator* generator, LPBITMAP lpbm) {
    int nWidth = generator->getWidth();
    int nHeight = generator->getHeight();
    double* lpdLayers = generator->getData();
    double dAverage = generator->getAverage();
    int lenght = nWidth * nHeight;
    int nWidthBytes = lpbm->bmWidthBytes;
    int nBitsPixel = lpbm->bmBitsPixel;
    int white = (nWidthBytes * 8) - nWidth * nBitsPixel;
    div_t d;
    int row, col;
    WORD word = 0;
    for (int i=0; i<lenght; i++) {
        d = div(i, nWidth);
        row = d.quot;
        col = d.rem;
        d = div(col, 16/nBitsPixel);
        word <<= 1;
        if (lpdLayers[i] > dAverage) {
            word |= 1;
        }
        if (d.rem == 1) {
            ((LPWORD)lpbm->bmBits)[row * nWidthBytes/2 + d.quot] = word;
        } else if (col == nWidth-1) {
            ((LPWORD)lpbm->bmBits)[row * nWidthBytes/2 + d.quot] = (word << white);
        }
    }
}
