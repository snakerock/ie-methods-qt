
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
#include "iterationmethodhankel.h"
#include "iterationmethodln.h"
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
    ui->kernelParameterInput->setValue(1);
    ui->gridStepsInput->setValue(100);

    ui->input_RightPartError->setValue(0);

    ui->plotWidget->addGraph();
    ui->plotWidget->addGraph();
    ui->plotWidget->addGraph();
    ui->plotWidget->addGraph();
    ui->plotWidget->addGraph();
    ui->plotWidget->addGraph();
    ui->plotWidget->xAxis->setRange(ui->lowerBoundInput->value(), ui->upperBoundInput->value());

    int penWidth = 5;

    QPen exactSolutionReal = QPen(QColor::fromRgb(255, 50, 50));
    exactSolutionReal.setWidth(penWidth);
    QPen exactSolutionComplex = QPen(QColor::fromRgb(50, 50, 255));
    exactSolutionComplex.setWidth(penWidth);
    QPen approximateSolutionReal = QPen(QColor::fromRgb(50, 255, 50));
    approximateSolutionReal.setWidth(penWidth);
    QPen approximateSolutionComplex = QPen(QColor::fromRgb(50, 255, 255));
    approximateSolutionComplex.setWidth(penWidth);
    QPen previousSolutionReal = QPen(Qt::PenStyle::DashLine);
    previousSolutionReal.setColor(QColor::fromRgb(10, 170, 10));
    previousSolutionReal.setWidth(penWidth / 2);
    QPen previousSolutionComplex = QPen(Qt::PenStyle::DashLine);
    previousSolutionComplex.setColor(QColor::fromRgb(10, 170, 170));
    previousSolutionComplex.setWidth(penWidth / 2);

    ui->plotWidget->graph(0)->setPen(exactSolutionReal);
    ui->plotWidget->graph(1)->setPen(previousSolutionReal);
    ui->plotWidget->graph(2)->setPen(approximateSolutionReal);

    ui->plotWidget->graph(3)->setPen(exactSolutionComplex);
    ui->plotWidget->graph(4)->setPen(previousSolutionComplex);
    ui->plotWidget->graph(5)->setPen(approximateSolutionComplex);

    makeGuiMathFunctionsAssociations();
    //onActionStart();
}


MainWindow::~MainWindow()
{
    delete solverReal;
    delete ui;
}


void MainWindow::setGraphBoundsTo(fx_t<double> func)
{
    if (func == nullptr) {
        return;
    }

    double minY = func(solverReal->getA());
    double maxY = minY;
    double step = solverReal->getDx();

    for (double x = solverReal->getA(); x <= solverReal->getB(); x += step) {
        double cur = func(x);
        if (cur < minY) minY = cur;
        if (cur > maxY) maxY = cur;
    }

    ui->plotWidget->yAxis->setRange(minY - 1.2, maxY + 2.2);
    ui->plotWidget->xAxis->setRange(ui->lowerBoundInput->value(), ui->upperBoundInput->value());
    //ui->plotWidget->yAxis->setRange(-3.0, 3.0);
}

void MainWindow::setGraphBoundsTo(fx_t<Complex> func)
{
    if (func == nullptr) {
        return;
    }

    double minY = func(solverComplex->getA()).real();
    double maxY = minY;
    double step = solverComplex->getDx();

    for (double x = solverComplex->getA(); x <= solverComplex->getB(); x += step) {
        Complex cur = func(x);
        if (cur.real() < minY) minY = cur.real();
        if (cur.imag() < minY) minY = cur.imag();
        if (cur.real() > maxY) maxY = cur.real();
        if (cur.imag() > maxY) maxY = cur.imag();
    }

    ui->plotWidget->yAxis->setRange(minY - 0.2, maxY + 0.2);
    ui->plotWidget->xAxis->setRange(ui->lowerBoundInput->value(), ui->upperBoundInput->value());
    //ui->plotWidget->yAxis->setRange(-3.0, 3.0);
}

void MainWindow::updateStatusBar()
{
    if (solverReal != nullptr) {
        ui->label_Status->setText(QString("Iteration: %1    Error: %2").arg(iterationCount).arg(
                                      solverReal->getDifference(solutionReal, solverReal->GetCurrentApproximation())));
    } else if (solverComplex != nullptr) {
        ui->label_Status->setText(QString("Iteration: %1    Error: %2").arg(iterationCount).arg(
                                      solverComplex->getDifference(solutionComplex, solverComplex->GetCurrentApproximation())));

    }
}


void MainWindow::makeRightPartNoise()
{
    if (ui->input_RightPartError->value() == 0) return;

    Approximation<double> newRightPart;

    double step = solverReal->getDx();
    for (double x = solverReal->getA() + step * 0.5; x <= solverReal->getB(); x += step) {
        double error = ((double(rand() % 100)) / 100.0) * (ui->input_RightPartError->value() / 100.0);
        if (rand() % 2) error = -error;
        newRightPart.addXY(x, rightPartReal(x) * (error + 1.0));
    }

    rightPartReal = newRightPart;
}


std::vector<Complex> MainWindow::getComplexRightPartNoise()
{
    std::vector<Complex> noise;

    int n = ui->gridStepsInput->value();
    for (int i = 0; i < n; ++i) {
        double errorRe = ((double(rand() % 100)) / 100.0) * (ui->input_RightPartError->value() / 100.0);
        if (rand() % 2) errorRe = -errorRe;

        double errorIm = ((double(rand() % 100)) / 100.0) * (ui->input_RightPartError->value() / 100.0);
        if (rand() % 2) errorIm = -errorIm;

        noise.push_back(Complex(1.0 + errorRe, 1.0 + errorIm));
    }

    return noise;
}

void MainWindow::makeGuiMathFunctionsAssociations()
{
    kernelsReal[0]    = MathFunctions::Kernels::e_abs_x_y;
    kernelsReal[2]    = [this] (double x, double y) {
        return MathFunctions::Kernels::ln_x_y(x, y, this->ui->kernelParameterInput->value());
    };
    kernelsReal[3]    = MathFunctions::Kernels::ln_abs_x;
    kernelsReal[4]    = MathFunctions::Kernels::ln_abs_x_y;

    kernelsComplex[0] = [] (double x, double y) { return MathFunctions::Kernels::Hankel(x, y, 1, 1); };

    //solutions[0] = fx_t<double>([](double) { return 1; });
    solutionsReal[0] = fx_t<double>(MathFunctions::Solutions::exponent);
    solutionsReal[1] = fx_t<double>(MathFunctions::Solutions::identical);
    solutionsReal[2] = fx_t<double>(MathFunctions::Solutions::cosinus_pi);
    solutionsReal[3] = fx_t<double>(MathFunctions::Solutions::sinus_2pi);
    solutionsReal[4] = fx_t<double>(MathFunctions::Solutions::one);
    solutionsReal[5] = [this] (double x) {
        return MathFunctions::Solutions::phi_sqrt(x, this->ui->kernelParameterInput->value());
    };
    solutionsReal[6] = fx_t<double>(MathFunctions::Solutions::sqrt_1_y2);
    solutionsReal[8] = fx_t<double>(MathFunctions::Solutions::one_2pi_ln2_sqrt);

    solutionsComplex[0] = fx_t<Complex>(MathFunctions::Solutions::complex_cos_plus_sin);
    solutionsComplex[1] = fx_t<Complex>(MathFunctions::Solutions::complex_exp);

    rightPartsReal[std::make_pair(0, 2)] = fx_t<double>(MathFunctions::RightParts::f_kernel_e_abs_x_y_cos_pi);
    rightPartsReal[std::make_pair(0, 3)] = fx_t<double>(MathFunctions::RightParts::f_kernel_e_abs_x_y_sin_2pi);
    rightPartsReal[std::make_pair(0, 0)] = fx_t<double>(MathFunctions::RightParts::f_kernel_e_abs_x_y_exp);
    rightPartsReal[std::make_pair(2, 4)] = [this] (double x) {
        return MathFunctions::RightParts::f_kernel_ln_x_y_one(x, this->ui->kernelParameterInput->value());
    };
    rightPartsReal[std::make_pair(3, 4)] = fx_t<double>(MathFunctions::RightParts::f_kernel_ln_abs_x_one);
    rightPartsReal[std::make_pair(4, 6)] = fx_t<double>(MathFunctions::RightParts::f_kernel_ln_abs_x_y_sqrt);
    rightPartsReal[std::make_pair(6, 8)] = fx_t<double>(MathFunctions::RightParts::f_kernel_ln_x_y_one_2pi_ln2_sqrt);
}


void MainWindow::plot(int graphId, const QVector<double> &xValues, const QVector<double> &yValues)
{
    ui->plotWidget->graph(graphId)->setData(xValues, yValues);
}


void MainWindow::plot(int graphId, fx_t<double> func)
{
    if (func == nullptr) {
        return;
    }

    QVector<double> xValues, yValues;
    int partsNumber, a, b;
    double step;
    if (solverReal != nullptr) {
        partsNumber = solverReal->getPartsNumber();
        a = solverReal->getA();
        b = solverReal->getB();
        step = solverReal->getDx();
    } else if (solverComplex != nullptr) {
        partsNumber = solverComplex->getPartsNumber();
        a = solverComplex->getA();
        b = solverComplex->getB();
        step = solverComplex->getDx();
    }

    xValues.reserve(partsNumber);
    yValues.reserve(partsNumber);

    for (double x = a + step * 0.5; x <= b; x += step) {
        xValues.push_back(x);
        yValues.push_back(func(x));
    }

    plot(graphId, xValues, yValues);
}

void MainWindow::plot(int graphId, fx_t<Complex> func)
{
    if (func == nullptr) {
        return;
    }

    plot(graphId, fx_t<double>([func] (double x) { return func(x).real(); }));
    plot(graphId + 3, fx_t<double>([func] (double x) { return func(x).imag(); }));
}

void MainWindow::onActionCalculate()
{
    IterationMethodPositive<double> im(MathFunctions::RightParts::f_kernel_e_abs_x_y_exp, MathFunctions::Kernels::e_abs_x_y);
    fx_t<double> prevU = im.Iterate();
    fx_t<double> curU = im.Iterate();
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
    if (solverReal != nullptr) {
        fx_t<double> prevU = solverReal->GetCurrentApproximation();
        for (int i = 0; i < ui->iterationsInOneStep->value(); ++i) {
            solverReal->Iterate();
        }

        if (solutionReal == nullptr) {
            setGraphBoundsTo(solverReal->GetCurrentApproximation());
        }
        plot(2, solverReal->GetCurrentApproximation());
        plot(1, prevU);
    } else if (solverComplex != nullptr) {
        fx_t<Complex> prevU = solverComplex->GetCurrentApproximation();
        for (int i = 0; i < ui->iterationsInOneStep->value(); ++i) {
            solverComplex->Iterate();
        }

        //if (solutionComplex == nullptr) {
            setGraphBoundsTo(solverComplex->GetCurrentApproximation());
        //}
        plot(0, solutionComplex);
        plot(2, solverComplex->GetCurrentApproximation());
        plot(1, prevU);
    }

    ui->plotWidget->replot();
    iterationCount += ui->iterationsInOneStep->value();
    updateStatusBar();
}


void MainWindow::onActionStart()
{
    iterationCount = 0;
    if (solverReal != nullptr) {
        delete solverReal;
        solverReal = nullptr;
    }

    if (solverComplex != nullptr) {
        delete solverComplex;
        solverComplex = nullptr;
    }

    solutionReal = solutionsReal[ui->expectedSolution->currentIndex()];

    if (ui->kernelType->currentIndex() == 1) {
        /* Dirichlet kernel */

        auto dirichletRightPart = MathFunctions::RightParts::f_dirichlet_exp;
        if (ui->expectedSolution->currentIndex() == 1) {
            dirichletRightPart = MathFunctions::RightParts::f_dirichlet_ident;
        }

        double k = ui->kernelParameterInput->value();
        double b = ui->upperBoundInput->value();
        std::vector<Complex> noise = this->getComplexRightPartNoise();
        auto noisedRightPart = fx_t<Complex>([ this, k, b, noise, dirichletRightPart ] (double x) {
            Complex res = dirichletRightPart(x, k, b);
            int i = int(x / this->solverReal->getDx());
            Complex n = noise[i];
            return Complex(res.real() * n.real(), res.imag() * n.imag());
        });
        //makeRightPartNoise();
        solverReal = new IterationMethodDirichletKernel(noisedRightPart,
                                                    k,
                                                    b,
                                                    /*(ui->upperBoundInput->value() - ui->lowerBoundInput->value()) / */
                                                    ui->gridStepsInput->value());
    } else if (ui->kernelType->currentIndex() == 5) {
        /* Hankel kernel */

        switch (ui->expectedSolution->currentIndex()) {
        case 7:
            solutionComplex = solutionsComplex[0];
            break;
        case 0:
            solutionComplex = solutionsComplex[1];
            break;
        }

        double k = ui->kernelParameterInput->value();
        double b = ui->upperBoundInput->value();

        kernelComplex = [k] (double x, double y) { return MathFunctions::Kernels::Hankel(x, y, k, 0.001); };


        IterationMethodHankel *solutionSolver = new IterationMethodHankel([] (double x) { return Complex(1, 0); },
                                                                       ui->kernelParameterInput->value(),
                                                                       ui->upperBoundInput->value(),
                                                                       ui->gridStepsInput->value(),
                                                                       1,
                                                                       solutionComplex);
        /*solutionComplex = [ this, solutionSolver ] (double x) {
            solutionSolver->Iterate(this->iterationCount - solutionSolver->getIterationNumber());
            return solutionSolver->GetCurrentApproximation()(x);
        };*/

        std::vector<Complex> noise = this->getComplexRightPartNoise();
        rightPartComplex = [ this, noise ] (double x) {
            Complex res = Complex(1, 0);
            int i = int(x / this->solverComplex->getDx());
            Complex n = noise[i];
            return Complex(res.real() * n.real(), n.imag() - 1.0);
        };

        rightPartComplex = nullptr;

        solverComplex = new IterationMethodHankel(rightPartComplex,
                                                  ui->kernelParameterInput->value(),
                                                  ui->upperBoundInput->value(),
                                                  ui->gridStepsInput->value(),
                                                  1,
                                                  solutionComplex);
/*
        solverComplex = new IterationMethodPositive<Complex>(nullptr,
                                                             kernelComplex,
                                                             ui->lowerBoundInput->value(),
                                                             ui->upperBoundInput->value(),
                                                             ui->gridStepsInput->value(),
                                                             solutionComplex);*/

    } else if (ui->kernelType->currentIndex() == 6) {
        // Ln(1/abs(x-y)) kernel

        solutionReal = solutionsReal[ui->expectedSolution->currentIndex()];
        rightPartReal = rightPartsReal[std::make_pair(ui->kernelType->currentIndex(), ui->expectedSolution->currentIndex())];
        solverReal = new IterationMethodLn(rightPartReal,
                                           ui->gridStepsInput->value(),
                                           solutionReal);
    } else {

        kernelReal = kernelsReal[ui->kernelType->currentIndex()];
        if (ui->expectedSolution->currentIndex() == 5) {
            rightPartReal = nullptr;
            solutionReal = solutionsReal[5];
        } else {
            rightPartReal = rightPartsReal[std::make_pair(ui->kernelType->currentIndex(), ui->expectedSolution->currentIndex())];
            solverReal = new IterationMethodPositive<double>(rightPartReal,
                                                 kernelReal,
                                                 ui->lowerBoundInput->value(),
                                                 ui->upperBoundInput->value(),
                                                 ui->gridStepsInput->value(),
                                                 solutionReal);
            makeRightPartNoise();
        }

        solverReal = new IterationMethodPositive<double>(rightPartReal,
                                             kernelReal,
                                             ui->lowerBoundInput->value(),
                                             ui->upperBoundInput->value(),
                                             ui->gridStepsInput->value(),
                                             solutionReal);
    }


    if (solverReal != nullptr) {
        if (solutionReal != nullptr) {
            setGraphBoundsTo(solutionReal);
            plot(0, solutionReal);
        }
        fx_t<double> zero = [](double) { return 0; };
        plot(1, zero);
        plot(2, zero);
    } else if (solverComplex != nullptr) {
        if (solutionComplex != nullptr) {
            setGraphBoundsTo(solutionComplex);
            plot(0, solutionComplex);
        }
        fx_t<Complex> zero = [](double) { return 0; };
        plot(1, zero);
        plot(2, zero);
    }

    ui->plotWidget->repaint();
}


void MainWindow::onActionSaveGraph()
{
    auto fileName = QFileDialog::getSaveFileName(this,
        tr("Save Image"), QString("graph-%1.png").arg(iterationCount), tr("Image Files (*.png)"));

    ui->plotWidget->savePng(fileName);
}

