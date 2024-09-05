#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPushButton>

MainWindow *MainWindow::_mainWindow = nullptr;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene   = new QGraphicsScene(this);
    scene->setSceneRect(0,0,400,300);

    container   = new QWidget;
    view        = new QGraphicsView(scene, this);
    btn         = new QPushButton("Draw", this);
    cli         = new QLineEdit(this);
    vbox        = new QVBoxLayout;
    logger      = new QTextEdit(this);

    logger->setReadOnly(true);
    logger->setFixedHeight(50);
    container->setLayout(vbox);
    setCentralWidget(container);

    vbox->addWidget(view);
    vbox->addWidget(logger);
    vbox->addWidget(cli);
    vbox->addWidget(btn);


    auto appendHandling = [log = logger, input = cli, tree = &ast]()
    {
        QString cmd = input->text();
        bool analyzer = tree->parser(cmd);
        QString clr = analyzer ? "green" : "red";
        QString appendText = analyzer ? "true" : "false";
        QString format = QString("<span style='color:%1;'>" "%2 - %3" "</span>").arg(clr, cmd, appendText);

        //logging cleaning command
        log->append(format);
        input->clear();
    };
    connect(btn, &QPushButton::clicked, appendHandling);
    connect(cli, &QLineEdit::returnPressed, appendHandling);
}

void MainWindow::resizeEvent(QResizeEvent *event)
 {

    QMainWindow::resizeEvent(event);

       int newWidth = this->size().width();
       int newHeight = this->size().height() - 50;

       scene->setSceneRect(0, 0, newWidth, newHeight);
       view->resize(newWidth, newHeight);
 }

MainWindow::~MainWindow()
{
    delete ui;
    delete btn;
    delete cli;
    delete scene;
    delete view;
    delete vbox;
    delete logger;
}


MainWindow *MainWindow::GetInstance(QWidget *parent)
{
    if(_mainWindow == nullptr)
        _mainWindow = new MainWindow(parent);

    return _mainWindow;
}
