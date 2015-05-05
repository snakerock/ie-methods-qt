#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <unordered_map>
#include <map>

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
    IterationMethodPositive *solver = nullptr;
    int iterationCount = 0;

private:
    fx_t rightPart;
    fxy_t kernel;
    fx_t solution;

    std::unordered_map<int, fxy_t> kernels;
    std::map<std::pair<int, int>, fx_t> rightParts;
    std::unordered_map<int, fx_t> solutions;


private:
    void plot(int graphId, const QVector<double>& x, const QVector<double>& y);
    void plot(int graphId, fx_t func);
    void setGraphBoundsTo(fx_t func);
    void updateStatusBar();

    void makeGuiMathFunctionsAssociations();

private slots:
    void onActionCalculate();
    void onActionPrevStep();
    void onActionNextIteration();
    void onActionStart();
    void onActionSaveGraph();
};

#endif // MAINWINDOW_H
