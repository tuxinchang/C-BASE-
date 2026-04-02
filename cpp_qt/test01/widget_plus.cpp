#include "widget_plus.h"
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QFormLayout>
/**
 * @brief Widget 构造函数
 * @param parent 父窗口指针
 * 
 * 功能：创建一个简单的登录界面，包含用户名输入、密码输入和登录按钮
 */

Widget_plus::Widget_plus(QWidget *parent): QWidget(parent)
{
    // 创建用户名标签
    label1 = new QLabel("用户名");
    
    // 创建密码标签
    label2 = new QLabel("密码");
    
    // 创建用户名输入框
    lineEdit1 = new QLineEdit();
    
    // 创建密码输入框
    lineEdit2 = new QLineEdit();
    
    // 设置密码输入框为密码模式（显示为***）
    lineEdit2->setEchoMode(QLineEdit::Password);
    
    // 创建登录按钮
    button = new QPushButton("登录账号");
    

    // 连接登录按钮点击信号到槽函数 on_login_clicked
    connect(button, SIGNAL(clicked()), this,SLOT(login_clicked()));    
    //boxLayout();  // 盒式布局
    //formLayout();//表格布局
    gridLayout();//网格布局
}
/**
 * @brief 网格布局设置函数
 * 
 * 功能：使用网格布局（QGridLayout）创建登录界面的布局结构
 * 
 * 布局结构：
 * - 使用 QGridLayout 作为主布局
 * - 创建一个 3 行 2 列的网格
 *   1. 第 0 行：用户名标签（第 0 列）和用户名输入框（第 1 列）
 *   2. 第 1 行：密码标签（第 0 列）和密码输入框（第 1 列）
 *   3. 第 2 行：登录按钮（第 1 列，第 0 列留空）
 * 
 * 布局特点：
 * - 网格布局通过行和列的坐标精确定位组件
 * - 组件排列整齐，对齐效果好
 * - 适合需要精确控制组件位置的界面
 */
void Widget_plus::gridLayout(){
    // 创建网格布局对象
    QGridLayout *gridlayout = new QGridLayout;

    // 将用户名标签放在第 0 行第 0 列
    gridlayout->addWidget(label1, 0, 0); 
    
    // 将用户名输入框放在第 0 行第 1 列
    gridlayout->addWidget(lineEdit1, 0, 1); 
    
    // 将密码标签放在第 1 行第 0 列
    gridlayout->addWidget(label2, 1, 0); 
    
    // 将密码输入框放在第 1 行第 1 列
    gridlayout->addWidget(lineEdit2, 1, 1); 
    
    // 将登录按钮放在第 2 行第 1 列（第 0 列留空）
    gridlayout->addWidget(button, 2, 1); 
    
    // 设置网格布局的对齐方式为左对齐
    gridlayout->setAlignment(Qt::AlignLeft);
    
    // 设置当前窗口的布局为创建的网格布局
    this->setLayout(gridlayout);
}
/**
 * @brief 表单布局设置函数
 * 
 * 功能：使用表单布局（QFormLayout）创建登录界面的布局结构
 * 
 * 布局结构：
 * - 使用 QFormLayout 作为主布局
 * - 添加三行：
 *   1. 第一行：用户名标签和输入框
 *   2. 第二行：密码标签和输入框
 *   3. 第三行：登录按钮
 * 
 * 布局特点：
 * - 表单布局会自动对齐标签和输入框
 * - 标签默认右对齐，输入框左对齐
 * - 整体布局简洁整齐，适合表单类界面
 */
void Widget_plus::formLayout()
{
    // 创建表单布局对象
    QFormLayout *formlayout = new QFormLayout;
    
    // 添加第一行：用户名标签和输入框
    formlayout->addRow(label1, lineEdit1);
    
    // 添加第二行：密码标签和输入框
    formlayout->addRow(label2, lineEdit2);
    
    // 添加第三行：登录按钮
    formlayout->addRow(button);
    
    // 设置表单布局的对齐方式为左对齐
    formlayout->setAlignment(Qt::AlignLeft);
    
    // 设置当前窗口的布局为创建的表单布局
    this->setLayout(formlayout);
}
/**
 * @brief 盒式布局设置函数
 * 
 * 功能：使用盒式布局（Box Layout）创建登录界面的布局结构
 * 
 * 布局结构：
 * - 主布局：垂直布局（QVBoxLayout）
 * - 子布局：三个水平布局（QHBoxLayout）
 *   1. 第一个水平布局：包含用户名标签和输入框
 *   2. 第二个水平布局：包含密码标签和输入框
 *   3. 第三个水平布局：包含登录按钮
 * 
 * 布局效果：
 * - 界面从上到下依次显示：
 *   1. 用户名标签和输入框（水平排列）
 *   2. 密码标签和输入框（水平排列）
 *   3. 登录按钮（水平排列）
 */
void Widget_plus::boxLayout()
{
    // 创建第一个水平布局，用于放置用户名标签和输入框
    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addWidget(label1);     // 添加用户名标签
    layout1->addWidget(lineEdit1);   // 添加用户名输入框
    
    // 创建第二个水平布局，用于放置密码标签和输入框
    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addWidget(label2);     // 添加密码标签
    layout2->addWidget(lineEdit2);   // 添加密码输入框  
    
    // 创建第三个水平布局，用于放置登录按钮
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addWidget(button);      // 添加登录按钮
    
    // 创建垂直布局作为主布局
    QVBoxLayout *mainLayout = new QVBoxLayout();
    
    // 将三个水平布局按顺序添加到垂直布局中
    mainLayout->addLayout(layout1);  // 添加用户名布局
    mainLayout->addLayout(layout2);  // 添加密码布局
    mainLayout->addLayout(layout3);  // 添加登录按钮布局
    
    // 设置当前窗口的布局为创建的垂直布局
    this->setLayout(mainLayout);
}
// 登录按钮点击槽函数,一定要在同名头文件的public slots中声明
void Widget_plus::login_clicked()
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