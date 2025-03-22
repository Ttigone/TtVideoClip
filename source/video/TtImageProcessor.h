#ifndef TTIMAGEPROCESSOR_H
#define TTIMAGEPROCESSOR_H

#include <QObject>

class TtImageProcessor : public QObject
{
    Q_OBJECT
public:
    explicit TtImageProcessor(QObject* parent = nullptr);
};

#endif // TTIMAGEPROCESSOR_H
