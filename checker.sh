#!/usr/bin/bash

TESTS=17 
TOTAL=100
TOTALTESTS=0 


function checkExe() {
    if test -f "tema1"
        then
            main
    else
        echo "The executable file needs to be named 'tema1'"
    fi
}


function testInput() {
    cat Teste/Input/test$1.in > tema1.in
    timeout 10s ./tema1 

    if [ "$?" -eq 139 ]
        then
            echo "test$1.in: FAILED (Segmentation Fault)"
            return
    fi

    diff Teste/Output/test$1.out tema1.out > /dev/null 2>&1
    if [ "$?" -ne 0 ]
        then
            echo "test$1.in: FAILED"
    else
        echo "test$1.in: PASSED"
       
    fi
}

function makeCommand() {
    make 1> /dev/null
    if [ "$?" -ne 0 ]
        then
            exit 1
    fi
}

function main() {
    echo "Test results:"
    echo

    touch tren.in
    touch tren.out


    for i in $(seq 1 $TESTS)
    do
        testInput $i
    done
    
    echo

}
makeCommand
checkExe
