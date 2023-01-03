flags="evinclhso"
test_count=0
num_test=1
# 1. Флаги с одним файлом
for (( i=1; i<${#flags}; i++ ));
do
    grep -"${flags:$i:1}" dw test.txt > original.txt
    ./s21_grep -"${flags:$i:1}" dw test.txt > own.txt
    result=$(diff original.txt own.txt)
    if [ $? -eq 1 ]
    then
        echo "ERROR with flags ${flags:$i:1} in test $num_test"
    else
        test_count=$(( test_count + 1 ))
    fi
    rm original.txt own.txt
done

# 2. Флаги с несколькими файлами 
flags="evinclhs"
for (( i=1; i<${#flags}; i++ ));
do
    grep -"${flags:$i:1}" dw test.txt aboba.txt > original.txt
    ./s21_grep -"${flags:$i:1}" dw test.txt aboba.txt > own.txt
    result=$(diff original.txt own.txt)
    if [ $? -eq 1 ]
    then
        echo "ERROR with flags ${flags:$i:1} in test $num_test"
    else
        test_count=$(( test_count + 1 ))
    fi
    rm original.txt own.txt
done
