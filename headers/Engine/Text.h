#ifndef TEXT_H
#define TEXT_H

#include <QFont>

namespace Entity {
class Text;
}

class Text
{
public:
    Text(QFont* pFont);

private:
    QFont* font;
};

#endif // TEXT_H
