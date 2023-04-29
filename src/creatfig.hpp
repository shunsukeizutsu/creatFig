/*
 *gnuplotでグラフを生成するクラス
 *author : Shunsuke.I
 *create : 2023/04/19
 */
#ifndef CREATFIG_HPP_
#define CREATFIG_HPP_

#include <stdio.h>
#include <iostream>
#include <vector>

typedef struct Figuredata
{
    double xdata;
    double ydata;
    double zdata;

    double xdata2;
    double ydata2;

    double xdata3;
    double ydata3;
} plot_data;

class PlotData
{
protected:
    FILE *gp;
    std::vector<plot_data> Vdata;
    char *xlabelname;
    char *ylabelname;
    char *zlabelname;

public:
    PlotData();
    PlotData(double xmax, double xmin, double ymax, double ymin);//範囲設定
    ~PlotData();
    void settingtics(int xtics,int ytics);
    //２次元
    void XYlabel(char *x, char *y);
    void saveData2D(double Xdata, double Ydata);
    void PrintFig2D(void);
    void saveData2Dx2(double Xdata, double Ydata, double Xdata2, double Ydata2);
    void PrintFig2Dx2(void);
    void saveData2Dx3(double Xdata, double Ydata, double Xdata2, double Ydata2, double Xdata3, double Ydata3);
    void PrintFig2Dx3(void);
    //３次元
    void XYZlabel(char *x, char *y, char *z);
    void saveData3D(double Xdata, double Ydata, double Zdata);
    void PrintFig3D(void);
};
#endif // CREATFIG_HPP