#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow *MainWindow::_mainWindow = nullptr;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene       = new QGraphicsScene(this);
    view        = new QGraphicsView(scene, this);
    container   = new QWidget(this);
    cli         = new QLineEdit(this);
    btn         = new QPushButton("Draw", this);
    saveBtn     = new QPushButton("Save Logs", this);
    logger      = new QTextEdit(this);
    vbox        = new QVBoxLayout;

    scene->setSceneRect(0,0,400,300);

    logger->setReadOnly(true);
    logger->setFixedHeight(50);

    container->setLayout(vbox);
    setCentralWidget(container);

    vbox->addWidget(view);
    vbox->addWidget(logger);
    vbox->addWidget(cli);
    vbox->addWidget(btn);
    vbox->addWidget(saveBtn);

    btn->setEnabled(false);

    auto appendHandling = [this]()
    {
        QString cmd = cli->text();
        bool analyzer = ast.parser(cmd);
        QString clr = analyzer ? "green" : "red";
        QString appendText = analyzer ? "true" : "false";
        QString format = QString("<span style='color:%1;'>" "%2 - %3" "</span>").arg(clr, cmd, appendText);
        logger->append(format);

        if (analyzer)
        {
            auto data = ast.getShapeData();
            std::unique_ptr<Factory> factory(getFactory(data.shape));
            if (factory)
            {
                std::unique_ptr<Shape>  shape(factory->create(data));
                shape->draw(scene);
            }
            else
                logger->append("<span style='color:red;'>" "Unknown error - false" "</span>");
        }
        cli->clear();
    };

    connect(btn, &QPushButton::clicked, appendHandling);
    connect(cli, &QLineEdit::returnPressed, appendHandling);
    connect(cli, &QLineEdit::textChanged, this, [=](){
        btn->setEnabled(!cli->text().isEmpty());
    });
    connect(saveBtn, &QPushButton::clicked, this, [=](){
        QString fileName = QFileDialog::getSaveFileName(this, "Save Log File", "", "Log Files (*.log)");
        if (!fileName.isEmpty())
        {
            QFile file(fileName);
            if (file.open(QIODevice::WriteOnly | QIODevice::Text))
            {
                QTextStream out(&file);
                out << logger->toPlainText();
                file.close();
            }
        }
    });
}


Factory *MainWindow::getFactory(const std::string shapeType)
{
    if (shapeType == "line")
        return new FactoryLine();
    else if (shapeType == "rectangle")
        return new FactoryRect();
    else if (shapeType == "triangle")
        return new FactoryTriangle();
    return (nullptr);
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
    delete saveBtn;
}


MainWindow *MainWindow::GetInstance(QWidget *parent)
{
    if(_mainWindow == nullptr)
        _mainWindow = new MainWindow(parent);

    return _mainWindow;
}
