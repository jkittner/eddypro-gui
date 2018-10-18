#ifndef QMLWIDGET_H
#define QMLWIDGET_H

#include <QQuickWidget>

class QmlWidget : public QQuickWidget
{
    Q_OBJECT

public:
    QmlWidget(QUrl source, QWidget *parent = nullptr);
};

#endif // QMLWIDGET_H
