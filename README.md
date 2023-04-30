# creatFig
gnuplotで図を生成するクラス

******バグ発生 and これから作成する関数********
1. PrintFig2D()のあとからはグラフの設定できない

2.データラベルの設定追加

3.正方形にするかどうかも定義したほうが良いのか？




*************各プログラムの詳細******************
gptest.cpp   : sampleプログラム


creatfig.cpp + creatfig.hpp : gnuplotでグラフを作成するクラス

        ーdefalutー
                PlotData():引数なしの場合、範囲設定なし

        ー範囲を設定したい場合ー
                PlotData(double xmax, double xmin, double yamx, double ymin)->コンストラクタの複数定義
                Xrangset(),Yrangset(),Zrangset()
                

        -ラベル設定
                XYlabel()
                XYZlabel()
        -tics設定
                settingtics()

        -２次元のグラフを１つ表示    
                saveData2D()
                PrintFig2D()

        -２次元のグラフを２つ表示
                saveData2Dx2()
                PrintFig2Dx2()

        -２次元のグラフを３つ表示
                saveData2Dx3()
                PrintFig2Dx3()

***************コンパイル方法********************
1.gnuplotがインストールされているか確認
->sudo apt install gnuplot

bin/
2.　cmake ..

3. make

4. ./creatfig
