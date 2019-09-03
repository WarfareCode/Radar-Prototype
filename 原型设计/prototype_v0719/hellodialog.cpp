#include "hellodialog.h"
#include "ui_hellodialog.h"
#include "mainwindownew.h"
/**
* @projectName   prototype_v0719
* @brief         开始欢迎页面，也即是进入主程序之前的拦截界面。可以选择打开或者新建工程。
* @author        Antrn
* @date          2019-08-12
*/
HelloDialog::HelloDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelloDialog)
{
    ui->setupUi(this);
    //去掉页面边框和标题栏
    this->setWindowFlag(Qt::FramelessWindowHint);
    //标题栏保留，去掉大小按钮
//    this->setWindowFlag(Qt::WindowMinimizeButtonHint, false);
//    this->setWindowFlag(Qt::WindowMaximizeButtonHint, false);
//    去除所有按钮
//    this->setWindowFlags(Qt::WindowTitleHint|Qt::CustomizeWindowHint);
    //只剩关闭按钮
//    this->setWindowFlag(Qt::WindowCloseButtonHint);

    ui->pushButton_open->setStyleSheet(
                //正常状态样式
                "QPushButton{"
                     "background-color:rgba(211, 215, 207, 30);"//背景色（也可以设置图片）
                     "border-style:outset;"                  //边框样式（inset/outset）
                     "border-width:1px;"                     //边框宽度像素
                     "border-radius:5px;"                   //边框圆角半径像素
                     "border-color:rgba(0,0,0,30);"    //边框颜色
                 "}"
                 //鼠标按下样式

                 "QPushButton:pressed{"
                     "background-color:rgba(100,255,100,200);"
                     "border-color:rgba(255,255,255,200);"
                     "border-style:inset;"
                 "}"

                 //鼠标悬停样式
                 "QPushButton:hover{"
                 "background-color:rgba(255,255,255,100);"
                 "border-color:rgba(30,30,30,80);"
                 "}"
     );
    ui->pushButton_new->setStyleSheet(
                //正常状态样式
                "QPushButton{"
                     "background-color:rgba(211, 215, 207, 30);"//背景色（也可以设置图片）
                     "border-style:outset;"                  //边框样式（inset/outset）
                     "border-width:1px;"                     //边框宽度像素
                     "border-radius:5px;"                   //边框圆角半径像素
                     "border-color:rgba(0,0,0,30);"    //边框颜色
                 "}"
                 //鼠标按下样式
                 "QPushButton:pressed{"
                     "background-color:rgba(100,255,100,200);"
                     "border-color:rgba(255,255,255,200);"
                     "border-style:inset;"
                 "}"

                 //鼠标悬停样式
                 "QPushButton:hover{"
                 "background-color:rgba(255,255,255,80);"
                 "border-color:rgba(30,30,30,100);"
                 "}"
     );

}

HelloDialog::~HelloDialog()
{
    delete ui;
}


void HelloDialog::on_pushButton_open_clicked()
{
    this->main = new MainWindow();
    this->main->show();
    this->close();
}

void HelloDialog::on_pushButton_new_clicked()
{
    MainWindowNew* mainnew = new MainWindowNew;
    mainnew->show();
    this->close();
}
