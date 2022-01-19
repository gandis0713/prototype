#!/bin/bash

_BLANK=""
_BLOCK="========================================================================================================================"

# echo $_BLOCK
# echo $_BLOCK
# echo "       ____________                 ___                                                                                   "
# echo "      /____   ____/                /  /                                                                                   "
# echo "          /  / _______            /  /___  _______    ________    ___   ___ _______   ___   ___ _______   _______         "
# echo "         /  / /  ___  \          /  ___  \/  ___  \  / ______/   /  /  /  //  ___  \ /  /  /  //  ___  \ /  ___  \        "
# echo "        /  / /  /__/  / __      /  /  /  /  /__/   \/ ______/   /  /__/  //  /__/  //  /__/  //  /  /  //  /__/  /        "
# echo "       /__/  \_______/ /_/     /__/  /__/________/\/_______/    \____   / \_______/ \______ //__/  /__/ \____   /         "
# echo "                                                                 ___/  /                               /\____/ /          "
# echo "                                                                /_____/                                \______/           "
# echo $_BLANK
# echo $_BLOCK
# echo $_BLOCK


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


# echo $_BLOCK
# print_text '안녕하세요. 김해영님.'
# sleep 0.5s
# print_text '개발자 적성 테스트에 오신걸 환영합니다.'
# sleep 0.5s
# print_text '이 테스트는 개발자로써의 성향을 파악하기 위해 제가 준비한 매우 간단한 테스트입니다.'
# sleep 0.5s
# print_text '테스트에 나오는 문제는 전혀 어렵지 않습니다.'
# sleep 0.5s
# print_text '그렇기 때문에 너무 걱정하지 않으셔도 됩니다.'
# sleep 0.5s
# print_text '다만, 문제를 풀 때 보기의 지문을 끝까지 잘 읽고, 신중하게 답해 주시기 바랍니다.'
# sleep 1s
# print_text "그럼 곧 테스트를 시작하겠습니다. 준비가 다 되면, 'ready' 를 입력해 주시기 바랍니다."
# echo $_BLOCK

# while true; do
#     read -p "Are you ready?" yn
#     case $yn in
#         [ready]* ) break;;
#         * ) echo "준비가 다 되면 'ready'를 입력해 주세요. 오타는 안되요~";;
#     esac
# done


echo $_BLOCK
print_text '자 그럼 문제나갑니다.'
sleep 2s
print_text '어느 한 카페에 남성 1명, 여성 1명이 대화를 나누고 있습니다.'
sleep 1s
print_text '두 남녀는 오늘 처음 만났습니다.'
sleep 1s
print_text '그럼에도 불구 하고 어색하지 않게 대화를 잘 나누고 있고 둘은 잘 통하는 것처럼 보입니다.'
sleep 1s
print_text '특히, 남자는 이쁘고 착하고 배려심 많은 여성의 모습에 큰 호기심을 가진 것 처럼 보입니다.'
sleep 1s
print_text '시간이 흐르고, 남자는 여자와 대화를 더 나누고 싶어, 여성에게 저녁을 먹으러 가지고 제안합니다.'
sleep 1s
print_text '다행히 여성은 흔쾌히 수락하는 것처럼 보입니다.'
sleep 1s
print_text '그리고 둘은 저녁은 먹으면 서로의 대해 조금 더 알아 가며 가까워 지고 있는 것처럽 보입니다.'
sleep 1s
print_text '남자는 시간이 흐를 수록 그녀의 매력에 빠져 드는 것처럼 보입니다.'
sleep 1s
print_text '저녁은 그 그녀의 매력에 빠져 드는 것처럼 보입니다.'


# count=0
# a=`echo "000 테스트에 오실걸 환영합니다."`
# while [ $count -lt $((${#a}+1)) ]
# do
#     x=`expr substr "$a" $count 1`
#     if [ "$x" != " " ]
#     then
#         echo -n $x
#         sleep 0.05
#     else echo -n " "
#     fi
#     count=$(($count+1))
# done
# echo " "


# string='000 테스트에 오실걸 환영합니다.\0'
# for ((i=0; i<${#string}; i++)); do
#     printf '%s' "${string:$i:1}"
#     sleep 0.0$(( (RANDOM % 5) + 1 ))
# done 

# matrix(){
#     tput setaf 2 &>/dev/null # green powaaa
#     for ((i=0; i<=${#1}; i++)); do
#         printf '%s' "${1:$i:1}"
#         sleep 0.$(( (RANDOM % 5) + 1 ))
#     done
#     tput sgr0 2 &>/dev/null
# }

# matrix 'foo bar base'

# NUMS="\r\033[1A\033[0K"
# for NUM in '당' '신' '의' ' ' '테' '스' '트' '에' ' ' '오' '신' '걸' ' ' '환' '영' '합' '니' '다' '.' ; do
#   sleep 1s
#   NUMS+="${NUM} "
#   echo -e "$NUMS"
# done

# while true; do
#     read -p "Do you wish to install this progra당신은?" yn
#     case $yn in
#         [Yy]* ) break;;
#         # [Nn]* ) exit;;
#         * ) echo "You can answer only yes.";;
#     esac
# done

# while true; do
#     read -p "Do you wish to install this program2?" yn
#     case $yn in
#         [Yy]* ) break;;
#         # [Nn]* ) exit;;
#         * ) echo "You can answer only yes.";;
#     esac
# done