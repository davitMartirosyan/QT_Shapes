#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPolygonItem>
#include <QResizeEvent>
#include <QString>
#include <QVector>
#include <QDebug>
#include <QTextEdit>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

#include "shape/Shape.h"
#include "parser/Parser.h"
#include "factory/Factory.h"
#include "factory/FactoryLine.h"
#include "factory/FactoryRect.h"
#include "factory/FactoryTriangle.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    static MainWindow *GetInstance(QWidget *parent = nullptr);
    ~MainWindow();

private:
    MainWindow(QWidget *parent = nullptr);
    Factory *getFactory(const std::string shapeType);

private:
    Ui::MainWindow  *ui;

private:
    int w;
    int h;
    double x;
    double y;

private:
    QPushButton     *btn;
    QPushButton     *saveBtn;
    QLineEdit       *cli;
    QGraphicsView   *view;
    QGraphicsScene  *scene;
    QVBoxLayout     *vbox;
    QHBoxLayout     *hbox;
    QWidget         *container;
    QTextEdit       *logger;

private:
    Parser          ast;

private:
    static MainWindow *_mainWindow;

protected:
    void resizeEvent(QResizeEvent *event);

private:
    Shape *shape;
};

#endif // MAINWINDOW_H
