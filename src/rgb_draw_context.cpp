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

void RgbDrawContext::draw(BmpGenerator* generator, LPBITMAP lpbm) {
    int layer = 1;
    int nWidth = generator->getWidth();
    int nHeight = generator->getHeight();
    double* lpdLayers = generator->getData();
    int lenght = nWidth * nHeight;
    int nWidthBytes = lpbm->bmWidthBytes;
    int white = (nWidthBytes * 8) - nWidth * lpbm->bmBitsPixel;
    div_t d;
    int row, col;
    WORD word = 0;
    for (int i=layer*lenght; i<(layer+1)*lenght; i++) {
        d = div(i, nWidth);
        row = d.quot % nHeight;
        d = div(col = d.rem, 16);
        word <<= 1;
        if (lpdLayers[i] > 0.5) {
            word |= 1;
        }
        if (d.rem == 15) {
            ((LPWORD)lpbm->bmBits)[row * nWidthBytes/2 + d.quot] = word;
        } else if (col == nWidth-1) {
            ((LPWORD)lpbm->bmBits)[row * nWidthBytes/2 + d.quot] = (word << white);
        }
    }
}
