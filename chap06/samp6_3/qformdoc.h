#ifndef QFORMDOC_H
#define QFORMDOC_H

#include <QWidget>

#include    <QToolBar>
#include    <QVBoxLayout>
#include    <QFileDialog>
#include    <QFile>
#include    <QTextStream>
#include    <QFontDialog>
#include    <QFileInfo>
#include    <QMessageBox>
#include    <qwmainwindow.h>

namespace Ui
{
    class QFormDoc;
}

class QFormDoc : public QWidget
{
    Q_OBJECT

private:
    QString mCurrentFile; //当前文件

public:
    explicit QFormDoc(QWidget* parent = 0);
    ~QFormDoc();

    void    loadFromFile(QString& aFileName);

private slots:
    void on_actOpen_triggered();

    void on_actFont_triggered();

private:
    Ui::QFormDoc* ui;
};

#endif // QFORMDOC_H
