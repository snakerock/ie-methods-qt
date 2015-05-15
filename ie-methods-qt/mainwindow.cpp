
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QVector>
#include <QFileDialog>

#include <iostream>
#include <functional>
#include <algorithm>

#include "approximation.h"
#include "iterationmethodpositive.h"
#include "iterationmethoddirichletkernel.h"
#include "ietypes.h"

#include "mathfunctions.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString strFormula = "<math>\n"
                         "    <mrow>\n"
                         "        <munderover>\n"
                         "            <mo>\n"
                         "                &#8747;\n"
                         "            </mo>\n"
                         "            <mn>\n"
                         "                0\n"
                         "            </mn>\n"
                         "            <mn>\n"
                         "                1\n"
                         "            </mn>\n"
                         "        </munderover>\n"
                         "        <mfrac>\n"
                         "            <mrow>\n"
                         "                <mi>\n"
                         "                    d\n"
                         "                </mi>\n"
                         "                <mi>\n"
                         "                    x\n"
                         "                </mi>\n"
                         "            </mrow>\n"
                         "            <mi>\n"
                         "                x\n"
                         "            </mi>\n"
                         "        </mfrac>\n"
                         "    </mrow>\n"
                         "</math>";

    ui->formulaWidget->setFormula(strFormula);

    ui->lowerBoundInput->setValue(0);
    ui->upperBoundInput->setValue(1);
    ui->gridStepsInput->setValue(100);

    ui->input_RightPartError->setValue(0);

    ui->plotWidget->addGraph();
    ui->plotWidget->addGraph();
    ui->plotWidget->addGraph();
    ui->plotWidget->xAxis->setRange(ui->lowerBoundInput->value(), ui->upperBoundInput->value());

    ui->plotWidget->graph(1)->setPen(QPen(QColor::fromRgb(255, 50, 50)));
    ui->plotWidget->graph(2)->setPen(QPen(Qt::PenStyle::DashLine));

    makeGuiMathFunctionsAssociations();
    onActionStart();
}


MainWindow::~MainWindow()
{
    delete solver;
    delete ui;
}


void MainWindow::setGraphBoundsTo(fx_t func)
{
    double minY = func(solver->getA());
    double maxY = minY;
    double step = solver->getDx();

    for (double x = solver->getA(); x <= solver->getB(); x += step) {
        double cur = func(x);
        if (cur < minY) minY = cur;
        if (cur > maxY) maxY = cur;
    }

    ui->plotWidget->yAxis->setRange(minY - 0.2, maxY + 0.2);
}


void MainWindow::updateStatusBar()
{
    ui->label_Status->setText(QString("Iteration: %1    Error: %2").arg(iterationCount).arg(
                                  solver->getDifference(solution, solver->GetCurrentApproximation())));
}


void MainWindow::makeRightPartNoise()
{
    if (ui->input_RightPartError->value() == 0) return;

    Approximation newRightPart;

    double step = solver->getDx();
    for (double x = solver->getA(); x <= solver->getB(); x += step) {
        double error = ((double(rand() % 100)) / 100.0) * (ui->input_RightPartError->value() / 100.0);
        if (rand() % 2) error = -error;
        newRightPart.addXY(x, rightPart(x) * (error + 1.0));
    }

    rightPart = newRightPart;
}


void MainWindow::makeGuiMathFunctionsAssociations()
{
    kernels[0]    = MathFunctions::Kernels::e_abs_x_y;

    //solutions[0] = fx_t([](double) { return 1; });
    solutions[0] = fx_t(MathFunctions::Solutions::exponent);
    solutions[1] = fx_t(MathFunctions::Solutions::identical);
    solutions[2] = fx_t(MathFunctions::Solutions::cosinus_pi);
    solutions[3] = fx_t(MathFunctions::Solutions::sinus_2pi);

    rightParts[std::make_pair(0, 2)] = fx_t(MathFunctions::RightParts::f_kernel_e_abs_x_y_cos_pi);
    rightParts[std::make_pair(0, 3)] = fx_t(MathFunctions::RightParts::f_kernel_e_abs_x_y_sin_2pi);
    rightParts[std::make_pair(0, 0)] = fx_t(MathFunctions::RightParts::f_kernel_e_abs_x_y_exp);
}


void MainWindow::plot(int graphId, const QVector<double> &xValues, const QVector<double> &yValues)
{
    ui->plotWidget->graph(graphId)->setData(xValues, yValues);
}


void MainWindow::plot(int graphId, fx_t func)
{
    QVector<double> xValues, yValues;
    xValues.reserve(solver->getPartsNumber());
    yValues.reserve(solver->getPartsNumber());
    double step = solver->getDx();

    for (double x = solver->getA(); x <= solver->getB(); x += step) {
        xValues.push_back(x);
        yValues.push_back(func(x));
    }

    plot(graphId, xValues, yValues);
}


void MainWindow::onActionCalculate()
{
    IterationMethodPositive im(MathFunctions::RightParts::f_kernel_e_abs_x_y_exp, MathFunctions::Kernels::e_abs_x_y);
    fx_t prevU = im.Iterate();
    fx_t curU = im.Iterate();
    double prevDiff, curDiff, realDiff;
    curDiff = im.getDifference(curU, prevU);

    for (int i = 1; i < 5; ++i) {
        prevDiff = curDiff;
        prevU = curU;
        curU = im.Iterate();

        realDiff = im.getDifference(curU, MathFunctions::Solutions::exponent);
        curDiff = im.getDifference(curU, prevU);
        std::cout << "|| u[" << i + 1 << "] - u[" << i << "] || = " << curDiff;
        std::cout << ";\t   || u[" << i + 1 << "] - U || = " << realDiff << std::endl;
        if (curDiff > prevDiff) {
            std::cout << "[WARNING] Divergence" << std::endl;
        }

        plot(0, curU);
    }

    for (double x = 10e-3 * 0.5; x <= 1.0; x+= 10e-3) {
        std::cout << "u(" << x << ") = " << curU(x) << std::endl;
    }
}


void MainWindow::onActionPrevStep()
{

}


void MainWindow::onActionNextIteration()
{
    fx_t prevU = solver->GetCurrentApproximation();
    for (int i = 0; i < ui->iterationsInOneStep->value(); ++i) {
        solver->Iterate();
    }

    plot(0, solver->GetCurrentApproximation());
    plot(2, prevU);

    ui->plotWidget->replot();
    iterationCount += ui->iterationsInOneStep->value();
    updateStatusBar();
}


void MainWindow::onActionStart()
{
    iterationCount = 0;
    if (solver != nullptr) delete solver;
    solution = solutions[ui->expectedSolution->currentIndex()];

    if (ui->kernelType->currentIndex() == 1) {
        /* dirichlet kernel */

        auto direchletRightPart = MathFunctions::RightParts::f_dirichlet_exp;
        if (ui->expectedSolution->currentIndex() == 1) {
            direchletRightPart = MathFunctions::RightParts::f_dirichlet_ident;
        }

        makeRightPartNoise();
        solver = new IterationMethodDirichletKernel(direchletRightPart,
                                                    1.0, ui->upperBoundInput->value(),
                                                    /*(ui->upperBoundInput->value() - ui->lowerBoundInput->value()) / */
                                                    ui->gridStepsInput->value());
    } else {

        kernel = kernels[ui->kernelType->currentIndex()];
        rightPart = rightParts[std::make_pair(ui->kernelType->currentIndex(), ui->expectedSolution->currentIndex())];

        makeRightPartNoise();
        solver = new IterationMethodPositive(rightPart, kernel,
                                             ui->lowerBoundInput->value(), ui->upperBoundInput->value(), ui->gridStepsInput->value());
    }


    setGraphBoundsTo(solution);
    plot(1, solution);
    plot(0, [](double) { return 0; });
    plot(2, [](double) { return 0; });

    ui->plotWidget->repaint();
}


void MainWindow::onActionSaveGraph()
{
    auto fileName = QFileDialog::getSaveFileName(this,
        tr("Save Image"), QString("graph-%1.png").arg(iterationCount), tr("Image Files (*.png)"));

    ui->plotWidget->savePng(fileName);
}

