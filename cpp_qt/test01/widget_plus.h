#ifndef WIDGET_PLUS_H
#define WIDGET_PLUS_H


#include <QWidget>
#include <QLabel>      // 添加 QLabel 头文件
#include <QLineEdit>   // 添加 QLineEdit 头文件
#include <QPushButton> // 添加 QPushButton 头文件
/**
 * @class Widget_plus
 * @brief 登录界面类
 * 
 * 继承自 QWidget，实现了一个简单的登录界面，包含：
 * - 用户名输入框
 * - 密码输入框（带密码掩码）
 * - 登录按钮
 * - 登录验证功能
 */
class Widget_plus : public QWidget
{
    Q_OBJECT  // Qt 元对象系统宏，用于支持信号槽机制

public:
    /**
     * @brief 构造函数
     * @param parent 父窗口指针，默认为 nullptr
     * 
     * 初始化登录界面的所有组件和布局
     */
    Widget_plus(QWidget *parent = nullptr);

signals:
    // 此处可添加自定义信号

public slots:
    /**
     * @brief 登录按钮点击槽函数
     * 
     * 处理登录按钮点击事件，验证用户名和密码
     * - 获取输入的用户名和密码
     * - 与预设的用户名密码进行比对
     * - 输出登录结果
     */
    void login_clicked();
    
private:
    void boxLayout();
    void formLayout();
    void gridLayout();
    QLineEdit *lineEdit1;
    QLineEdit *lineEdit2;
    QLabel *label1;
    QLabel *label2;
    QPushButton *button;
};

#endif // WIDGET_PLUS_H
