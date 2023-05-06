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
#include <signal.h>

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
    PlotData(bool square);
    PlotData(double xmax, double xmin, double ymax, double ymin, bool square); // 範囲設定
    ~PlotData();
    void SeTics(double xtics, double ytics);
    void Xrangset(double xmax, double xmin);
    void Yrangset(double ymax, double ymin);
    void Zrangset(double zmax, double zmin);
    void SaveFigure(char *fname);
    // void Datalabel(char *a,char *b,char *c);

    // ２次元
    void XYlabel(char *x, char *y);
    void SaveData2D(double Xdata, double Ydata);
    void PrintFig2D(void);
    void SaveData2Dx2(double Xdata, double Ydata, double Xdata2, double Ydata2);
    void PrintFig2Dx2(char *a, char *b);
    void SaveData2Dx3(double Xdata, double Ydata, double Xdata2, double Ydata2, double Xdata3, double Ydata3);
    void PrintFig2Dx3(char *a, char *b, char *c);
    // ３次元
    void XYZlabel(char *x, char *y, char *z);
    void SaveData3D(double Xdata, double Ydata, double Zdata);
    void PrintFig3D(void);
};
#endif // CREATFIG_HPP