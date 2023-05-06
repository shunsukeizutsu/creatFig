#include "creatfig.hpp"

PlotData::PlotData(bool square) // default
{                               // グラフの詳細設定、文字のフォント等
    gp = popen("gnuplot", "w"); // シェル起動
    fprintf(gp, "set grid\n");
    fprintf(gp, "set size ratio -1\n");
    if (square == true)
    {
        fprintf(gp, "set size square\n");
    }
}
PlotData::PlotData(double xmax, double xmin, double yamx, double ymin, bool square) // グラフの範囲を設定したい場合
{
    gp = popen("gnuplot", "w"); // シェル起動
    fprintf(gp, "set grid\n");
    fprintf(gp, "set size ratio -1\n");
    fprintf(gp, "set xrange[%f:%f]\nset yrange[%f:%f]\n", xmin, xmax, ymin, yamx); // 範囲
    if (square == true)
    {
        fprintf(gp, "set size square\n");
    }
}
PlotData::~PlotData()
{
    pclose(gp);
}
void PlotData::SaveFigure(char *fname)
{
    fprintf(gp,"set terminal postscript eps color enhanced\n");
    fprintf(gp,"set out '%s.esp'\n",fname);
    fprintf(gp,"replot\n");
}
void PlotData::SeTics(double xtics, double ytics)
{
    fprintf(gp, "set xtics %f\n", xtics);
    fprintf(gp, "set ytics %f\n", ytics);
}
void PlotData::Xrangset(double xmax, double xmin)
{
    fprintf(gp, "set xrange[%f:%f]\n", xmax, xmin);
}
void PlotData::Yrangset(double ymax, double ymin)
{
    fprintf(gp, "set yrange[%f:%f]\n", ymax, ymin);
}
void PlotData::Zrangset(double zmax, double zmin)
{
    fprintf(gp, "set zrange[%f:%f]\n", zmax, zmin);
}
//**********************2次元***************************//
void PlotData::SaveData2D(double Xdata, double Ydata) // プロットしたいデータ->vectorへ
{
    plot_data tmp;
    tmp.xdata = Xdata;
    tmp.ydata = Ydata;
    Vdata.push_back(tmp);
}
void PlotData::XYlabel(char *x, char *y)
{
    fprintf(gp, "set xlabel \'%s\'\n", x);
    fprintf(gp, "set ylabel \'%s\'\n", y);
}
void PlotData::PrintFig2D() // vector->２次元で一つのグラフ生成
{
    printf("\x1b[32m\x1b[1m%s\x1b[39m\x1b[0m\n", "Start Plot PrintFigure 2D");
    fprintf(gp, "p ");
    fprintf(gp, " '-' pt 5 ps 0.5 lc rgb 'red' t \"\" ");
    
    for (int i = 0; i < Vdata.size(); i++)
    {
        // printf("%f %f\n", Vdata[i].xdata, Vdata[i].ydata);

        fprintf(gp, "%f %f\n", Vdata[i].xdata, Vdata[i].ydata);
    }
    fprintf(gp, "e\n");
    fflush(gp);
}
void PlotData::SaveData2Dx2(double Xdata, double Ydata, double Xdata2, double Ydata2) // プロットしたい2つのデータ->vector
{
    plot_data tmp;
    tmp.xdata = Xdata;
    tmp.ydata = Ydata;
    tmp.xdata2 = Xdata2;
    tmp.ydata2 = Ydata2;
    Vdata.push_back(tmp);
}
void PlotData::PrintFig2Dx2(char *a, char *b) // vector->２次元で2つのグラフ生成
{
    fprintf(gp, "p ");
    fprintf(gp, " '-' pt 5 lc rgb 'red' t \'%s\', ",a);
    fprintf(gp, " '-' pt 5 lc rgb 'blue' t \'%s\' ",b);

    for (int i = 0; i < Vdata.size(); i++)
    {
        // printf("%f %f\n", Vdata[i].xdata, Vdata[i].ydata);
        fprintf(gp, "%f %f\n", Vdata[i].xdata, Vdata[i].ydata);
    }
    fprintf(gp, "e\n");
    for (int j = 0; j < Vdata.size(); j++)
    {
        // printf("%f %f\n", Vdata[j].xdata2, Vdata[j].ydata2);
        fprintf(gp, "%f %f\n", Vdata[j].xdata2, Vdata[j].ydata2);
    }
    fprintf(gp, "e\n");
    fflush(gp);
}
void PlotData::SaveData2Dx3(double Xdata, double Ydata, double Xdata2, double Ydata2, double Xdata3, double Ydata3) // プロットしたい3つのデータ->vector
{
    plot_data tmp;
    tmp.xdata = Xdata;
    tmp.ydata = Ydata;
    tmp.xdata2 = Xdata2;
    tmp.ydata2 = Ydata2;
    tmp.xdata3 = Xdata3;
    tmp.ydata3 = Ydata3;
    Vdata.push_back(tmp);
}
void PlotData::PrintFig2Dx3(char *a, char *b, char *c) // vector->２次元で3つのグラフ生成
{
    fprintf(gp,"set key horizontal\n");
    fprintf(gp, "p ");
    fprintf(gp, " '-' pt 5 lc rgb 'red' t \'%s\', ",a);
    fprintf(gp, " '-' pt 5 lc rgb 'blue' t \'%s\', ",b);
    fprintf(gp, " '-' pt 5 lc rgb 'green' t \'%s\' ",c);
    fprintf(gp, "\n");
    double AveX=0;
    double AveY=0;
    double AveZ=0;
    for (int i = 0; i < Vdata.size(); i++)
    {
        AveX += Vdata[i].ydata;
        
        fprintf(gp, "%f %f\n", Vdata[i].xdata, Vdata[i].ydata);
    }
    fprintf(gp, "e\n");

    for (int j = 0; j < Vdata.size(); j++)
    {
        AveY += Vdata[j].ydata2;
        fprintf(gp, "%f %f\n", Vdata[j].xdata2, Vdata[j].ydata2);
    }
    fprintf(gp, "e\n");

    for (int k = 0; k < Vdata.size(); k++)
    {
        AveZ += Vdata[k].ydata3;
        fprintf(gp, "%f %f\n", Vdata[k].xdata3, Vdata[k].ydata3);
    }
    AveX = AveX/Vdata.size();
    AveY = AveY/Vdata.size();
    AveZ = AveZ/Vdata.size();
    printf("%f %f %f\n",AveX,AveY,AveZ);
    fprintf(gp, "e\n");

    fflush(gp);
}

//***************************3次元***************************//
void PlotData::XYZlabel(char *x, char *y, char *z)
{
    fprintf(gp, "set xlabel '%s'\n\n", x);
    fprintf(gp, "set ylabel '%s'\n\n", y);
    fprintf(gp, "set zlabel '%s'\n\n", z);
}
void PlotData::SaveData3D(double Xdata, double Ydata, double Zdata) // プロットしたいデータ->vectorへ
{
    plot_data tmp;
    tmp.xdata = Xdata;
    tmp.ydata = Ydata;
    tmp.zdata = Zdata;
    Vdata.push_back(tmp);
}
void PlotData::PrintFig3D(void) // vector->２次元で一つのグラフ生成
{
    fprintf(gp, "splot ");
    fprintf(gp, " '-' pt 5 lc rgb 'red' t \"\" ");
    for (int i = 0; i < Vdata.size(); i++)
    {
        printf("%f %f %f\n", Vdata[i].xdata, Vdata[i].ydata, Vdata[i].zdata);
        fprintf(gp, "%f %f %f\n", Vdata[i].xdata, Vdata[i].ydata, Vdata[i].zdata);
    }
    fprintf(gp, "e\n");
    fflush(gp);
}