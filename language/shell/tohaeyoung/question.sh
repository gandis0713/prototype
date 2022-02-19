#!/bin/bash

_BLANK=""
_BLOCK="========================================================================================================================"

print_text() {
    tput setaf 2 &>/dev/null
    count=0
    a=`echo "$1"`
    while [ $count -lt $((${#a}+1)) ]
    do
        x=`expr substr "$a" $count 1`
        if [ "$x" != " " ]
        then
            echo -n $x
            sleep 0.1
        else echo -n " "
        fi
        count=$(($count+1))
    done
    echo " "
    tput sgr0 2 &>/dev/null
}


echo $_BLOCK
print_text '안녕하세요. 김해영님.'
sleep 0.5s
print_text '개발자 적성 테스트에 오신걸 환영합니다.'
sleep 0.5s
print_text '이 테스트는 개발자로써의 성향을 파악하기 위해 제가 준비한 매우 간단한 테스트입니다.'
sleep 0.5s
print_text '테스트에 나오는 문제는 전혀 어렵지 않습니다.'
sleep 0.5s
print_text '그렇기 때문에 너무 걱정하지 않으셔도 됩니다.'
sleep 0.5s
print_text '다만, 문제를 풀 때 보기의 지문을 끝까지 잘 읽고, 신중하게 답해 주시기 바랍니다.'
sleep 1s
print_text "그럼 곧 테스트를 시작하겠습니다."
sleep 1s
print_text "준비가 되면, 'ready' 를 입력해 주시기 바랍니다."
echo $_BLOCK

while true; do
    read -p "Are you ready?" yn
    case $yn in
        [ready]* ) break;;
        * ) echo "준비가 다 되면 'ready'를 입력해 주세요. 오타는 안되요~";;
    esac
done

sleep 1s
echo $_BLOCK
print_text '자 그럼 문제나갑니다.'
sleep 2s
print_text '어느 한 카페에 남성 1명, 여성 1명이 대화를 나누고 있습니다.'
sleep 1s
print_text '두 남녀는 오늘 처음 만났습니다.'
sleep 1s
print_text '그럼에도 불구 하고 어색하지 않게 대화를 잘 나누고 있는 둘은 서로 잘 통하는 것처럼 보입니다.'
sleep 1s
print_text '특히, 남자는 이쁘고 착하고 배려심 많은 여성의 모습에 반한것처럼 보입니다.'
sleep 1s
print_text '첫 만남 이후 남성은 여성와 매일매일 연락하며 그 여성의 매력에 더욱 빠지게 되었습니다.'
sleep 1s
print_text '그리고 남자는 이제 용기내어 여성에게 정식으로 고백하려고 합니다.'
sleep 1s
print_text '당신은 이 남성과 정식으로 만나보시겠습니까? yes or no를 입력해 주세요'

while true; do
    read -p "" yn
    case $yn in
        [Yy]* ) break;;
        * ) echo "틀린 답입니다.";;
    esac
done

echo $_BLOCK
echo $_BLOCK
echo "       ____    ____          ___                                                                                   "
echo "      /    \  /    \        /  /                                                                                   "
echo "     /      \/      \      /  /___  _______    ________    ___   ___ _______   ___   ___ _______   _______         "
echo "     \              /     /  ___  \/  ___  \  / ______/   /  /  /  //  ___  \ /  /  /  //  ___  \ /  ___  \        "
echo "      \            /     /  /  /  /  /__/   \/ ______/   /  /__/  //  /__/  //  /__/  //  /  /  //  /__/  /        "
echo "       \          /     /__/  /__/________/\/_______/    \____   / \_______/ \______ //__/  /__/ \____   /         "
echo "        \        /                                        ___/  /                               /\____/ /          "
echo "         \      /                                        /_____/                                \______/           "
echo "          \    /                                                                                                   "
echo "           \  /                                                                                                    "
echo $_BLANK
echo $_BLOCK
echo $_BLOCK
