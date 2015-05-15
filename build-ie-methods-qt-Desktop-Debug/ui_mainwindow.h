/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.2.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "formulaview.h"
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionCalculate_all_iterations;
    QAction *actionPrevIteration;
    QAction *actionNextStep;
    QAction *actionSave_graph;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_5;
    QComboBox *kernelType;
    QLabel *label_4;
    QComboBox *expectedSolution;
    QWidget *widget;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QDoubleSpinBox *lowerBoundInput;
    QLabel *label_2;
    QDoubleSpinBox *upperBoundInput;
    FormulaView *formulaWidget;
    QSpacerItem *verticalSpacer;
    QFrame *line_2;
    QGroupBox *groupBox;
    QWidget *widget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QSpinBox *gridStepsInput;
    QLabel *label_7;
    QDoubleSpinBox *input_RightPartError;
    QPushButton *btnStartSolving;
    QSpacerItem *verticalSpacer_2;
    QFrame *line;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget;
    QGridLayout *gridLayout_4;
    QLabel *label_6;
    QSpinBox *iterationsInOneStep;
    QFrame *frame_2;
    QVBoxLayout *verticalLayout_3;
    QCustomPlot *plotWidget;
    QWidget *widget_3;
    QHBoxLayout *horizontalLayout;
    QLabel *statusLabel;
    QSpacerItem *horizontalSpacer;
    QLabel *label_Status;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1150, 720);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionCalculate_all_iterations = new QAction(MainWindow);
        actionCalculate_all_iterations->setObjectName(QStringLiteral("actionCalculate_all_iterations"));
        QFont font;
        font.setPointSize(13);
        font.setBold(false);
        font.setItalic(false);
        font.setUnderline(false);
        font.setWeight(50);
        font.setStrikeOut(false);
        actionCalculate_all_iterations->setFont(font);
        actionPrevIteration = new QAction(MainWindow);
        actionPrevIteration->setObjectName(QStringLiteral("actionPrevIteration"));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        actionPrevIteration->setFont(font1);
        actionNextStep = new QAction(MainWindow);
        actionNextStep->setObjectName(QStringLiteral("actionNextStep"));
        actionNextStep->setFont(font1);
        actionSave_graph = new QAction(MainWindow);
        actionSave_graph->setObjectName(QStringLiteral("actionSave_graph"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(-1, 3, 5, 5);
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(300, 0));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(3);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 5, 5, -1);
        groupBox_3 = new QGroupBox(frame);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        verticalLayout_2 = new QVBoxLayout(groupBox_3);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 10, 0, 0);
        label_5 = new QLabel(groupBox_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(label_5);

        kernelType = new QComboBox(groupBox_3);
        kernelType->setObjectName(QStringLiteral("kernelType"));

        verticalLayout_2->addWidget(kernelType);

        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(label_4);

        expectedSolution = new QComboBox(groupBox_3);
        expectedSolution->setObjectName(QStringLiteral("expectedSolution"));

        verticalLayout_2->addWidget(expectedSolution);

        widget = new QWidget(groupBox_3);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout_3 = new QGridLayout(widget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        lowerBoundInput = new QDoubleSpinBox(widget);
        lowerBoundInput->setObjectName(QStringLiteral("lowerBoundInput"));

        gridLayout_3->addWidget(lowerBoundInput, 0, 1, 1, 1);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        upperBoundInput = new QDoubleSpinBox(widget);
        upperBoundInput->setObjectName(QStringLiteral("upperBoundInput"));

        gridLayout_3->addWidget(upperBoundInput, 1, 1, 1, 1);


        verticalLayout_2->addWidget(widget);

        formulaWidget = new FormulaView(groupBox_3);
        formulaWidget->setObjectName(QStringLiteral("formulaWidget"));
        sizePolicy1.setHeightForWidth(formulaWidget->sizePolicy().hasHeightForWidth());
        formulaWidget->setSizePolicy(sizePolicy1);
        formulaWidget->setMinimumSize(QSize(0, 120));

        verticalLayout_2->addWidget(formulaWidget);

        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);


        verticalLayout->addWidget(groupBox_3);

        line_2 = new QFrame(frame);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setStyleSheet(QStringLiteral(""));
        widget_2 = new QWidget(groupBox);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(0, 20, 291, 82));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy2);
        gridLayout_2 = new QGridLayout(widget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_3 = new QLabel(widget_2);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 1);

        gridStepsInput = new QSpinBox(widget_2);
        gridStepsInput->setObjectName(QStringLiteral("gridStepsInput"));
        gridStepsInput->setMinimum(10);
        gridStepsInput->setMaximum(100000);

        gridLayout_2->addWidget(gridStepsInput, 0, 1, 1, 1);

        label_7 = new QLabel(widget_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        input_RightPartError = new QDoubleSpinBox(widget_2);
        input_RightPartError->setObjectName(QStringLiteral("input_RightPartError"));

        gridLayout_2->addWidget(input_RightPartError, 1, 1, 1, 1);


        verticalLayout->addWidget(groupBox);

        btnStartSolving = new QPushButton(frame);
        btnStartSolving->setObjectName(QStringLiteral("btnStartSolving"));

        verticalLayout->addWidget(btnStartSolving);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        line = new QFrame(frame);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        groupBox_2 = new QGroupBox(frame);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 281, 41));
        gridLayout_4 = new QGridLayout(layoutWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_4->addWidget(label_6, 0, 0, 1, 1);

        iterationsInOneStep = new QSpinBox(layoutWidget);
        iterationsInOneStep->setObjectName(QStringLiteral("iterationsInOneStep"));
        iterationsInOneStep->setValue(1);

        gridLayout_4->addWidget(iterationsInOneStep, 0, 1, 1, 1);


        verticalLayout->addWidget(groupBox_2);


        gridLayout->addWidget(frame, 0, 0, 1, 1);

        frame_2 = new QFrame(centralWidget);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame_2);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        plotWidget = new QCustomPlot(frame_2);
        plotWidget->setObjectName(QStringLiteral("plotWidget"));

        verticalLayout_3->addWidget(plotWidget);

        widget_3 = new QWidget(frame_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        sizePolicy1.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy1);
        widget_3->setMinimumSize(QSize(0, 25));
        horizontalLayout = new QHBoxLayout(widget_3);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, 0, 5, 5);
        statusLabel = new QLabel(widget_3);
        statusLabel->setObjectName(QStringLiteral("statusLabel"));
        statusLabel->setAutoFillBackground(false);
        statusLabel->setScaledContents(false);

        horizontalLayout->addWidget(statusLabel);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_Status = new QLabel(widget_3);
        label_Status->setObjectName(QStringLiteral("label_Status"));

        horizontalLayout->addWidget(label_Status);


        verticalLayout_3->addWidget(widget_3);


        gridLayout->addWidget(frame_2, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setMouseTracking(false);
        mainToolBar->setLayoutDirection(Qt::RightToLeft);
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        mainToolBar->addAction(actionCalculate_all_iterations);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionNextStep);
        mainToolBar->addSeparator();
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionSave_graph);

        retranslateUi(MainWindow);
        QObject::connect(actionCalculate_all_iterations, SIGNAL(triggered()), MainWindow, SLOT(onActionCalculate()));
        QObject::connect(actionNextStep, SIGNAL(triggered()), MainWindow, SLOT(onActionNextIteration()));
        QObject::connect(btnStartSolving, SIGNAL(clicked()), MainWindow, SLOT(onActionStart()));
        QObject::connect(actionSave_graph, SIGNAL(triggered()), MainWindow, SLOT(onActionSaveGraph()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Intergal equation solver (featuring interations method)", 0));
        actionCalculate_all_iterations->setText(QApplication::translate("MainWindow", "Calculate all iterations", 0));
        actionPrevIteration->setText(QApplication::translate("MainWindow", "< Prev Iteration", 0));
        actionNextStep->setText(QApplication::translate("MainWindow", "Next Iteration >", 0));
        actionSave_graph->setText(QApplication::translate("MainWindow", "Save graph", 0));
        groupBox_3->setTitle(QApplication::translate("MainWindow", " Equation", 0));
        label_5->setText(QApplication::translate("MainWindow", "Kernel:", 0));
        kernelType->clear();
        kernelType->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "exp(-(x-y))", 0)
         << QApplication::translate("MainWindow", "exp(ixy)   -  Dirichlet", 0)
        );
        label_4->setText(QApplication::translate("MainWindow", "Expected exact solution:", 0));
        expectedSolution->clear();
        expectedSolution->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "exp(x)", 0)
         << QApplication::translate("MainWindow", "x", 0)
         << QApplication::translate("MainWindow", "cos(pi*x)", 0)
         << QApplication::translate("MainWindow", "sin(2*pi*x)", 0)
        );
        label->setText(QApplication::translate("MainWindow", "Lower integral bound:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Upper intergal bound:", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", " Method parameters", 0));
        label_3->setText(QApplication::translate("MainWindow", "Grid steps:", 0));
        label_7->setText(QApplication::translate("MainWindow", "Right part error %:", 0));
        btnStartSolving->setText(QApplication::translate("MainWindow", "Start / Restart solution", 0));
        groupBox_2->setTitle(QApplication::translate("MainWindow", " Presentation", 0));
        label_6->setText(QApplication::translate("MainWindow", "Iterations in one step:", 0));
        statusLabel->setText(QApplication::translate("MainWindow", "red - exact solution; blue- current iteration; black dashed - previous iteration", 0));
        label_Status->setText(QApplication::translate("MainWindow", "TextLabel", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
