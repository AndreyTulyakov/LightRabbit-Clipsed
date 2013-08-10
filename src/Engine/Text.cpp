#include "headers/Engine/Text.h"

using namespace Entity;

Text::Text(QFont *pFont)
{
    initializeGLFunctions();
    font = pFont;
}

Text::Text()
{
    initializeGLFunctions();
    font = nullptr;
}

void Text::update()
{

}

void Text::draw()
{

}
