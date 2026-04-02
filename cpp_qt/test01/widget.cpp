#include "widget.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
/**
 * @brief Widget 构造函数
 * @param parent 父窗口指针
 * 
 * 功能：创建一个简单的登录界面，包含用户名输入、密码输入和登录按钮
 */
QLineEdit *lineEdit1;
    
QLineEdit *lineEdit2;
Widget::Widget(QWidget *parent): QWidget(parent)
{
    // 创建用户名标签
    QLabel *label1 = new QLabel("用户名");
    
    // 创建密码标签
    QLabel *label2 = new QLabel("密码");
    
    // 创建用户名输入框
    lineEdit1 = new QLineEdit();
    
    // 创建密码输入框
    lineEdit2 = new QLineEdit();
    
    // 设置密码输入框为密码模式（显示为***）
    lineEdit2->setEchoMode(QLineEdit::Password);
    
    // 创建登录按钮
    QPushButton *button = new QPushButton("登录");
    
    // 创建垂直布局作为主布局
    QVBoxLayout *layout = new QVBoxLayout();

    // 连接登录按钮点击信号到槽函数 on_login_clicked
    connect(button, SIGNAL(clicked()), this,SLOT(login_clicked()));    
    
    // 创建用户名水平布局（标签+输入框）
    QHBoxLayout *hLayout1 = new QHBoxLayout();
    hLayout1->addWidget(label1);
    hLayout1->addWidget(lineEdit1);

    QHBoxLayout *hLayout2 = new QHBoxLayout();
    hLayout2->addWidget(label2);
    hLayout2->addWidget(lineEdit2);

    QHBoxLayout *hLayout3 = new QHBoxLayout();
    hLayout3->addWidget(button);
    
    // 向布局中添加组件，按垂直顺序排列
    layout->addLayout(hLayout1);     // 添加用户名标签
    layout->addLayout(hLayout2);   // 添加用户名输入框
    layout->addLayout(hLayout3);     // 添加密码标签


    // 设置当前窗口的布局为创建的垂直布局
    this->setLayout(layout);
}
// 登录按钮点击槽函数,一定要在同名头文件的public slots中声明
void Widget::login_clicked()
{
    // 当登录按钮被点击时，输出提示信息
    qDebug("登录按钮被点击了");
    QString username = lineEdit1->text();
    QString password = lineEdit2->text();
    if(username == "admin" && password == "123456")
    {
        qDebug()<<"登录成功";
    }
    else
    {
        qDebug()<<"登录失败";
    }

}