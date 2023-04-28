#cmakeのバージョン設定
cmake_minimum_required(VERSION 3.13)
#プロジェクト名と使用する言語
project(test CXX)
#hello_worldを[ファイル場所]から作成
add_executable(creatFig ./src/gptest.cpp ./src/creatfig.cpp)