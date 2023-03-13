#ifndef QWMAINWINDOW_H
#define QWMAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

/********************/
#include "qformdoc.h"
#include "qformtable.h"
/********************/
QT_BEGIN_NAMESPACE
namespace Ui
{
    class QWMainWindow;
}
QT_END_NAMESPACE

class QWMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QWMainWindow(QWidget* parent = nullptr);
    ~QWMainWindow();

    virtual void paintEvent(QPaintEvent* event);

private slots:
    void on_actWidgetInsite_triggered();

    void on_actWidget_triggered();

    void on_actWindowInsite_triggered();

    void on_actWindow_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_tabWidget_currentChanged(int index);

private:
    Ui::QWMainWindow* ui;
};
#endif // QWMAINWINDOW_H
