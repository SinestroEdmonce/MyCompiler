#!/bin/bash
# Enter into Code folder to build
cd Code
make clean
make parser

# Change the location of the excutable file
if [ $(find ./ -name "parser" | wc -l) != 0 ];then
    cp parser ./../parser
    rm -rf parser
fi
cd ..

paras_num=$#
src_name='Test'
file_num=$(find ./$src_name/ -name "*.txt" | wc -l)

if [ $paras_num == 0 ];then
    echo 'Default Results Storage Path: results.txt'
    for ((i=1;i<=$file_num;i++))
    do
        echo -e "$i" >> results.txt
	    ./parser ./$src_name/test${i}.txt 1>>results.txt 2>>results.txt
    done
else
    for ((i=1;i<=$file_num;i++))
    do
        echo -e "$i" >> $1.txt
	    ./parser ./$src_name/test${i}.txt 1>>$1.txt 2>>$1.txt
    done
fi

