/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton;
    QRadioButton *radioButton_3;
    QPushButton *btn_file;
    QPushButton *btn_detect;
    QPushButton *btn_exit;
    QFrame *line;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QWidget *widget_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_source;
    QLabel *label_2;
    QWidget *widget_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_detect;
    QWidget *widget_6;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QWidget *widget_7;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *layout_log;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1000, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: rgb(46, 54, 64);\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 5px;"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 60));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_3 = new QLabel(widget);
        label_3->setObjectName("label_3");
        QFont font;
        font.setPointSize(16);
        font.setBold(true);
        label_3->setFont(font);

        horizontalLayout_2->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        radioButton_2 = new QRadioButton(widget);
        radioButton_2->setObjectName("radioButton_2");
        QFont font1;
        font1.setPointSize(10);
        radioButton_2->setFont(font1);

        horizontalLayout_2->addWidget(radioButton_2);

        radioButton = new QRadioButton(widget);
        radioButton->setObjectName("radioButton");
        radioButton->setFont(font1);

        horizontalLayout_2->addWidget(radioButton);

        radioButton_3 = new QRadioButton(widget);
        radioButton_3->setObjectName("radioButton_3");
        radioButton_3->setFont(font1);

        horizontalLayout_2->addWidget(radioButton_3);

        btn_file = new QPushButton(widget);
        btn_file->setObjectName("btn_file");
        btn_file->setMinimumSize(QSize(80, 40));
        QFont font2;
        font2.setPointSize(9);
        btn_file->setFont(font2);
        btn_file->setStyleSheet(QString::fromUtf8("background-color: rgb(45, 171, 64);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(btn_file);

        btn_detect = new QPushButton(widget);
        btn_detect->setObjectName("btn_detect");
        btn_detect->setMinimumSize(QSize(80, 40));
        btn_detect->setFont(font2);
        btn_detect->setStyleSheet(QString::fromUtf8("background-color: rgb(45, 171, 64);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(btn_detect);

        btn_exit = new QPushButton(widget);
        btn_exit->setObjectName("btn_exit");
        btn_exit->setMinimumSize(QSize(80, 40));
        btn_exit->setFont(font2);
        btn_exit->setStyleSheet(QString::fromUtf8("background-color: rgb(45, 171, 64);\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(btn_exit);


        verticalLayout->addWidget(widget);

        line = new QFrame(centralwidget);
        line->setObjectName("line");
        line->setMaximumSize(QSize(16777215, 1));
        line->setStyleSheet(QString::fromUtf8("background-color: rgb(229, 229, 229);\n"
"background-color: rgba(255, 255, 255, 30);"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        widget_2 = new QWidget(centralwidget);
        widget_2->setObjectName("widget_2");
        horizontalLayout = new QHBoxLayout(widget_2);
        horizontalLayout->setObjectName("horizontalLayout");
        widget_3 = new QWidget(widget_2);
        widget_3->setObjectName("widget_3");
        verticalLayout_2 = new QVBoxLayout(widget_3);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(widget_3);
        label->setObjectName("label");
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setFont(font1);

        verticalLayout_2->addWidget(label);

        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName("widget_4");
        widget_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(200, 200, 200);"));
        horizontalLayout_3 = new QHBoxLayout(widget_4);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_source = new QLabel(widget_4);
        label_source->setObjectName("label_source");

        horizontalLayout_3->addWidget(label_source);


        verticalLayout_2->addWidget(widget_4);

        label_2 = new QLabel(widget_3);
        label_2->setObjectName("label_2");
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setFont(font1);

        verticalLayout_2->addWidget(label_2);

        widget_5 = new QWidget(widget_3);
        widget_5->setObjectName("widget_5");
        widget_5->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 200, 200);"));
        horizontalLayout_4 = new QHBoxLayout(widget_5);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_detect = new QLabel(widget_5);
        label_detect->setObjectName("label_detect");

        horizontalLayout_4->addWidget(label_detect);


        verticalLayout_2->addWidget(widget_5);


        horizontalLayout->addWidget(widget_3);

        widget_6 = new QWidget(widget_2);
        widget_6->setObjectName("widget_6");
        widget_6->setMaximumSize(QSize(400, 16777215));
        verticalLayout_3 = new QVBoxLayout(widget_6);
        verticalLayout_3->setObjectName("verticalLayout_3");
        label_4 = new QLabel(widget_6);
        label_4->setObjectName("label_4");
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setFont(font1);

        verticalLayout_3->addWidget(label_4);

        widget_7 = new QWidget(widget_6);
        widget_7->setObjectName("widget_7");
        widget_7->setStyleSheet(QString::fromUtf8("background-color: rgb(200, 200, 200);"));
        verticalLayout_4 = new QVBoxLayout(widget_7);
        verticalLayout_4->setObjectName("verticalLayout_4");
        layout_log = new QVBoxLayout();
        layout_log->setObjectName("layout_log");

        verticalLayout_4->addLayout(layout_log);


        verticalLayout_3->addWidget(widget_7);


        horizontalLayout->addWidget(widget_6);


        verticalLayout->addWidget(widget_2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\346\234\272\345\231\250\350\247\206\350\247\211\345\255\246\344\271\240\350\275\246\347\211\214\346\243\200\346\265\213\347\263\273\347\273\237", nullptr));
        radioButton_2->setText(QCoreApplication::translate("MainWindow", "\345\233\276\347\211\207", nullptr));
        radioButton->setText(QCoreApplication::translate("MainWindow", "\345\275\225\345\203\217", nullptr));
        radioButton_3->setText(QCoreApplication::translate("MainWindow", "\346\221\204\345\203\217\345\244\264", nullptr));
        btn_file->setText(QCoreApplication::translate("MainWindow", "\344\270\212\344\274\240\346\226\207\344\273\266", nullptr));
        btn_detect->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\243\200\346\265\213", nullptr));
        btn_exit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\347\263\273\347\273\237", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\345\216\237\345\247\213\347\233\256\346\240\207", nullptr));
        label_source->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\243\200\346\265\213\347\233\256\346\240\207", nullptr));
        label_detect->setText(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227\350\256\260\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
