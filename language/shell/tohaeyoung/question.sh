#!/bin/bash

_BLANK=""
_BLOCK="========================================================================================================================"

echo $_BLOCK
echo $_BLOCK
echo "       ____________                 ___                                                                                   "
echo "      /____   ____/                /  /                                                                                   "
echo "          /  / _______            /  /___  _______    ________    ___   ___ _______   ___   ___ _______   _______         "
echo "         /  / /  ___  \          /  ___  \/  ___  \  / ______/   /  /  /  //  ___  \ /  /  /  //  ___  \ /  ___  \        "
echo "        /  / /  /__/  / __      /  /  /  /  /__/   \/ ______/   /  /__/  //  /__/  //  /__/  //  /  /  //  /__/  /        "
echo "       /__/  \_______/ /_/     /__/  /__/________/\/_______/    \____   / \_______/ \______ //__/  /__/ \____   /         "
echo "                                                                 ___/  /                               /\____/ /          "
echo "                                                                /_____/                                \______/           "
echo $_BLANK
echo $_BLOCK
echo $_BLOCK

count=0
echo "enter your name"
read b
sleep 2
a="hello"
a=`echo $a" "$b" nice to meet you"`
while [ $count -lt $((${#a}+1)) ]
do
    x=`expr substr "$a" $count 1`
    if [ "$x" != " " ]
    then
        echo -n $x
        sleep 0.2
    else echo -n " "
    fi
    count=$(($count+1))
done
echo " "


string='000 테스트에 오실걸 환영합니다.\0'
for ((i=0; i<${#string}; i++)); do
    printf '%s' "${string:$i:1}"
    sleep 0.0$(( (RANDOM % 5) + 1 ))
done 

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