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
    fprintf(gp, "set terminal postscript eps color enhanced\n");
    fprintf(gp, "set out '%s.esp'\n", fname);
    fprintf(gp, "replot\n");
}
void PlotData::SeTics(double xtics, double ytics)
{
    fprintf(gp, "set xtics %f\n", xtics);
    fprintf(gp, "set ytics %f\n", ytics);
    fprintf(gp, "set xtics rotate by -90\n");
    fprintf(gp, "set tics font 'Helvetica,10'\n");
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
void PlotData::SaveData_GNSS(double Xdata, double Ydata, double Zdata, int status)
{
    plot_data tmp;
    tmp.xdata = Xdata;
    tmp.ydata = Ydata;
    tmp.zdata = Zdata;
    tmp.status = status;
    count++;
    switch (status)
    {
    case 0:
        UNKNOWN.push_back(tmp);
        break;
    case 1:
        SINGLE.push_back(tmp);
        break;
    case 2:
        DGPS.push_back(tmp);
        break;
    case 4:
        Vdata.push_back(tmp);
        break;
    case 5:
        FLOAT.push_back(tmp);
        break;
    default:
        break;
    }
    // std::cout << Vdata.size() << "," << FLOAT.size() << "," << DGPS.size() << std::endl;
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
    fprintf(gp, " '-' pt 7 ps 0.5 lc rgb 'blue' t \'\'");
    fprintf(gp, "\n");

    for (int i = 0; i < Vdata.size(); i++)
    {
        fprintf(gp, "%f %f\n", Vdata[i].xdata, Vdata[i].ydata);
    }
    fprintf(gp, "e\n");
    fflush(gp);
}
/*void PlotData::GNSS_PrintFig2D() // vector->２次元で一つのグラフ生成
{
    printf("\x1b[32m\x1b[1m%s\x1b[39m\x1b[0m\n", "Start Plot PrintFigure 2D");
   // fprintf(gp, "plot '-' using 1:(($3==2) ? 2 : 1/0) w lp pt 7 lc rgb 'blue' ps 0.3 t 'RTK FIX (1)', \\\n");
    fprintf(gp,"set palette defined (0 'blue', 1 'green', 2 'orange')\n");
    fprintf(gp, "plot '-' using 1:2:(($3==4) ? 0 : 1) w points palette pt 7 ps 0.3 t \'\'\n");
    fprintf(gp, " '-' using 1:2:(($3==4) ? 0 : 1) w points palette pt 7 ps 0.3 t \'\'\n");


    // データポイントのプロット
    for (int i = 0; i < Vdata.size(); i++)
    {
        fprintf(gp, "%f %f %d\n", Vdata[i].xdata, Vdata[i].ydata, Vdata[i].status);
        //printf("%f %f %d\n", Vdata[i].xdata, Vdata[i].ydata, Vdata[i].status);
    }
    fprintf(gp, "e\n");
    fflush(gp);
}*/
double PlotData::GNSS_PrintFig2D() // vector->２次元で一つのグラフ生成
{
    printf("\x1b[32m\x1b[1m%s\x1b[39m\x1b[0m\n", "Start Plot PrintFigure 2D");
    fprintf(gp, "p ");
    fprintf(gp, " '-' pt 7 ps 0.2 lc rgb 'blue' t \'FIX\', ");
    fprintf(gp, " '-' pt 7 ps 0.2 lc rgb 'orange' t \'FLOAT\', ");
    fprintf(gp, " '-' pt 7 ps 0.2 lc rgb 'forest-green' t \'DGPS\', ");
    fprintf(gp, " '-' pt 7 ps 0.2 lc rgb 'red' t \'SINGLE\', ");
    fprintf(gp, " '-' pt 7 ps 0.2 lc rgb 'black' t \'UNKNOWN\' ");
    fprintf(gp, "\n");
    // データポイントのプロット
    for (int i = 0; i < Vdata.size(); i++)
    {
        fprintf(gp, "%f %f\n", Vdata[i].xdata, Vdata[i].ydata);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < FLOAT.size(); i++)
    {
        fprintf(gp, "%f %f\n", FLOAT[i].xdata, FLOAT[i].ydata);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < DGPS.size(); i++)
    {
        fprintf(gp, "%f %f\n", DGPS[i].xdata, DGPS[i].ydata);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < SINGLE.size(); i++)
    {
        fprintf(gp, "%f %f\n", SINGLE[i].xdata, SINGLE[i].ydata);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < UNKNOWN.size(); i++)
    {
        fprintf(gp, "%f %f\n", UNKNOWN[i].xdata, UNKNOWN[i].ydata);
    }
    fprintf(gp, "e\n");

    fflush(gp);
    rate_fix = (double)Vdata.size() / (double)count;
    return rate_fix * 100;
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
    fprintf(gp, " '-' pt 7 ps 0.5 lc rgb 'red' t \'%s\', ", a);
    fprintf(gp, " '-' pt 7 ps 0.5 lc rgb 'blue' t \'%s\' ", b);
    fprintf(gp, "\n");

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
void PlotData::SaveData2Dx3_1(double Xdata,double Ydata)
{
	plot_data tmp;
	tmp.xdata = Xdata;
	tmp.ydata = Ydata;
	Vdata.push_back(tmp);
}
void PlotData::SaveData2Dx3_2(double Xdata,double Ydata)
{
	plot_data tmp2;
	tmp2.xdata = Xdata;
	tmp2.ydata = Ydata;
	Vdata2.push_back(tmp2);
}
void PlotData::SaveData2Dx3_3(double Xdata,double Ydata)
{
	plot_data tmp3;
	tmp3.xdata = Xdata;
	tmp3.ydata = Ydata;
	Vdata3.push_back(tmp3);
}
void PlotData::SaveData2Dx3_4(double Xdata,double Ydata)
{
	plot_data tmp4;
	tmp4.xdata = Xdata;
	tmp4.ydata = Ydata;
	Vdata4.push_back(tmp4);
}
void PlotData::PrintFig2Dx3_123() // vector->２次元で一つのグラフ生成
{
    printf("\x1b[32m\x1b[1m%s\x1b[39m\x1b[0m\n", "Start Plot PrintFigure 2D");
    fprintf(gp, "p ");
    fprintf(gp, " '-' pt 7 ps 1 lc rgb 'blue' t \'localizer\', ");
    fprintf(gp, " '-' w lp pt 1 ps 0.5 lc rgb 'orange' t \'odm_global\', ");
    fprintf(gp, " '-' w lp pt 5 ps 1 lc rgb 'forest-green' t \'ndt\', ");
    fprintf(gp, " '-' pt 7 ps 1 lc rgb 'red' t \'gnss\'");
    fprintf(gp, "\n");
    // データポイントのプロット
    for (int i = 0; i < Vdata.size(); i++)
    {
        fprintf(gp, "%f %f\n", Vdata[i].xdata, Vdata[i].ydata);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < Vdata2.size(); i++)
    {
        fprintf(gp, "%f %f\n", Vdata2[i].xdata, Vdata2[i].ydata);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < Vdata3.size(); i++)
    {
        fprintf(gp, "%f %f\n", Vdata3[i].xdata, Vdata3[i].ydata);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < Vdata4.size(); i++)
    {
        fprintf(gp, "%f %f\n", Vdata4[i].xdata, Vdata4[i].ydata);
    }
    fprintf(gp, "e\n");

    fflush(gp);
}
void PlotData::PrintFig2Dx3() // vector->２次元で一つのグラフ生成
{
    printf("\x1b[32m\x1b[1m%s\x1b[39m\x1b[0m\n", "Start Plot PrintFigure 2D");
    fprintf(gp, "p ");
    fprintf(gp, " '-' pt 7 ps 0.5 lc rgb 'blue' t \'wp1\', ");
    fprintf(gp, " '-' pt 5 ps 0.5 lc rgb 'red' t \'wp2\'");
    fprintf(gp, "\n");
    // データポイントのプロット
    for (int i = 0; i < Vdata.size(); i++)
    {
        fprintf(gp, "%f %f\n", Vdata[i].xdata, Vdata[i].ydata);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < Vdata2.size(); i++)
    {
        fprintf(gp, "%f %f\n", Vdata2[i].xdata, Vdata2[i].ydata);
    }
    fprintf(gp, "e\n");

    fflush(gp);
}	
void PlotData::PrintFig2Dx3(char *a, char *b, char *c) // vector->２次元で3つのグラフ生成
{
    fprintf(gp, "set key horizontal\n");
    fprintf(gp, "p ");
    fprintf(gp, " '-' pt 7 ps 0.5 lc rgb 'red' t \'%s\', ", a);
    fprintf(gp, " '-' pt 7 ps 0.5 lc rgb 'blue' t \'%s\', ", b);
    fprintf(gp, " '-' pt 7 ps 0.5 lc rgb 'green' t \'%s\' ", c);
    fprintf(gp, "\n");
    double AveX = 0;
    double AveY = 0;
    double AveZ = 0;
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
    AveX = AveX / Vdata.size();
    AveY = AveY / Vdata.size();
    AveZ = AveZ / Vdata.size();
    printf("%f %f %f\n", AveX, AveY, AveZ);
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
    fprintf(gp, " '-' pt 7 ps 0.5 lc rgb 'red' t \"\" ");
    for (int i = 0; i < Vdata.size(); i++)
    {
        printf("%f %f %f\n", Vdata[i].xdata, Vdata[i].ydata, Vdata[i].zdata);
        fprintf(gp, "%f %f %f\n", Vdata[i].xdata, Vdata[i].ydata, Vdata[i].zdata);
    }
    fprintf(gp, "e\n");
    fflush(gp);
}
void PlotData::GNSS_PrintFig3D(void) // vector->２次元で一つのグラフ生成
{
    printf("\x1b[32m\x1b[1m%s\x1b[39m\x1b[0m\n", "Start Plot PrintFigure GNSS 3D");
    fprintf(gp, "splot ");
    fprintf(gp, " '-' pt 7 ps 0.2 lc rgb 'blue' t \'FIX\', ");
    fprintf(gp, " '-' pt 7 ps 0.2 lc rgb 'orange' t \'FLOAT\', ");
    fprintf(gp, " '-' pt 7 ps 0.2 lc rgb 'forest-green' t \'DGPS\', ");
    fprintf(gp, " '-' pt 7 ps 0.2 lc rgb 'red' t \'SINGLE\', ");
    fprintf(gp, " '-' pt 7 ps 0.2 lc rgb 'black' t \'UNKNOWN\' ");
    fprintf(gp, "\n");
    // データポイントのプロット
    for (int i = 0; i < Vdata.size(); i++)
    {
        fprintf(gp, "%f %f %f\n", Vdata[i].xdata, Vdata[i].ydata,Vdata[i].zdata);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < FLOAT.size(); i++)
    {
        fprintf(gp, "%f %f %f\n", FLOAT[i].xdata, FLOAT[i].ydata,FLOAT[i].zdata);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < DGPS.size(); i++)
    {
        fprintf(gp, "%f %f %f\n", DGPS[i].xdata, DGPS[i].ydata,DGPS[i].zdata);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < SINGLE.size(); i++)
    {
        fprintf(gp, "%f %f %f\n", SINGLE[i].xdata, SINGLE[i].ydata,SINGLE[i].zdata);
    }
    fprintf(gp, "e\n");

    for (int i = 0; i < UNKNOWN.size(); i++)
    {
        fprintf(gp, "%f %f %f\n", UNKNOWN[i].xdata, UNKNOWN[i].ydata,UNKNOWN[i].zdata);
    }
    fprintf(gp, "e\n");

    fflush(gp);
}
