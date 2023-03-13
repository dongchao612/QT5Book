#include "qwmainwindow.h"

#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include "qdlgLogin.h"

#include    <QTextCodec>
int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    QWMainWindow w;

    QDlgLogin*   dlgLogin = new QDlgLogin; //创建对话框

    if (dlgLogin->exec() == QDialog::Accepted)
    {
        // delete dlgLogin;
        QWMainWindow w;
        w.show();
        return a.exec();
    }
    else
        return  0;
}
