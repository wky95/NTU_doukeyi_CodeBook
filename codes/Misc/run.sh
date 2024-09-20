g++ gen.cpp -o gen
g++ checker.cpp -o checker
g++ valid.cpp -o valid
g++ sol/main_sol.cpp -o jsol
g++ sol/BF.cpp -o psol
echo > gen_command.txt

declare -i counter=1
# 0 = 執行所有程式
# 1 = 如果 WA 就結束
declare -i mode=0
declare -i tl=5

if [ ! -d "./input" ]; then
mkdir input
fi
if [ ! -d "./output" ]; then
    mkdir output
fi
if [ ! -d "./answer" ]; then
    mkdir answer
fi

function run() {
    echo -n ./input/$1.in ：
    ./valid < input/$1.in
    if [ $? -ne 0 ]; then
        echo -e "\033[1;31mInput format not corret.\033[0m"
        exit 0
    fi
    
    timeout ${tl} ./jsol < input/$1.in > answer/$1.ans
    if [ $? -ne 0 ]; then
        echo -e "\033[1;34mTLE\033[0m Jury answer got time limit exceeded."
        exit 0
    fi

    timeout ${tl} ./psol < input/$1.in > output/$1.out
    if [ $mode -eq 1 -a $? -ne 0 ]; then
        echo -e "\033[1;34mTLE\033[0m Participant answer got time limit exceeded."
        exit 0
    fi
    
    ./checker input/$1.in output/$1.out answer/$1.ans
    if [ $mode -eq 1 -a $? -eq 1 ]; then
        exit 0
    fi

    counter=$((${counter}+1))
}

function run_group() {
    echo \<#list 1..$1 as i\> >> gen_command.txt
    echo -e "\t"gen $2 \${i*17+10} \> \$ >> gen_command.txt
    echo \</#list\> >> gen_command.txt
    
    echo ========================
    echo TestGroup：$2
    for ((i=1 ; i<=$1 ; i=i+1))
    do
        ./gen $2 $((${i}*17+10)) > input/${counter}.in
        run ${counter}
    done
}

# example
run example1

# generator
run_group 5 "-n=50 -mode=big"
run_group 5 "-n=50 -mode=random"
run_group 5 "-mode=big"
run_group 5 "-mode=random"