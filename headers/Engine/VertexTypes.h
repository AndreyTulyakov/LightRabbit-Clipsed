/*
 * Copyright (C) 2013 Andrey Tulyakov
 * @mail: mhyhre@gmail.com
 *
 * This work is licensed under a Creative Commons
 * Attribution-NonCommercial-NoDerivs 3.0 Unported License.
 * You may obtain a copy of the License at
 *
 *              http://creativecommons.org/licenses/by-nc-nd/3.0/legalcode
 *
 */

#ifndef VERTEXTYPES_H
#define VERTEXTYPES_H


struct Vertex2D {
    QVector2D position;
    QVector2D texCoord;
};

struct Vertex2DTextureColor {
    QVector2D position;
    QVector2D texCoord;
    QVector4D color;
};


struct Vertex2DSimple {
    QVector2D position;
};

#endif // VERTEXTYPES_H
