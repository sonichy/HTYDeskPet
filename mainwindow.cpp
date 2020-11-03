#include "mainwindow.h"
#include <QPainter>
#include <QApplication>
#include <QDesktopWidget>
#include <QAction>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    settings(QApplication::organizationName(), QApplication::applicationName())
{
    setFixedSize(200,200);
    setAttribute(Qt::WA_TranslucentBackground, true);
    setWindowFlags(Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint);

    QString sx =  settings.value("X").toString();
    QString sy =  settings.value("Y").toString();
    if (sx == "" || sy == "" || sx.toInt() > QApplication::desktop()->width() || sy.toInt() > QApplication::desktop()->height()) {
        move(QApplication::desktop()->width() - width(), QApplication::desktop()->height() - height());
    } else {
        move(sx.toInt(), sy.toInt());
    }

    QAction *action_quit = new QAction("&Quit", this);
    connect(action_quit, SIGNAL(triggered(bool)), this, SLOT(close()));
    addAction(action_quit);
    setContextMenuPolicy(Qt::ActionsContextMenu);

    list_image.append(QImage(":/1.png"));
    list_image.append(QImage(":/2.png"));
    list_image.append(QImage(":/3.png"));

    propertyAnimation = new QPropertyAnimation(this, "index");
    propertyAnimation->setDuration(1000);
    //propertyAnimation->setLoopCount(-1);
    propertyAnimation->setStartValue(0);
    propertyAnimation->setEndValue(2);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]{
        propertyAnimation->start();
    });
    timer->start(60000);
}

MainWindow::~MainWindow()
{

}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawImage(rect(), list_image.at(getIndex()));
}

int MainWindow::getIndex()
{
    qDebug() << indexi;
    return indexi;
}

void MainWindow::setIndex(int index)
{
    indexi = index;
    update();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        isMLBD = true;
        m_point = event->pos();
        propertyAnimation->start();
        timer->start(60000);
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (isMLBD) {
        setCursor(Qt::ClosedHandCursor);
        move(event->pos() - m_point + pos());
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    isMLBD = false;
    setCursor(Qt::ArrowCursor);
    settings.setValue("X", x());
    settings.setValue("Y", y());
}