#include "qwmainwindow.h"
#include "ui_qwmainwindow.h"

QWMainWindow::QWMainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::QWMainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setVisible(false);
    ui->tabWidget->clear();//清除所有页面
    ui->tabWidget->tabsClosable(); //Page有关闭按钮，可被关闭

    this->setCentralWidget(ui->tabWidget);

    // this->setWindowState(Qt::WindowFullScreen); //窗口最大化显示
    this->setWindowState(Qt::WindowMaximized); //窗口最大化显示
    // this->setWindowState(Qt::WindowMinimized); //窗口最大化显示
    this->setAutoFillBackground(true);

}

QWMainWindow::~QWMainWindow()
{
    delete ui;
}
//绘制窗口背景图片
void QWMainWindow::paintEvent(QPaintEvent* event)
{

    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(0, ui->mainToolBar->height(), this->width(), this->height() - ui->mainToolBar->height() - ui->statusBar->height(), QPixmap(":/images/images/back2.jpg"));
}


void QWMainWindow::on_actWidgetInsite_triggered()
{
    QFormDoc* formDoc = new QFormDoc(this);//指定父窗口
    formDoc->setAttribute(Qt::WA_DeleteOnClose);// 关闭时自动删除

    // formDoc->setWindowFlag(Qt::Widget, true);
    // formDoc->setWindowFlag(Qt::CustomizeWindowHint, true);//窗口标题
    // formDoc->setWindowFlag(Qt::WindowMinMaxButtonsHint,false);//最大最小化按钮

    // formDoc->setWindowState(Qt::WindowMaximized);
    // formDoc->setWindowOpacity(0.5);
    // formDoc->setWindowModality(Qt::WindowModal);

    // formDoc->show(); //在单独的窗口中显示
    // formDoc->setWindowTitle("基于QWidget的窗口，无父窗口，关闭时删除");

    int cur = ui->tabWidget->addTab(formDoc, QString::asprintf("Doc %d", ui->tabWidget->count()));

    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void QWMainWindow::on_actWidget_triggered()
{
    QFormDoc* formDoc = new QFormDoc(); //不指定父窗口，用show()显示
    formDoc->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    formDoc->setWindowTitle("基于QWidget的窗体，无父窗口，关闭时删除");

    formDoc->setWindowFlag(Qt::Window, true);

    // formDoc->setWindowFlag(Qt::CustomizeWindowHint,true);
    // formDoc->setWindowFlag(Qt::WindowMinMaxButtonsHint,true);
    // formDoc->setWindowFlag(Qt::WindowCloseButtonHint,true);
    // formDoc->setWindowFlag(Qt::WindowStaysOnTopHint,true);

    // formDoc->setWindowState(Qt::WindowMaximized);//最大化
    formDoc->setWindowOpacity(0.9);//透明度
    // formDoc->setWindowModality(Qt::WindowModal);

    formDoc->show(); //在单独的窗口中显示
}


void QWMainWindow::on_actWindowInsite_triggered()
{
    QFormTable* formTable = new QFormTable(this);
    formTable->setAttribute(Qt::WA_DeleteOnClose); //关闭时自动删除
    //    aTable->setWindowTitle("基于QWidget的窗口，无父窗口，关闭时删除");

    int cur = ui->tabWidget->addTab(formTable, QString::asprintf("Table %d", ui->tabWidget->count()));
    ui->tabWidget->setCurrentIndex(cur);
    ui->tabWidget->setVisible(true);
}


void QWMainWindow::on_actWindow_triggered()
{
    QFormTable* formTable = new QFormTable(this);
//    formChart = new QFormTable(); //无父窗体,在windows任务栏上有显示
    formTable->setAttribute(Qt::WA_DeleteOnClose); //对话框关闭时自动删除对话框对象,用于不需要读取返回值的对话框
    formTable->setWindowTitle("基于QMainWindow的窗口，指定父窗口，关闭时删除");
//    formChart->setWindowTitle("多实例窗口，指定父窗口");
    formTable->show();
}
//关闭Tab
void QWMainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (index < 0)
        return;

    QWidget* aForm = ui->tabWidget->widget(index);
    aForm->close();
}

void QWMainWindow::on_tabWidget_currentChanged(int index)
{
    Q_UNUSED(index);
    bool  en = ui->tabWidget->count() > 0; //再无页面时，actions禁用
    ui->tabWidget->setVisible(en);
}

