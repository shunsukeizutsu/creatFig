# creatFig
gnuplotで図を生成するクラス

******バグ発生 and これから作成する関数********
1. PrintFig2D()のあとからはグラフの設定できない
->replotでどうにかなるものか？

2.while文を中に入れたが、途中でプログラムが終了してしまうため、returnまで行っていないことが判明
->どうにかしてグラフを出し続ける方法を探る





*************各プログラムの詳細******************
gptest.cpp   : sampleプログラム


creatfig.cpp + creatfig.hpp : gnuplotでグラフを作成するクラス

        ーdefalutー
                PlotData():引数なしの場合、範囲設定なし

        ー範囲を設定したい場合ー
                PlotData(double xmax, double xmin, double yamx, double ymin)->コンストラクタの複数定義
                Xrangset(),Yrangset(),Zrangset()
                
        -表示したグラフをespで保存する場合-
                SaveFigure()->引数に名前

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
