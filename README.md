# creatFig
gnuplotで図を生成するクラス
******注意********
PrintFig2D()のあとにXYlabel()、settingtics()などがおけない
->replotする関数を作ればいけるかも？？？
******************
creatfig.cpp : gnuplotでグラフを作成するクラス
gptest.cpp   : sampleプログラム

ーdefalutー
PlotData():引数なしの場合、範囲設定なし

ー範囲を設定したい場合ー
PlotData(double xmax, double xmin, double yamx, double ymin)

-２次元のグラフを１つ表示    
        saveData2D()
        PrintFig2D()

-２次元のグラフを２つ表示
        saveData2Dx2()
        PrintFig2Dx2()

-２次元のグラフを３つ表示
        saveData2Dx3()
        PrintFig2Dx3()

*********コンパイル方法***********
1.gnuplotがインストールされているか確認

bin/
2.　cmake ..

3. make

4. ./creatfig
