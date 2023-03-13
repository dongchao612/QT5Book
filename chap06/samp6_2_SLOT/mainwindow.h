#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QDebug>
#include <QMainWindow>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QCloseEvent>
#include "qwdialogsize.h"
#include "qwdialogheaders.h"
#include "qwdialoglocate.h"

class   QWDialogLocate;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    void setDlgLocateNull();
    void closeEvent(QCloseEvent* event);//关闭窗口时间，可以询问是否退出
public slots:
    void setACellText(int row, int col, QString& text);//设置一个单元格的内容
    void setActLocateEnable(bool enable);//设置actTab_Locate的enabled属性

signals:
    void    cellIndexChanged(int rowNo, int colNo);//当前单元格发生变化
private slots:
    void on_actTab_SetSize_triggered();
    void on_actTab_SetHeader_triggered();
    void on_actTab_Locate_triggered();
    void on_tableView_clicked(const QModelIndex& index);

private:
    Ui::MainWindow* ui;
    //用于状态栏的信息显示
    QLabel*  LabCellPos;    //当前单元格行列号
    QLabel*  LabCellText;   //当前单元格内容

    QStandardItemModel*  theModel;//数据模型
    QItemSelectionModel* theSelection;//Item选择模型

    QWDialogHeaders* dlgSetHeaders = NULL; //设置表头文字对话框, 一次创建，exec()重复调用
    QWDialogLocate*  dlgLocate;

};
#endif // MAINWINDOW_H
