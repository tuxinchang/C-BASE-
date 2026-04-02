#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>  
#include <QToolBar>
#include <QAction>
#include <QStatusBar> 


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 动态创建一个新的工具栏
    QToolBar *toolBar = new QToolBar("工具", this);
    this->addToolBar(toolBar);
    QStatusBar *statusBar = new QStatusBar(this);
    statusBar->showMessage("状态栏");
    this->setStatusBar(statusBar);
    // 动态创建一个新的按钮
    QPushButton *pushButton1= new QPushButton("点击1");
    toolBar->addWidget(pushButton1);
    QPushButton *pushButton2 = new QPushButton("点击2");
    pushButton2->setMinimumSize(60, 20); // 设置按钮最小尺寸
    statusBar->addPermanentWidget(pushButton2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

