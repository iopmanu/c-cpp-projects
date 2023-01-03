flags="benstv"
test_count=0
num_test=1
# 1. Флаги по одному без флагов с аргументами
for (( i=1; i<${#flags}; i++ ));
do
    cat -"${flags:$i:1}" test.txt > original.txt
    ./s21_cat -"${flags:$i:1}"  test.txt > own.txt
    result=$(diff original.txt own.txt)
    if [ $? -eq 1 ]
    then
        echo "ERROR occured with flags ${flags:$i:1} in test $num_test"
    else
        test_count=$(( test_count + 1 ))
    fi
    rm original.txt own.txt
done
