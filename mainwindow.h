#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/dnn.hpp>
#include "logtextedit.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /**
     * 初始化
     */
    void init();
    /**
     * 选择文件
     */
    void selectFile();
    /**
     * 开始检测
     */
    void startDetect();

private:
    Ui::MainWindow *ui;
    QImage srcImage;
    LogTextEdit* logView;

};
#endif // MAINWINDOW_H
