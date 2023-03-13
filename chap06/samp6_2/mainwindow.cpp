#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    theModel = new QStandardItemModel(10, 5, this); //创建数据模型
    theSelection = new QItemSelectionModel(theModel);//Item选择模型


    //为tableView设置数据模型
    ui->tableView->setModel(theModel); //设置数据模型
    ui->tableView->setSelectionModel(theSelection);//设置选择模型

    setCentralWidget(ui->tableView); //

    //创建状态栏组件
    LabCellPos = new QLabel("当前单元格：", this);
    LabCellPos->setMinimumWidth(180);
    LabCellPos->setAlignment(Qt::AlignHCenter);

    LabCellText = new QLabel("单元格内容：", this);
    LabCellText->setMinimumWidth(200);


    ui->statusBar->addWidget(LabCellPos);
    ui->statusBar->addWidget(LabCellText);

    // connect(theSelection, SIGNAL(currentChanged(QModelIndex, QModelIndex)), this, SLOT(on_currentChanged(QModelIndex, QModelIndex)));

}

MainWindow::~MainWindow()
{
    delete ui;
}
//定位到单元格，并设置字符串
void MainWindow::setAccellText(int row, int col, QString text)
{

    QModelIndex index = theModel->index(row, col); //获取模型索引
    theSelection->clearSelection(); //清除现有选择
    theSelection->setCurrentIndex(index, QItemSelectionModel::Select); //定位到单元格
    theModel->setData(index, text, Qt::DisplayRole); //设置单元格字符串
}

void MainWindow::setActLocateEnable(bool enable)
{
    ui->actTab_Locate->setEnabled(enable);
}
void MainWindow::setDlgLocateNull()
{
    dlgLocate = NULL;
}


//模态对话框，动态创建，用过后删除
void MainWindow::on_actTab_SetSize_triggered()
{
    QWDialogSize*    dlgTableSize = new QWDialogSize(this); //创建对话框
    //   dlgTableSize->setAttribute(Qt::WA_DeleteOnClose);
    //对话框关闭时自动删除对话框对象,用于不需要读取返回值的对话框
    //如果需要获取对话框的返回值，不能设置该属性，可以在调用完对话框后删除对话框
    Qt::WindowFlags    flags = dlgTableSize->windowFlags();
    dlgTableSize->setWindowFlags(flags | Qt::MSWindowsFixedSizeDialogHint); //设置对话框固定大小

    dlgTableSize->setRowColumn(theModel->rowCount(), theModel->columnCount()); //对话框数据初始化
    //qDebug() << dlgTableSize->rowCount() << "\t" << dlgTableSize->columnCount();
    int ret = dlgTableSize->exec(); // 以模态方式显示对话框，用户关闭对话框时返回 DialogCode值
    if (ret == QDialog::Accepted) //OK键被按下,对话框关闭，若设置了setAttribute(Qt::WA_DeleteOnClose)，对话框被释放，无法获得返回值
    {
        //OK键被按下，获取对话框上的输入，设置行数和列数
        int cols = dlgTableSize->columnCount();
        theModel->setColumnCount(cols);

        int rows = dlgTableSize->rowCount();
        theModel->setRowCount(rows);
    }
    delete dlgTableSize; //删除对话框

}

//一次创建，多次调用，对话框关闭时只是隐藏
void MainWindow::on_actTab_SetHeader_triggered()
{
    if (dlgSetHeaders == NULL) //如果对象没有被创建过，就创建对象
        dlgSetHeaders = new QWDialogHeaders(this);

    if (dlgSetHeaders->headerList().count() != theModel->columnCount())
    {
        //只需在创建时传递参数给对话框,由于对话框只是隐藏，界面内容保存
        QStringList strList;
        for (int i = 0; i < theModel->columnCount(); i++) //获取现有的表头标题
            strList.append(theModel->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString());
        dlgSetHeaders->setHeaderList(strList);//用于对话框初始化显示
    }

    int ret = dlgSetHeaders->exec(); // 以模态方式显示对话框
    if (ret == QDialog::Accepted) //OK键被按下
    {
        QStringList strList = dlgSetHeaders->headerList(); //获取对话框上修改后的StringList
        theModel->setHorizontalHeaderLabels(strList);// 设置模型的表头标题
    }
}

// 创建 StayOnTop的对话框，对话框关闭时自动删除
void MainWindow::on_actTab_Locate_triggered()
{
    //通过控制actTab_Locate的enable属性避免重复点击
    //ui->actTab_Locate->setEnabled(false);
    dlgLocate = new QWDialogLocate(this);
    dlgLocate->setAttribute(Qt::WA_DeleteOnClose);//对话框关闭时自动删除
    Qt::WindowFlags    flags = dlgLocate->windowFlags(); //获取已有flags
    dlgLocate->setWindowFlags(flags | Qt::WindowStaysOnTopHint); //设置对话框固定大小,StayOnTop
    //对话框初始化设置
    dlgLocate->setSpinRange(theModel->rowCount(), theModel->columnCount());
    QModelIndex curIndex = theSelection->currentIndex();
    if (curIndex.isValid())
        dlgLocate->setSpinValue(curIndex.row(), curIndex.column());

    dlgLocate->show(); //非模态显示对话框
}




//单击单元格时，将单元格的行号、列号设置到对话框上
void MainWindow::on_tableView_clicked(const QModelIndex& index)
{
    if(dlgLocate != NULL)
    {
        dlgLocate->setSpinValue(index.row(), index.column());
    }
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    QMessageBox::StandardButton result = QMessageBox::question(this, "确认", "确定要退出吗?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel, QMessageBox::No);
    if(result == QMessageBox::Yes)
    {
        event->accept();
    }
    else
    {
        event->ignore();
    }
}

