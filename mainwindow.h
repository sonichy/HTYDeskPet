#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QSettings>
#include <QPropertyAnimation>
#include <QTimer>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(int index READ getIndex WRITE setIndex)

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QPropertyAnimation *propertyAnimation;
    QList<QImage> list_image;
    int indexi = 0;
    int getIndex();
    void setIndex(int index);
    bool isMLBD = false;
    QPoint m_point;
    QSettings settings;
    QTimer *timer;
};

#endif // MAINWINDOW_H