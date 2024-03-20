#!/bin/bash
export CFLAGS="-Wall -Wextra -Wno-unused"

red='\e[0;31m'
green='\e[0;32m'
nc='\e[0m'     

base=$(dirname $0)


function tobase(){
    cd $(dirname $0)
}


function utest( ){

    code=0
    if [ "$1" == "$2" ]
    then
	echo -ne "$green pass $nc"
    else
	echo -ne "$red FAIL $nc"
	code=1
    fi
    echo -e "\t\t $3"
    return $code
}

function utest_ne( ){

    code=0
    if [ "$1" != "$2" ]
    then
	echo -ne "$green pass $nc"
    else
	echo -ne "$red FAIL $nc"
	code=1
    fi
    echo -e "\t\t $3"
    return $code
}

function utest_nz( ){
    if [ ! -z "$1" ]
    then
	echo -ne "$green pass $nc" 
    else
	echo -ne "$red FAIL $nc" 
    fi
    echo -e "\t\t $2"
}

function utest_z( ){
    code=0
    if [ -z "$1" ]
    then
	echo -ne "$green pass $nc" 
    else
	echo -ne "$red FAIL $nc"
	code=1
    fi
    echo -e "\t\t $2"
    return $code
}

function utest_lt(){
    r=$(echo "$1 < $2" | bc)
    if [ "$r" == "1" ]
    then
	echo -ne "$green pass $nc" 
    else
	echo -ne "$red FAIL $nc" 
    fi
    echo -e "\t\t $3"
}

function utest_gt(){
    r=$(echo "$1 > $2" | bc)
    if [ "$r" == "1" ]
    then
	echo -ne "$green pass $nc" 
    else
	echo -ne "$red FAIL $nc" 
    fi
    echo -e "\t\t $3"
}


function test_shredder(){
    echo "--- TEST SHREDDER ---"

    
    cmd="gcc -g -Wall shredder.c -o shredder > /dev/null 2>&1" 
    res=$(eval $cmd)
    utest_z "$res" "compiles without warnings or errors ($res)"
    if [ ! -z "$res" ]
    then
	echo
	echo "--- ERRORS --- "
	echo "$res"
	echo
    fi
    
    touch test.fs
    cmd="./shredder ls | grep test.fs"
    res=$(eval $cmd)
    utest_nz "$res" "exec's command ($cmd)"
    rm test.fs

    cmd="./shredder ls | grep \"Blast that grotesque ganglion\! You let them get away\!\""
    res=$(eval $cmd)
    utest_nz "$res" "prints message \"Blast ...\" ($cmd)"
    
    cmd="./shredder sleep 1.5 | tr \"\\\\n\" \" \""
    res=$(eval $cmd)
    expect="1: tick-tock Blast that grotesque ganglion! You let them get away! "
    utest "$res" "$expect" "prints message and tick's once ($cmd)"
    
    cmd="./shredder sleep 2.5 | tr \"\\\\n\" \" \""
    res=$(eval $cmd)
    expect="1: tick-tock 2: tick-tock Blast that grotesque ganglion! You let them get away! "
    utest "$res" "$expect" "prints message and tick's twice ($cmd)"

    cmd="./shredder sleep 3.5 | tr \"\\\\n\" \" \""
    res=$(eval $cmd)
    expect="1: tick-tock 2: tick-tock 3: tick-tock Sayonara you shell-backed simpletons. I'll get you next time! "
    utest "$res" "$expect" "prints \"Sayonara...\" and tick's three ($cmd)"

    cmd="./shredder sleep 5.5 | tr \"\\\\n\" \" \""
    res=$(eval $cmd)
    expect="1: tick-tock 2: tick-tock 3: tick-tock 4: tick-tock 5: tick-tock Tonight I dine on turtle soup! Muhaha! "
    utest "$res" "$expect" "prints \"Tonight ...\" and tick's five times ($cmd)"


    cmd="./shredder sleep 100 | tr \"\\\\n\" \" \""
    res=$(eval $cmd)
    expect="1: tick-tock 2: tick-tock 3: tick-tock 4: tick-tock 5: tick-tock Tonight I dine on turtle soup! Muhaha! "
    utest "$res" "$expect" "prints \"Tonight ...\" and tick's five times ($cmd)"
    

    echo
}




if [ ! -z $1 ]
then
    cd $1
else
    cd $(dirname $0)
fi


test_shredder
