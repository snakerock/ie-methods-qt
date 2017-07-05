#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <unordered_map>
#include <map>

#include "iterationmethodpositive.h"
#include "iterationmethodcommon.h"
#include "ietypes.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    IterationMethodPositive<double> *solverReal = nullptr;
    IterationMethodPositive<Complex> *solverComplex = nullptr;
    int iterationCount = 0;

private:
    fx_t<double> rightPartReal;
    fxy_t<double> kernelReal;
    fx_t<double> solutionReal;

    fx_t<Complex> rightPartComplex;
    fxy_t<Complex> kernelComplex;
    fx_t<Complex> solutionComplex;

    std::unordered_map<int, fxy_t<double>> kernelsReal;
    std::map<std::pair<int, int>, fx_t<double>> rightPartsReal;
    std::unordered_map<int, fx_t<double>> solutionsReal;

    std::unordered_map<int, fxy_t<Complex>> kernelsComplex;
    std::map<std::pair<int, int>, fx_t<Complex>> rightPartsComplex;
    std::unordered_map<int, fx_t<Complex>> solutionsComplex;



private:
    void plot(int graphId, const QVector<double>& x, const QVector<double>& y);
    void plot(int graphId, fx_t<double> func);
    void plot(int graphId, fx_t<Complex> func);
    void setGraphBoundsTo(fx_t<double> func);
    void setGraphBoundsTo(fx_t<Complex> func);
    void updateStatusBar();
    void makeRightPartNoise();
    std::vector<Complex> getComplexRightPartNoise();

    void makeGuiMathFunctionsAssociations();

private slots:
    void onActionCalculate();
    void onActionPrevStep();
    void onActionNextIteration();
    void onActionStart();
    void onActionSaveGraph();
};

#endif // MAINWINDOW_H
