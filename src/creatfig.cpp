#include "creatfig.hpp"

PlotData::PlotData()            // default
{                              // グラフの詳細設定、文字のフォント等
    gp = popen("gnuplot", "w"); // シェル起動
    fprintf(gp, "set grid\n");
    fprintf(gp, "set size ratio -1\n\n");
    fprintf(gp, "set size square \n\n");
    fprintf(gp, "set xlabel font 'Arial,22'\n\n");
    fprintf(gp, "set ylabel font 'Arial,22'\n\n");
    fprintf(gp, "set xlabel offset 0,-1\n\n");
    fprintf(gp, "set ylabel offset -4,0\n\n");
    fprintf(gp, "set tics font 'Arial,15'\n\n");
    fprintf(gp, "set grid linewidth 1.5\n\n");
}
PlotData::PlotData(double xmax, double xmin, double yamx, double ymin) // グラフの範囲を設定したい場合
{
    gp = popen("gnuplot", "w"); // シェル起動
    fprintf(gp, "set grid\n");
    fprintf(gp, "set size ratio -1\n\n");
    fprintf(gp, "set size square \n\n");
    fprintf(gp, "set xlabel font 'Arial,22'\n\n");
    fprintf(gp, "set ylabel font 'Arial,22'\n\n");
    fprintf(gp, "set xlabel offset 0,-1\n\n");
    fprintf(gp, "set ylabel offset -4,0\n\n");
    fprintf(gp, "set tics font 'Arial,15'\n\n");
    fprintf(gp, "set grid linewidth 1.5\n\n");
    fprintf(gp, "set xrange[%f:%f]\nset yrange[%f:%f]\n\n", xmin, xmax, ymin, yamx); // 範囲
}
PlotData::~PlotData()
{
    pclose(gp);
}
void PlotData::saveData2D(double Xdata, double Ydata) // プロットしたいデータ->vectorへ
{
    plot_data tmp;
    tmp.xdata = Xdata;
    tmp.ydata = Ydata;
    Vdata.push_back(tmp);
}
void PlotData::PrintFig2D(void) // vector->２次元で一つのグラフ生成
{
    printf( "\x1b[32m\x1b[1m%s\x1b[39m\x1b[0m\n", "Start Plot PrintFigure 2D" );
    fprintf(gp, "set xlabel 'xlabelname'\n\n");
    fprintf(gp, "set ylabel 'ylabelname '\n\n");
    fprintf(gp, "p ");
    fprintf(gp, " '-' pt 7 ps 1 lc rgb 'red' t \"\" ");
    for (int i = 0; i < Vdata.size(); i++)
    {
        //printf("%f %f\n", Vdata[i].xdata, Vdata[i].ydata);
        fprintf(gp, "%f %f\n", Vdata[i].xdata, Vdata[i].ydata);
    }
    fprintf(gp, "e\n");
    fflush(gp);
}
void PlotData::saveData2Dx2(double Xdata, double Ydata, double Xdata2, double Ydata2) // プロットしたい2つのデータ->vector
{
    plot_data tmp;
    tmp.xdata = Xdata;
    tmp.ydata = Ydata;
    tmp.xdata2 = Xdata2;
    tmp.ydata2 = Ydata2;
    Vdata.push_back(tmp);
}
void PlotData::PrintFig2Dx2(void) // vector->２次元で2つのグラフ生成
{
    fprintf(gp, "set xlabel 'xlabelname'\n\n");
    fprintf(gp, "set ylabel 'ylabelname '\n\n");
    fprintf(gp, "p ");
    fprintf(gp, " '-' pt 7 ps 1 lc rgb 'red' t 'notitle', ");
    fprintf(gp, " '-' pt 7 ps 1 lc rgb 'blue' t 'notitle2' ");

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
void PlotData::saveData2Dx3(double Xdata, double Ydata, double Xdata2, double Ydata2, double Xdata3, double Ydata3) // プロットしたい3つのデータ->vector
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
void PlotData::PrintFig2Dx3(void) // vector->２次元で3つのグラフ生成
{
    fprintf(gp, "set xlabel 'xlabelname'\n\n");
    fprintf(gp, "set ylabel 'ylabelname '\n\n");
    fprintf(gp, "p ");
    fprintf(gp, " '-' pt 7 ps 1 lc rgb 'red' t 'notitle', ");
    fprintf(gp, " '-' pt 7 ps 1 lc rgb 'blue' t 'notitle2', ");
    fprintf(gp, " '-' pt 7 ps 1 lc rgb 'green' t 'notitle3' ");

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

    for (int k = 0; k < Vdata.size(); k++)
    {
        // printf("%f %f\n", Vdata[j].xdata2, Vdata[j].ydata2);
        fprintf(gp, "%f %f\n", Vdata[k].xdata3, Vdata[k].ydata3);
    }
    fprintf(gp, "e\n");

    fflush(gp);
}
void PlotData::saveData3D(double Xdata, double Ydata,double Zdata)//プロットしたいデータ->vectorへ
{
    plot_data tmp;
    tmp.xdata = Xdata;
    tmp.ydata = Ydata;
    tmp.zdata = Zdata;
    Vdata.push_back(tmp);
}
void PlotData::PrintFig3D(void)//vector->２次元で一つのグラフ生成
{
    fprintf(gp, "set xlabel 'xlabelname'\n\n");
    fprintf(gp, "set ylabel 'ylabelname '\n\n");
    fprintf(gp, "set ylabel 'zlabelname '\n\n");
    fprintf( gp, "splot " );
    fprintf(gp, " '-' pt 7 ps 1 lc rgb 'red' t \"\" ");
    for (int i = 0; i < Vdata.size(); i++)
    {
        printf("%f %f %f\n", Vdata[i].xdata, Vdata[i].ydata,Vdata[i].zdata);
        fprintf(gp, "%f %f %f\n", Vdata[i].xdata, Vdata[i].ydata,Vdata[i].zdata);
    }
    fprintf(gp, "e\n");
    fflush(gp);
}