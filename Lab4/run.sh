#!/bin/bash

# Initialize some parameters
paras_num=$#
src_name="Test"
target_name="Test_IR"
file_num=$(find ./$src_name/ -name "*.txt" | wc -l)

# Default source file path will be told to users.
echo "Default source file path: ${src_name}"
echo "If you want to chage the source file path, please edit the file called \"run.sh\""

# Usage.
echo "Usage: ./run.sh [-p] [-s] [-dag] [-ir] -[a] [result path]"
echo "       source: default source is ${src_name}"
echo "       default mode: \"-ir\""
echo "       -p  print the syntax tree"
echo "       -s  only process semantic checking"
echo "     -dag  enable dag optimizing"
echo "      -ir  only process generating IR code"
echo "       -a  process generating assembly code"
echo "                                           "
echo "  --clean  this parameter should be used alone and it tells the program to clean up all unnecessary files."
echo "Copyright: Qiaoyi Yin @NJU\n" 

# Clean up
if [[ $paras_num == 1 && "$@" == "--clean" ]];then
    cd Code
    make clean
    cd ..
else
    # Enter into Code folder to build.
    cd Code
    make parser

    # Change the location of the excutable file.
    if [ $(find ./ -name "parser" | wc -l) != 0 ];then
        cp parser ./../parser
        rm -rf parser
    fi
    cd ..

    # Analyze the parameters and output the results.
    if [ $paras_num == 0 ];then
        echo "Default Mode: generate the intermediate representation code"
        echo "Default Results Storage Path: ${target_name}"
        
        # Find the target storage folder. If it doesn't exit, create one.
        if [ $(find ./ -name ${target_name} | wc -l) != 0 ];then
            rm -rf ${target_name}
            mkdir ${target_name}
        else
            mkdir ${target_name}
        fi

        # Start the program execution
        for ((i=1;i<=$file_num;i++))
        do
            ./parser -ir ./$src_name/test${i}.txt 1>>${target_name}/test${i}_ir.ir 2>>${target_name}/test${i}_ir.ir
        done
    else
        args=" "

        st_flag=0
        sa_flag=0
        ir_flag=0
        asm_flag=0

        echo "User-Chosen Mode: " $@

        # Determine the result path and other modes that are chosen
        for arg in "$@"
        do
            if [ ${arg} == "-p" ];then
                st_flag=1
            fi
            if [ ${arg} == "-a" ];then
                asm_flag=1
            fi
            if [ ${arg} == "-ir" ];then
                ir_flag=1
                rm -rf "Test_IR"
            fi
            if [ ${arg} == "-s" ];then
                sa_flag=1
            fi

            if [ ${arg:0:1} != "-" ];then
                target_name=${arg}
            else
                args=${args}" "${arg}
            fi
        done

        # Start the program execution
        echo "User-Chosen Storage Path: ${target_name}"
        for ((i=1;i<=$file_num;i++))
        do
            if [[ $st_flag == 0 && $sa_flag == 0 && $ir_flag == 0 && $asm_flag == 1 ]];then
                if [ ${target_name} == "Test_IR" ];then
                    echo "Change the default storage path: ${target_name} -> Test_ASM"
                    target_name="Test_ASM"
                    echo ${target_name}
                    rm -rf ${target_name}
                fi
                if [ $(find ./ -name ${target_name} | wc -l) == 0 ];then
                    mkdir ${target_name}
                fi
                ./parser ${args} ./$src_name/test${i}.txt 1>>${target_name}/test${i}_asm.asm 2>>${target_name}/test${i}_asm.asm
            elif [[ $st_flag == 0 && $sa_flag == 0 && $ir_flag == 1 ]];then
                if [ $(find ./ -name ${target_name} | wc -l) == 0 ];then
                    mkdir ${target_name}
                fi
                ./parser ${args} ./$src_name/test${i}.txt 1>>${target_name}/test${i}_ir.ir 2>>${target_name}/test${i}_ir.ir
            elif [[ $st_flag == 0 && $sa_flag == 1 ]];then
                if [ ${target_name} == "Test_IR" ];then
                    echo "Change the default storage path: ${target_name} -> Test_SA"
                    target_name="Test_SA"
                    rm -rf ${target_name}
                fi
                if [ $(find ./ -name ${target_name} | wc -l) == 0 ];then
                    mkdir ${target_name}
                fi
                ./parser ${args} ./$src_name/test${i}.txt 1>>${target_name}/test${i}_sa.txt 2>>${target_name}/test${i}_sa.txt
            elif [[ $st_flag == 1 && $sa_flag == 1 ]];then
                if [ ${target_name} == "Test_IR" ];then
                    echo "Change the default storage path: ${target_name} -> Test_ST_SA"
                    target_name="Test_ST_SA"
                    rm -rf ${target_name}
                fi
                if [ $(find ./ -name ${target_name} | wc -l) == 0 ];then
                    mkdir ${target_name}
                fi
                ./parser ${args} ./$src_name/test${i}.txt 1>>${target_name}/test${i}_st_sa.txt 2>>${target_name}/test${i}_st_sa.txt
            elif [[ $st_flag == 1 && $sa_flag == 0 ]];then
                if [ ${target_name} == "Test_IR" ];then
                    echo "Change the default storage path: ${target_name} -> Test_ST"
                    target_name="Test_ST"
                    rm -rf ${target_name}
                fi
                if [ $(find ./ -name ${target_name} | wc -l) == 0 ];then
                    mkdir ${target_name}
                fi
                ./parser ${args} ./$src_name/test${i}.txt 1>>${target_name}/test${i}_st.txt 2>>${target_name}/test${i}_st.txt
            else 
                echo "None results have been generated."
            fi
        done
    fi
fi